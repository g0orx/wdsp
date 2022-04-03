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
	// CTCSS Removal
	a->sntch = create_snotch(1, a->size, a->out, a->out, (int)a->rate, a->ctcss_freq, 0.0002);
}

void decalc_fmd (FMD a)
{
	destroy_snotch(a->sntch);
}

FMD create_fmd( int run, int size, real* in, real* out, int rate, real deviation, real f_low, real f_high, 
	real fmin, real fmax, real zeta, real omegaN, real tau, real afgain, int sntch_run, real ctcss_freq, int nc_de, int mp_de, int nc_aud, int mp_aud)
{
	FMD a = (FMD) malloc0 (sizeof (fmd));
	real* impulse;
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = (real)rate;
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
	a->nc_de = nc_de;
	a->mp_de = mp_de;
	a->nc_aud = nc_aud;
	a->mp_aud = mp_aud;
	calc_fmd (a);
	// de-emphasis filter
	a->audio = (real *) malloc0 (a->size * sizeof (complex));
	impulse = fc_impulse (a->nc_de, a->f_low, a->f_high, +20.0 * log10(a->f_high / a->f_low), 0.0, 1, a->rate, 1.0 / (2.0 * a->size), 0, 0);
	a->pde = create_fircore (a->size, a->audio, a->out, a->nc_de, a->mp_de, impulse);
	_aligned_free (impulse);
	// audio filter
	impulse = fir_bandpass(a->nc_aud, 0.8 * a->f_low, 1.1 * a->f_high, a->rate, 0, 1, a->afgain / (2.0 * a->size));
	a->paud = create_fircore (a->size, a->out, a->out, a->nc_aud, a->mp_aud, impulse);
	_aligned_free (impulse);
	return a;
}

void destroy_fmd (FMD a)
{
	destroy_fircore (a->paud);
	destroy_fircore (a->pde);
	_aligned_free (a->audio);
	decalc_fmd (a);
	_aligned_free (a);
}

void flush_fmd (FMD a)
{
	memset (a->audio, 0, a->size * sizeof (complex));
	flush_fircore (a->pde);
	flush_fircore (a->paud);
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
		real det, del_out;
		real vco[2], corr[2];
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
		xfircore (a->pde);
		// audio filter
		xfircore (a->paud);
		// CTCSS Removal
		xsnotch (a->sntch);
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

void setBuffers_fmd (FMD a, real* in, real* out)
{
	decalc_fmd (a);
	a->in = in;
	a->out = out;
	calc_fmd (a);
	setBuffers_fircore (a->pde,  a->audio, a->out);
	setBuffers_fircore (a->paud, a->out, a->out);
}

void setSamplerate_fmd (FMD a, int rate)
{
	real* impulse;
	decalc_fmd (a);
	a->rate = rate;
	calc_fmd (a);
	// de-emphasis filter
	impulse = fc_impulse (a->nc_de, a->f_low, a->f_high, +20.0 * log10(a->f_high / a->f_low), 0.0, 1, a->rate, 1.0 / (2.0 * a->size), 0, 0);
	setImpulse_fircore (a->pde, impulse, 1);
	_aligned_free (impulse);
	// audio filter
	impulse = fir_bandpass(a->nc_aud, 0.8 * a->f_low, 1.1 * a->f_high, a->rate, 0, 1, a->afgain / (2.0 * a->size));
	setImpulse_fircore (a->paud, impulse, 1);
	_aligned_free (impulse);
}

void setSize_fmd (FMD a, int size)
{
	real* impulse;
	decalc_fmd (a);
	_aligned_free (a->audio);
	a->size = size;
	calc_fmd (a);
	a->audio = (real *) malloc0 (a->size * sizeof (complex));
	// de-emphasis filter
	destroy_fircore (a->pde);
	impulse = fc_impulse (a->nc_de, a->f_low, a->f_high, +20.0 * log10(a->f_high / a->f_low), 0.0, 1, a->rate, 1.0 / (2.0 * a->size), 0, 0);
	a->pde = create_fircore (a->size, a->audio, a->out, a->nc_de, a->mp_de, impulse);
	_aligned_free (impulse);
	// audio filter
	destroy_fircore (a->paud);
	impulse = fir_bandpass(a->nc_aud, 0.8 * a->f_low, 1.1 * a->f_high, a->rate, 0, 1, a->afgain / (2.0 * a->size));
	a->paud = create_fircore (a->size, a->out, a->out, a->nc_aud, a->mp_aud, impulse);
	_aligned_free (impulse);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXAFMDeviation (int channel, real deviation)
{
	FMD a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].fmd.p;
	a->deviation = deviation;
	a->again = a->rate / (a->deviation * TWOPI);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXACTCSSFreq (int channel, real freq)
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

PORT
void SetRXAFMNCde (int channel, int nc)
{
	FMD a;
	real* impulse;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].fmd.p;
	if (a->nc_de != nc)
	{
		a->nc_de = nc;
		impulse = fc_impulse (a->nc_de, a->f_low, a->f_high, +20.0 * log10(a->f_high / a->f_low), 0.0, 1, a->rate, 1.0 / (2.0 * a->size), 0, 0);
		setNc_fircore (a->pde, a->nc_de, impulse);
		_aligned_free (impulse);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAFMMPde (int channel, int mp)
{
	FMD a;
	a = rxa[channel].fmd.p;
	if (a->mp_de != mp)
	{
		a->mp_de = mp;
		setMp_fircore (a->pde, a->mp_de);
	}
}

PORT
void SetRXAFMNCaud (int channel, int nc)
{
	FMD a;
	real* impulse;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].fmd.p;
	if (a->nc_aud != nc)
	{
		a->nc_aud = nc;
		impulse = fir_bandpass(a->nc_aud, 0.8 * a->f_low, 1.1 * a->f_high, a->rate, 0, 1, a->afgain / (2.0 * a->size));
		setNc_fircore (a->paud, a->nc_aud, impulse);
		_aligned_free (impulse);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAFMMPaud (int channel, int mp)
{
	FMD a;
	a = rxa[channel].fmd.p;
	if (a->mp_aud != mp)
	{
		a->mp_aud = mp;
		setMp_fircore (a->paud, a->mp_aud);
	}
}
