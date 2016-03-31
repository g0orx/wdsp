/*  fmd.c

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

void calc_fmd (FMD a)
{
	double* impulse;
	// pll
	a->omega_min = TWOPI * a->fmin / a->rate;
	a->omega_max = TWOPI * a->fmax / a->rate;
	a->g1 = 1.0 - exp(-2.0 * a->omegaN * a->zeta / a->rate);
	a->g2 = -a->g1 + 2.0 * (1 - exp(-a->omegaN * a->zeta / a->rate) * cos(a->omegaN / a->rate * sqrt(1.0 - a->zeta * a->zeta)));
	a->phs = 0.0;
	a->fil_out = 0.0;
	a->omega = 0.0;
	a->pllpole = a->omegaN * sqrt(2.0 * a->zeta * a->zeta + 1.0 + sqrt((2.0 * a->zeta * a->zeta + 1.0) * (2.0 * a->zeta * a->zeta + 1.0) + 1)) / TWOPI;
	// dc removal
	a->mtau = exp(-1.0 / (a->rate * a->tau));
	a->onem_mtau = 1.0 - a->mtau;
	a->fmdc = 0.0;
	// pll audio gain
	a->again = a->rate / (a->deviation * TWOPI);
	a->audio = (double *)malloc0(a->size * sizeof(complex));
	// de-emphasis filter
	a->mults = fc_mults(a->size, a->f_low, a->f_high, +20.0 * log10(a->f_high / a->f_low), 0.0, 1, a->rate, 1.0 / (2.0 * a->size), 0, 1);
	a->infilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->product = (double *)malloc0(2 * a->size * sizeof(complex));
	a->outfilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->CFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->infilt, (fftw_complex *)a->product, FFTW_FORWARD, FFTW_PATIENT);
	a->CRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->product, (fftw_complex *)a->outfilt, FFTW_BACKWARD, FFTW_PATIENT);
	// audio filter
	impulse = fir_bandpass(a->size + 1, 0.8 * a->f_low, 1.1 * a->f_high, a->rate, 0, 1, a->afgain / (2.0 * a->size));
	a->amults = fftcv_mults(2 * a->size, impulse);
	a->ainfilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->aproduct = (double *)malloc0(2 * a->size * sizeof(complex));
	a->aCFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->ainfilt, (fftw_complex *)a->aproduct, FFTW_FORWARD, FFTW_PATIENT);
	a->aCRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->aproduct, (fftw_complex *)a->out, FFTW_BACKWARD, FFTW_PATIENT);
	_aligned_free(impulse);
	// CTCSS Removal
	a->sntch = create_snotch(1, a->size, a->out, a->out, (int)a->rate, a->ctcss_freq, 0.0002);
}

void decalc_fmd (FMD a)
{
	destroy_snotch(a->sntch);
	fftw_destroy_plan(a->aCRev);
	fftw_destroy_plan(a->aCFor);
	_aligned_free(a->aproduct);
	_aligned_free(a->ainfilt);
	_aligned_free(a->amults);
	fftw_destroy_plan(a->CRev);
	fftw_destroy_plan(a->CFor);
	_aligned_free(a->outfilt);
	_aligned_free(a->product);
	_aligned_free(a->infilt);
	_aligned_free(a->mults);
	_aligned_free(a->audio);
}

FMD create_fmd( int run, int size, double* in, double* out, int rate, double deviation, double f_low, double f_high, 
	double fmin, double fmax, double zeta, double omegaN, double tau, double afgain, int sntch_run, double ctcss_freq)
{
	FMD a = (FMD) malloc0 (sizeof (fmd));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = (double)rate;
	a->deviation = deviation;
	a->f_low = f_low;
	a->f_high = f_high;
	a->fmin = fmin;
	a->fmax = fmax;
	a->zeta = zeta;
	a->omegaN = omegaN;
	a->tau = tau;
	a->afgain = afgain;
	a->sntch_run = sntch_run;
	a->ctcss_freq = ctcss_freq;
	calc_fmd (a);
	return a;
}

void destroy_fmd (FMD a)
{
	decalc_fmd (a);
	_aligned_free (a);
}

void flush_fmd (FMD a)
{
	memset (a->audio,   0,     a->size * sizeof (complex));
	memset (a->infilt,  0, 2 * a->size * sizeof (complex));
	memset (a->ainfilt, 0, 2 * a->size * sizeof (complex));
	a->phs = 0.0;
	a->fil_out = 0.0;
	a->omega = 0.0;
	a->fmdc = 0.0;
	flush_snotch (a->sntch);
}

void xfmd (FMD a)
{
	if (a->run)
	{
		int i;
		double I, Q;
		double det, del_out;
		double vco[2], corr[2];
		for (i = 0; i < a->size; i++)
		{
			// pll
			vco[0]  = cos (a->phs);
			vco[1]  = sin (a->phs);
			corr[0] = + a->in[2 * i + 0] * vco[0] + a->in[2 * i + 1] * vco[1];
			corr[1] = - a->in[2 * i + 0] * vco[1] + a->in[2 * i + 1] * vco[0];
			if ((corr[0] == 0.0) && (corr[1] == 0.0)) corr[0] = 1.0;
			det = atan2 (corr[1], corr[0]);
			del_out = a->fil_out;
			a->omega += a->g2 * det;
			if (a->omega < a->omega_min) a->omega = a->omega_min;
			if (a->omega > a->omega_max) a->omega = a->omega_max;
			a->fil_out = a->g1 * det + a->omega;
			a->phs += del_out;
			while (a->phs >= TWOPI) a->phs -= TWOPI;
			while (a->phs < 0.0) a->phs += TWOPI;
			// dc removal, gain, & demod output
			a->fmdc = a->mtau * a->fmdc + a->onem_mtau * a->fil_out;
			a->audio[2 * i + 0] = a->again * (a->fil_out - a->fmdc);
			a->audio[2 * i + 1] = a->audio[2 * i + 0];
		}
		// de-emphasis
		memcpy (&(a->infilt[2 * a->size]), a->audio, a->size * sizeof (complex));
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
		// audio filter
		memcpy (&(a->ainfilt[2 * a->size]), a->outfilt, a->size * sizeof (complex));
		fftw_execute (a->aCFor);
		for (i = 0; i < 2 * a->size; i++)
		{
			I = a->aproduct[2 * i + 0];
			Q = a->aproduct[2 * i + 1];
			a->aproduct[2 * i + 0] = I * a->amults[2 * i + 0] - Q * a->amults[2 * i + 1];
			a->aproduct[2 * i + 1] = I * a->amults[2 * i + 1] + Q * a->amults[2 * i + 0];
		}
		fftw_execute (a->aCRev);
		memcpy (a->ainfilt, &(a->ainfilt[2 * a->size]), a->size * sizeof(complex));
		// CTCSS Removal
		xsnotch (a->sntch);
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

void setBuffers_fmd (FMD a, double* in, double* out)
{
	decalc_fmd (a);
	a->in = in;
	a->out = out;
	calc_fmd (a);
}

void setSamplerate_fmd (FMD a, int rate)
{
	decalc_fmd (a);
	a->rate = rate;
	calc_fmd (a);
}

void setSize_fmd (FMD a, int size)
{
	decalc_fmd (a);
	a->size = size;
	calc_fmd (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXAFMDeviation (int channel, double deviation)
{
	FMD a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].fmd.p;
	a->deviation = deviation;
	a->again = a->rate / (a->deviation * TWOPI);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXACTCSSFreq (int channel, double freq)
{
	FMD a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].fmd.p;
	a->ctcss_freq = freq;
	SetSNCTCSSFreq (a->sntch, a->ctcss_freq);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXACTCSSRun (int channel, int run)
{
	FMD a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].fmd.p;
	a->sntch_run = run;
	SetSNCTCSSRun (a->sntch, a->sntch_run);
	LeaveCriticalSection (&ch[channel].csDSP);
}