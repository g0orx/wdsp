/*  eq.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2013 Warren Pratt, NR0V

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

The author can be reached by email at  

warren@wpratt.com

*/

#include "comm.h"

double* eq_mults (int size, int nfreqs, double* F, double* G, double samplerate, double scale, int ctfmode, int method)
{
	double* fp = (double *) malloc0 ((nfreqs + 2)   * sizeof (double));
	double* gp = (double *) malloc0 ((nfreqs + 2)   * sizeof (double));
	double* A  = (double *) malloc0 ((size / 2 + 1) * sizeof (double));
	double gpreamp, f, frac;
	double* impulse;
	double* mults;
	int i, j, mid;
	fp[0] = 0.0;
	fp[nfreqs + 1] = 1.0;
	gp[0] = G[1];
	gp[nfreqs + 1] = G[nfreqs];
	gpreamp = G[0];
	for (i = 1; i <= nfreqs; i++)
	{
		fp[i] = 2.0 * F[i] / samplerate;
		gp[i] = G[i];
	}
	mid = size / 2;
	j = 0;
	for (i = 0; i <= mid; i++)
	{
		f = (double)i / (double)mid;
		while (f > fp[j + 1]) j++;
		frac = (f - fp[j]) / (fp[j + 1] - fp[j]);
		A[i] = pow (10.0, 0.05 * (frac * gp[j + 1] + (1.0 - frac) * gp[j] + gpreamp)) * scale;
	}
	if (ctfmode == 0)
	{
		int k;
		int low = (int)(fp[1] * mid);
		int high = (int)(fp[nfreqs] * mid + 0.5);
		double lowmag = A[low];
		double highmag = A[high];
		double flow4 = pow((double)low / (double)mid, 4.0);
		double fhigh4 = pow((double)high / (double)mid, 4.0);
		k = low;
		while (--k >= 0)
		{
			f = (double)k / (double)mid;
			lowmag *= (f * f * f * f) / flow4;
			if (lowmag < 1.0e-100) lowmag = 1.0e-100;
			A[k] = lowmag;
		}
		k = high;
		while (++k <= mid)
		{
			f = (double)k / (double)mid;
			highmag *= fhigh4 / (f * f * f * f);
			if (highmag < 1.0e-100) highmag = 1.0e-100;
			A[k] = highmag;
		}
	}
	if (method == 0)
		impulse = fir_fsamp(size + 1, A, 1, 1.0, -1);
	else
		impulse = fir_fsamp_odd(size + 1, A, 1, 1.0, -1);
	// print_impulse("eq.txt", size + 1, impulse, 1, 0);
	mults = fftcv_mults(2 * size, impulse);
	_aligned_free (impulse);
	_aligned_free (A);
	_aligned_free (gp);
	_aligned_free (fp);
	return mults;
}

void calc_eq (EQ a)
{
	a->scale = 1.0 / (double)(2 * a->size);
	a->infilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->product = (double *)malloc0(2 * a->size * sizeof(complex));
	a->CFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->infilt, (fftw_complex *)a->product, FFTW_FORWARD, FFTW_PATIENT);
	a->CRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->product, (fftw_complex *)a->out, FFTW_BACKWARD, FFTW_PATIENT);
	a->mults = eq_mults(a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
}

void decalc_eq (EQ a)
{
	fftw_destroy_plan(a->CRev);
	fftw_destroy_plan(a->CFor);
	_aligned_free(a->mults);
	_aligned_free(a->product);
	_aligned_free(a->infilt);
}

EQ create_eq (int run, int size, double *in, double *out, int nfreqs, double* F, double* G, int ctfmode, int method, int samplerate)
{
	EQ a = (EQ) malloc0 (sizeof (eq));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->nfreqs = nfreqs;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	memcpy (a->F, F, (nfreqs + 1) * sizeof (double));
	memcpy (a->G, G, (nfreqs + 1) * sizeof (double));
	a->ctfmode = ctfmode;
	a->method = method;
	a->samplerate = (double)samplerate;
	calc_eq (a);
	return a;
}

void destroy_eq (EQ a)
{
	decalc_eq (a);
	_aligned_free (a->G);
	_aligned_free (a->F);
	_aligned_free (a);
}

void flush_eq (EQ a)
{
	memset (a->infilt, 0, 2 * a->size * sizeof (complex));
}

void xeq (EQ a)
{
	int i;
	double I, Q;
	if (a->run)
	{
		memcpy (&(a->infilt[2 * a->size]), a->in, a->size * sizeof (complex));
		fftw_execute (a->CFor);
		for (i = 0; i < 2 * a->size; i++)
		{
			I = a->product[2 * i + 0];
			Q = a->product[2 * i + 1];
			a->product[2 * i + 0] = I * a->mults[2 * i + 0] - Q * a->mults[2 * i + 1];
			a->product[2 * i + 1] = I * a->mults[2 * i + 1] + Q * a->mults[2 * i + 0];
		}
		fftw_execute (a->CRev);
		memcpy (a->infilt, &(a->infilt[2 * a->size]), a->size * sizeof(complex));
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

void setBuffers_eq (EQ a, double* in, double* out)
{
	decalc_eq (a);
	a->in = in;
	a->out = out;
	calc_eq (a);
}

void setSamplerate_eq (EQ a, int rate)
{
	decalc_eq (a);
	a->samplerate = rate;
	calc_eq (a);
}

void setSize_eq (EQ a, int size)
{
	decalc_eq (a);
	a->size = size;
	calc_eq (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXAEQRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].eq.p->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEQProfile (int channel, int nfreqs, double* F, double* G)
{
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].eq.p;
	_aligned_free (a->G);
	_aligned_free (a->F);
	a->nfreqs = nfreqs;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	memcpy (a->F, F, (nfreqs + 1) * sizeof (double));
	memcpy (a->G, G, (nfreqs + 1) * sizeof (double));
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEQCtfmode (int channel, int mode)
{
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].eq.p;
	a->ctfmode = mode;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEQMethod (int channel, int method)
{
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].eq.p;
	a->method = method;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAGrphEQ (int channel, int *rxeq)
{	// three band equalizer (legacy compatibility)
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].eq.p;
	_aligned_free (a->G);
	_aligned_free (a->F);
	a->nfreqs = 4;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->F[1] =  150.0;
	a->F[2] =  400.0;
	a->F[3] = 1500.0;
	a->F[4] = 6000.0;
	a->G[0] = (double)rxeq[0];
	a->G[1] = (double)rxeq[1];
	a->G[2] = (double)rxeq[1];
	a->G[3] = (double)rxeq[2];
	a->G[4] = (double)rxeq[3];
	a->ctfmode = 0;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAGrphEQ10 (int channel, int *rxeq)
{	// ten band equalizer (legacy compatibility)
	EQ a;
	int i;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].eq.p;
	_aligned_free (a->G);
	_aligned_free (a->F);
	a->nfreqs = 10;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->F[1]  =    32.0;
	a->F[2]  =    63.0;
	a->F[3]  =   125.0;
	a->F[4]  =   250.0;
	a->F[5]  =   500.0;
	a->F[6]  =  1000.0;
	a->F[7]  =  2000.0;
	a->F[8]  =  4000.0;
	a->F[9]  =  8000.0;
	a->F[10] = 16000.0;
	for (i = 0; i <= a->nfreqs; i++)
		a->G[i] = (double)rxeq[i];
	a->ctfmode = 0;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetTXAEQRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	txa[channel].eq.p->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAEQProfile (int channel, int nfreqs, double* F, double* G)
{
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].eq.p;
	_aligned_free (a->G);
	_aligned_free (a->F);
	a->nfreqs = nfreqs;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	memcpy (a->F, F, (nfreqs + 1) * sizeof (double));
	memcpy (a->G, G, (nfreqs + 1) * sizeof (double));
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAEQCtfmode (int channel, int mode)
{
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].eq.p;
	a->ctfmode = mode;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAEQMethod (int channel, int method)
{
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].eq.p;
	a->method = method;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAGrphEQ (int channel, int *txeq)
{	// three band equalizer (legacy compatibility)
	EQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].eq.p;
	_aligned_free (a->G);
	_aligned_free (a->F);
	a->nfreqs = 4;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->F[1] =  150.0;
	a->F[2] =  400.0;
	a->F[3] = 1500.0;
	a->F[4] = 6000.0;
	a->G[0] = (double)txeq[0];
	a->G[1] = (double)txeq[1];
	a->G[2] = (double)txeq[1];
	a->G[3] = (double)txeq[2];
	a->G[4] = (double)txeq[3];
	a->ctfmode = 0;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAGrphEQ10 (int channel, int *txeq)
{	// ten band equalizer (legacy compatibility)
	EQ a;
	int i;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].eq.p;
	_aligned_free (a->G);
	_aligned_free (a->F);
	a->nfreqs = 10;
	a->F = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->G = (double *) malloc0 ((a->nfreqs + 1) * sizeof (double));
	a->F[1]  =    32.0;
	a->F[2]  =    63.0;
	a->F[3]  =   125.0;
	a->F[4]  =   250.0;
	a->F[5]  =   500.0;
	a->F[6]  =  1000.0;
	a->F[7]  =  2000.0;
	a->F[8]  =  4000.0;
	a->F[9]  =  8000.0;
	a->F[10] = 16000.0;
	for (i = 0; i <= a->nfreqs; i++)
		a->G[i] = (double)txeq[i];
	a->ctfmode = 0;
	_aligned_free (a->mults);
	a->mults = eq_mults (a->size, a->nfreqs, a->F, a->G, a->samplerate, a->scale, a->ctfmode, a->method);
	LeaveCriticalSection (&ch[channel].csDSP);
}