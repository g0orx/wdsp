/*  bandpass.c

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

void calc_bandpass (BANDPASS a)
{
	double* impulse;
	a->infilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->product = (double *)malloc0(2 * a->size * sizeof(complex));
	impulse = fir_bandpass(a->size + 1, a->f_low, a->f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
	a->mults = fftcv_mults(2 * a->size, impulse);
	a->CFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->infilt, (fftw_complex *)a->product, FFTW_FORWARD, FFTW_PATIENT);
	a->CRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->product, (fftw_complex *)a->out, FFTW_BACKWARD, FFTW_PATIENT);
	_aligned_free(impulse);
}

void decalc_bandpass (BANDPASS a)
{
	fftw_destroy_plan(a->CRev);
	fftw_destroy_plan(a->CFor);
	_aligned_free(a->mults);
	_aligned_free(a->product);
	_aligned_free(a->infilt);
}

BANDPASS create_bandpass (int run, int position, int size, double* in, double* out, 
	double f_low, double f_high, int samplerate, int wintype, double gain)
{
	BANDPASS a = (BANDPASS) malloc0 (sizeof (bandpass));
	a->run = run;
	a->position = position;
	a->size = size;
	a->samplerate = (double)samplerate;
	a->wintype = wintype;
	a->gain = gain;
	a->in = in;
	a->out = out;
	a->f_low = f_low;
	a->f_high = f_high;
	calc_bandpass (a);
	return a;
}

void destroy_bandpass (BANDPASS a)
{
	decalc_bandpass (a);
	_aligned_free (a);
}

void flush_bandpass (BANDPASS a)
{
	memset (a->infilt, 0, 2 * a->size * sizeof (complex));
}

void xbandpass (BANDPASS a, int pos)
{
	int i;
	double I, Q;
	if (a->run && pos == a->position)
	{
		memcpy (&(a->infilt[2 * a->size]), a->in, a->size * sizeof (complex));
		fftw_execute (a->CFor);
		for (i = 0; i < 2 * a->size; i++)
		{
			I = a->gain * a->product[2 * i + 0];
			Q = a->gain * a->product[2 * i + 1];
			a->product[2 * i + 0] = I * a->mults[2 * i + 0] - Q * a->mults[2 * i + 1];
			a->product[2 * i + 1] = I * a->mults[2 * i + 1] + Q * a->mults[2 * i + 0];
		}
		fftw_execute (a->CRev);
		memcpy (a->infilt, &(a->infilt[2 * a->size]), a->size * sizeof(complex));
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

void setBuffers_bandpass (BANDPASS a, double* in, double* out)
{
	decalc_bandpass (a);
	a->in = in;
	a->out = out;
	calc_bandpass (a);
}

void setSamplerate_bandpass (BANDPASS a, int rate)
{
	decalc_bandpass (a);
	a->samplerate = rate;
	calc_bandpass (a);
}

void setSize_bandpass (BANDPASS a, int size)
{
	decalc_bandpass (a);
	a->size = size;
	calc_bandpass (a);
}

void setFreqs_bandpass (BANDPASS a, double f_low, double f_high)
{
	decalc_bandpass (a);
	a->f_low = f_low;
	a->f_high = f_high;
	calc_bandpass (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXABandpassRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].bp1.p->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXABandpassFreqs (int channel, double f_low, double f_high)
{
	double* impulse;
	BANDPASS a1;
	EnterCriticalSection (&ch[channel].csDSP);
	a1 = rxa[channel].bp1.p;
	if ((f_low != a1->f_low) || (f_high != a1->f_high))
	{
		a1->f_low = f_low;
		a1->f_high = f_high;
		_aligned_free (a1->mults);
		impulse = fir_bandpass(a1->size + 1, f_low, f_high, a1->samplerate, a1->wintype, 1, 1.0 / (double)(2 * a1->size));
		a1->mults = fftcv_mults (2 * a1->size, impulse);
		_aligned_free (impulse);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXABandpassWindow (int channel, int wintype)
{
	double* impulse;
	BANDPASS a1;
	EnterCriticalSection (&ch[channel].csDSP);
	a1 = rxa[channel].bp1.p;
	if ((a1->wintype != wintype))
	{
		a1->wintype = wintype;
		_aligned_free (a1->mults);
		impulse = fir_bandpass(a1->size + 1, a1->f_low, a1->f_high, a1->samplerate, a1->wintype, 1, 1.0 / (double)(2 * a1->size));
		a1->mults = fftcv_mults (2 * a1->size, impulse);
		_aligned_free (impulse);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetTXABandpassRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	txa[channel].bp1.p->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXABandpassFreqs (int channel, double f_low, double f_high)
{
	double* impulse;
	BANDPASS a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].bp0.p;
	if ((f_low != a->f_low) || (f_high != a->f_high))
	{
		a->f_low = f_low;
		a->f_high = f_high;
		_aligned_free (a->mults);
		impulse = fir_bandpass(a->size + 1, f_low, f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
		a->mults = fftcv_mults (2 * a->size, impulse);
		_aligned_free (impulse);
	}
	a = txa[channel].bp1.p;
	if ((f_low != a->f_low) || (f_high != a->f_high))
	{
		a->f_low = f_low;
		a->f_high = f_high;
		_aligned_free (a->mults);
		impulse = fir_bandpass(a->size + 1, f_low, f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
		a->mults = fftcv_mults (2 * a->size, impulse);
		_aligned_free (impulse);
	}
	a = txa[channel].bp2.p;
	if ((f_low != a->f_low) || (f_high != a->f_high))
	{
		a->f_low = f_low;
		a->f_high = f_high;
		_aligned_free (a->mults);
		impulse = fir_bandpass(a->size + 1, f_low, f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
		a->mults = fftcv_mults (2 * a->size, impulse);
		_aligned_free (impulse);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXABandpassWindow (int channel, int wintype)
{
	double* impulse;
	BANDPASS a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].bp0.p;
	if (a->wintype != wintype)
	{
		a->wintype = wintype;
		_aligned_free (a->mults);
		impulse = fir_bandpass(a->size + 1, a->f_low, a->f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
		a->mults = fftcv_mults (2 * a->size, impulse);
		_aligned_free (impulse);
	}
	a = txa[channel].bp1.p;
	if (a->wintype != wintype)
	{
		a->wintype = wintype;
		_aligned_free (a->mults);
		impulse = fir_bandpass(a->size + 1, a->f_low, a->f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
		a->mults = fftcv_mults (2 * a->size, impulse);
		_aligned_free (impulse);
	}
	a = txa[channel].bp2.p;
	if (a->wintype != wintype)
	{
		a->wintype = wintype;
		_aligned_free (a->mults);
		impulse = fir_bandpass (a->size + 1, a->f_low, a->f_high, a->samplerate, a->wintype, 1, 1.0 / (double)(2 * a->size));
		a->mults = fftcv_mults (2 * a->size, impulse);
		_aligned_free (impulse);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}