/*  cfir.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2014 Warren Pratt, NR0V

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
#define _CRT_SECURE_NO_DEPRECATE
#include "comm.h"

void calc_cfir (CFIR a)
{
	a->scale = 1.0 / (double)(2 * a->size);
	a->infilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->product = (double *)malloc0(2 * a->size * sizeof(complex));
	a->CFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->infilt, (fftw_complex *)a->product, FFTW_FORWARD, FFTW_ESTIMATE);
	a->CRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->product, (fftw_complex *)a->out, FFTW_BACKWARD, FFTW_ESTIMATE);
	a->mults = cfir_mults(a->size, a->runrate, a->cicrate, a->scale, a->DD, a->R, a->Pairs, a->cutoff, a->xtype, a->xbw);
}

void decalc_cfir (CFIR a)
{
	fftw_destroy_plan(a->CRev);
	fftw_destroy_plan(a->CFor);
	_aligned_free(a->mults);
	_aligned_free(a->product);
	_aligned_free(a->infilt);
}

CFIR create_cfir (int run, int size, double* in, double* out, int runrate, int cicrate, int DD, int R, int Pairs, double cutoff, int xtype, double xbw)
//	run:  0 - no action; 1 - operate
//	size:  number of complex samples in an input buffer to the CFIR filter
//	in:  pointer to the input buffer
//	out:  pointer to the output buffer
//	rate:  samplerate
//	DD:  differential delay of the CIC to be compensated (usually 1 or 2)
//	R:  interpolation factor of CIC
//	Pairs:  number of comb-integrator pairs in the CIC
//	cutoff:  cutoff frequency
//  xtype:  0 - fourth power transition; 1 - raised cosine transition
//  xbw:  width of raised cosine transition
{
	CFIR a = (CFIR) malloc0 (sizeof (cfir));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->runrate = runrate;
	a->cicrate = cicrate;
	a->DD = DD;
	a->R = R;
	a->Pairs = Pairs;
	a->cutoff = cutoff;
	a->xtype = xtype;
	a->xbw = xbw;
	calc_cfir (a);
	return a;
}

void destroy_cfir (CFIR a)
{
	decalc_cfir (a);
	_aligned_free (a);
}

void flush_cfir (CFIR a)
{
	memset (a->infilt, 0, 2 * a->size * sizeof (complex));
}

void xcfir (CFIR a)
{
	if (a->run)
	{
		int i;
		double I, Q;
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

void setBuffers_cfir (CFIR a, double* in, double* out)
{
	decalc_cfir (a);
	a->in = in;
	a->out = out;
	calc_cfir (a);
}

void setSamplerate_cfir (CFIR a, int rate)
{
	decalc_cfir (a);
	a->runrate = rate;
	calc_cfir (a);
}

void setSize_cfir (CFIR a, int size)
{
	decalc_cfir (a);
	a->size = size;
	calc_cfir (a);
}

void setOutRate_cfir (CFIR a, int rate)
{
	decalc_cfir (a);
	a->cicrate = rate;
	calc_cfir (a);
}


double *fir_read (int N, const char *filename, int rtype, double scale)
	// N = number of real or complex coefficients (see rtype)
	// *filename = filename
	// rtype = 0:  real coefficients
	// rtype = 1:  complex coefficients
	// scale = a scale factor that will be applied to the returned coefficients;
	//		if this is not needed, set it to 1.0
	// NOTE:  The number of values in the file must NOT exceed those implied by N and rtype
{
	FILE *file;
	int i;
	double I, Q;
	double *c_impulse = (double *) malloc0 (N * sizeof (complex));
	file = fopen (filename, "r");
	for (i = 0; i < N; i++)
	{
		// read in the complex impulse response
		// NOTE:  IF the freq response is symmetrical about 0, the imag coeffs will all be zero.
		switch (rtype)
		{
		case 0:
			fscanf (file, "%le", &I);
			c_impulse[i] = + scale * I;
			break;
		case 1:
			fscanf (file, "%le", &I);
			fscanf (file, "%le", &Q);
			c_impulse[2 * i + 0] = + scale * I;
			c_impulse[2 * i + 1] = - scale * Q;
			break;
		}
	}
	fclose (file);
	return c_impulse;
}

void print_response (const char* filename, int N, double* response)
{
	FILE *file;
	int i;
	file = fopen (filename, "w");
	for (i = 0; i < N; i++)
		fprintf (file, "%.17e\n", response[i]);
	fflush (file);
	fclose (file);
}

double* cfir_impulse (int N, int DD, int R, int Pairs, double runrate, double cicrate, double cutoff, int xtype, double xbw, int rtype, double scale)
{
	// N:		number of impulse response samples
	// DD:		differential delay used in the CIC filter
	// R:		interpolation / decimation factor of the CIC
	// Pairs:	number of comb-integrator pairs in the CIC
	// runrate:	sample rate at which this filter is to run (assumes there may be flat interp. between this filter and the CIC)
	// cicrate: sample rate at interface to CIC
	// cutoff:	cutoff frequency
	// xtype:	transition type, 0 for 4th-power rolloff, 1 for raised cosine
	// xbw:		transition bandwidth for raised cosine
	// rtype:	0 for real output, 1 for complex output
	// scale:	scale factor to be applied to the output
	int i, j;
	double tmp, local_scale, ri, mag, fn;
	double* impulse;
	double* A = (double *) malloc0 (N * sizeof (double));
	double ft = cutoff / cicrate;										// normalized cutoff frequency
	int u_samps = (N + 1) / 2;											// number of unique samples,  OK for odd or even N
	int c_samps = (int)(cutoff / runrate * N) + (N + 1) / 2 - N / 2;	// number of unique samples within bandpass, OK for odd or even N
	int x_samps = (int)(xbw / runrate * N);								// number of unique samples in transition region, OK for odd or even N
	double offset = 0.5 - 0.5 * (double)((N + 1) / 2 - N / 2);			// sample offset from center, OK for odd or even N
	double* xistion = (double *) malloc0 ((x_samps + 1) * sizeof (double));
	double delta = PI / (double)x_samps;
	double L = cicrate / runrate;
	double phs = 0.0;
	for (i = 0; i <= x_samps; i++)
	{
		xistion[i] = 0.5 * (cos (phs) + 1.0);
		phs += delta;
	}
	if ((tmp = DD * R * sin (PI * ft / R) / sin (PI * DD * ft)) < 0.0)	//normalize by peak gain
		tmp = -tmp;
	local_scale = scale / pow (tmp, Pairs);
	if (xtype == 0)
	{
		for (i = 0, ri = offset; i < u_samps; i++, ri += 1.0)
		{
			fn = ri / (L * (double)N);
			if (fn <= ft)
			{
				if (fn == 0.0) tmp = 1.0;
				else if ((tmp = DD * R * sin (PI * fn / R) / sin (PI * DD * fn)) < 0.0)
					tmp = -tmp;
				mag = pow (tmp, Pairs) * local_scale;
			}
			else
				mag *= (ft * ft * ft * ft) / (fn * fn * fn * fn);
			A[i] = mag; 
		}
	}
	else if (xtype == 1)
	{
		for (i = 0, ri = offset; i < u_samps; i++, ri += 1.0)
		{
			fn = ri / (L *(double)N);
			if (i < c_samps)
			{
				if (fn == 0.0) tmp = 1.0;
				else if ((tmp = DD * R * sin (PI * fn / R) / sin (PI * DD * fn)) < 0.0)
					tmp = -tmp;
				mag = pow (tmp, Pairs) * local_scale;
				A[i] = mag;
			}
			else if ( i >= c_samps && i <= c_samps + x_samps)
				A[i] = mag * xistion[i - c_samps];
			else
				A[i] = 0.0;
		}
	}
	if (N & 1)
		for (i = u_samps, j = 2; i < N; i++, j++)
			A[i] = A[u_samps - j];
	else
		for (i = u_samps, j = 1; i < N; i++, j++)
			A[i] = A[u_samps - j];

	// print_response ("cfirResponse.txt", N, A);
	impulse = fir_fsamp(N, A, rtype, 1.0, -1);
	// print_impulse ("cfirImpulse.txt", N, impulse, 1, 0);
	_aligned_free (A);
	return impulse;
}

double* cfir_mults (int size, int runrate, int cicrate, double scale, int DD, int R, int Pairs, double cutoff, int xtype, double xbw)
{
	// size = input/output size of the FFT-Convolution Filter
	double* impulse;
	double* mults;
	impulse = cfir_impulse (size + 1, DD, R, Pairs, (double)runrate, (double)cicrate, cutoff, xtype, xbw, 1, scale);
	mults = fftcv_mults(2 * size, impulse);
	_aligned_free (impulse);
	return mults;
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT void
SetTXACFIRRun (int channel, int run)
{
	EnterCriticalSection(&ch[channel].csDSP);
	txa[channel].cfir.p->run = run;
	LeaveCriticalSection(&ch[channel].csDSP);
}