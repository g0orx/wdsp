/*  fmmod.c

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

void calc_fmmod (FMMOD a)
{
	double* impulse;
	// ctcss gen
	a->tscale = 1.0 / (1.0 + a->ctcss_level);
	a->tphase = 0.0;
	a->tdelta = TWOPI * a->ctcss_freq / a->samplerate;
	// mod
	a->sphase = 0.0;
	a->sdelta = TWOPI * a->deviation / a->samplerate;
	// bandpass
	a->bp_fc = a->deviation + a->f_high;
	impulse = fir_bandpass(a->size + 1, -a->bp_fc, +a->bp_fc, a->samplerate, 0, 1, 1.0 / (2 * a->size));
	a->bp_mults = fftcv_mults(2 * a->size, impulse);
	a->bp_infilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->bp_product = (double *)malloc0(2 * a->size * sizeof(complex));
	a->bp_CFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->bp_infilt, (fftw_complex *)a->bp_product, FFTW_FORWARD, FFTW_PATIENT);
	a->bp_CRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->bp_product, (fftw_complex *)a->out, FFTW_BACKWARD, FFTW_PATIENT);
	_aligned_free(impulse);
}

void decalc_fmmod (FMMOD a)
{
	fftw_destroy_plan(a->bp_CRev);
	fftw_destroy_plan(a->bp_CFor);
	_aligned_free(a->bp_product);
	_aligned_free(a->bp_infilt);
	_aligned_free(a->bp_mults);
}

FMMOD create_fmmod (int run, int size, double* in, double* out, int rate, double dev, double f_low, double f_high, 
	int ctcss_run, double ctcss_level, double ctcss_freq, int bp_run)
{
	FMMOD a = (FMMOD) malloc0 (sizeof (fmmod));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->samplerate = (double)rate;
	a->deviation = dev;
	a->f_low = f_low;
	a->f_high = f_high;
	a->ctcss_run = ctcss_run;
	a->ctcss_level = ctcss_level;
	a->ctcss_freq = ctcss_freq;
	a->bp_run = bp_run;
	calc_fmmod (a);
	return a;
}

void destroy_fmmod (FMMOD a)
{
	decalc_fmmod (a);
	_aligned_free (a);
}

void flush_fmmod (FMMOD a)
{
	memset (a->bp_infilt, 0, 2 * a->size * sizeof (complex));
	a->tphase = 0.0;
	a->sphase = 0.0;
}

void xfmmod (FMMOD a)
{
	int i;
	double I, Q;
	double dp, magdp, peak;
	if (a->run)
	{
		peak = 0.0;
		for (i = 0; i < a->size; i++)
		{
			if (a->ctcss_run)
			{
				a->tphase += a->tdelta;
				if (a->tphase >= TWOPI) a->tphase -= TWOPI;
				a->out[2 * i + 0] = a->tscale * (a->in[2 * i + 0] + a->ctcss_level * cos (a->tphase));
			}
			dp = a->out[2 * i + 0] * a->sdelta;
			a->sphase += dp;
			if (a->sphase >= TWOPI) a->sphase -= TWOPI;
			if (a->sphase <   0.0 ) a->sphase += TWOPI;
			a->out[2 * i + 0] = 0.7071 * cos (a->sphase);
			a->out[2 * i + 1] = 0.7071 * sin (a->sphase);
			if ((magdp = dp) < 0.0) magdp = - magdp;
			if (magdp > peak) peak = magdp;
		}
		//print_deviation ("peakdev.txt", peak, a->samplerate);
		if (a->bp_run)
		{
			memcpy (&(a->bp_infilt[2 * a->size]), a->out, a->size * sizeof (complex));
			fftw_execute (a->bp_CFor);
			for (i = 0; i < 2 * a->size; i++)
			{
				I = a->bp_product[2 * i + 0];
				Q = a->bp_product[2 * i + 1];
				a->bp_product[2 * i + 0] = I * a->bp_mults[2 * i + 0] - Q * a->bp_mults[2 * i + 1];
				a->bp_product[2 * i + 1] = I * a->bp_mults[2 * i + 1] + Q * a->bp_mults[2 * i + 0];
			}
			fftw_execute (a->bp_CRev);
			memcpy (a->bp_infilt, &(a->bp_infilt[2 * a->size]), a->size * sizeof(complex));
		}
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

setBuffers_fmmod (FMMOD a, double* in, double* out)
{
	decalc_fmmod (a);
	a->in = in;
	a->out = out;
	calc_fmmod (a);
}

setSamplerate_fmmod (FMMOD a, int rate)
{
	decalc_fmmod (a);
	a->samplerate = rate;
	calc_fmmod (a);
}

setSize_fmmod (FMMOD a, int size)
{
	decalc_fmmod (a);
	a->size = size;
	calc_fmmod (a);
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetTXAFMDeviation (int channel, double deviation)
{
	double* impulse;
	FMMOD a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].fmmod.p;
	a->deviation = deviation;
	// mod
	a->sphase = 0.0;
	a->sdelta = TWOPI * a->deviation / a->samplerate;
	// bandpass
	a->bp_fc = a->deviation + a->f_high;
	_aligned_free (a->bp_mults);
	impulse = fir_bandpass (a->size + 1, -a->bp_fc, +a->bp_fc, a->samplerate, 0, 1, 1.0 / (2 * a->size));
	a->bp_mults = fftcv_mults (2 * a->size, impulse);
	_aligned_free (impulse);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXACTCSSFreq (int channel, double freq)
{
	FMMOD a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].fmmod.p;
	a->ctcss_freq = freq;
	a->tphase = 0.0;
	a->tdelta = TWOPI * a->ctcss_freq / a->samplerate;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXACTCSSRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	txa[channel].fmmod.p->ctcss_run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}