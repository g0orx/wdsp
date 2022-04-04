/*  iir.c

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

#include "comm.h"

/********************************************************************************************************
*																										*
*											Bi-Quad Notch												*
*																										*
********************************************************************************************************/

void calc_snotch (SNOTCH a)
{
	real fn, qk, qr, csn;
	fn = a->f / (real)a->rate;
	csn = cos (TWOPI * fn);
	qr = 1.0 - 3.0 * a->bw;
	qk = (1.0 - 2.0 * qr * csn + qr * qr) / (2.0 * (1.0 - csn));
	a->a0 = + qk;
	a->a1 = - 2.0 * qk * csn;
	a->a2 = + qk;
	a->b1 = + 2.0 * qr * csn;
	a->b2 = - qr * qr;
	flush_snotch (a);
}

SNOTCH create_snotch (int run, int size, real* in, real* out, int rate, real f, real bw)
{
	SNOTCH a = (SNOTCH) malloc0 (sizeof (snotch));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = rate;
	a->f = f;
	a->bw = bw;
	InitializeCriticalSectionAndSpinCount ( &a->cs_update, 2500 );
	calc_snotch (a);
	return a;
}

void destroy_snotch (SNOTCH a)
{
	DeleteCriticalSection (&a->cs_update);
	_aligned_free (a);
}

void flush_snotch (SNOTCH a)
{
	a->x1 = a->x2 = a->y1 = a->y2 = 0.0;
}

void xsnotch (SNOTCH a)
{
	EnterCriticalSection (&a->cs_update);
	if (a->run)
	{
		int i;
		for (i = 0; i < a->size; i++)
		{
			a->x0 = a->in[2 * i + 0];
			a->out[2 * i + 0] = a->a0 * a->x0 + a->a1 * a->x1 + a->a2 * a->x2 + a->b1 * a->y1 + a->b2 * a->y2;
			a->y2 = a->y1;
			a->y1 = a->out[2 * i + 0];
			a->x2 = a->x1;
			a->x1 = a->x0;
		}
	}
	else if (a->out != a->in)
		memcpy (a->out, a->in, a->size * sizeof (complex));
	LeaveCriticalSection (&a->cs_update);
}

void setBuffers_snotch (SNOTCH a, real* in, real* out)
{
	a->in = in;
	a->out = out;
}

void setSamplerate_snotch (SNOTCH a, int rate)
{
	a->rate = rate;
	calc_snotch (a);
}

void setSize_snotch (SNOTCH a, int size)
{
	a->size = size;
	flush_snotch (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

void SetSNCTCSSFreq (SNOTCH a, real freq)
{
	EnterCriticalSection (&a->cs_update);
	a->f = freq;
	calc_snotch (a);
	LeaveCriticalSection (&a->cs_update);
}

void SetSNCTCSSRun (SNOTCH a, int run)
{
	EnterCriticalSection (&a->cs_update);
	a->run = run;
	LeaveCriticalSection (&a->cs_update);
}


/********************************************************************************************************
*																										*
*											Complex Bi-Quad Peaking										*
*																										*
********************************************************************************************************/

void calc_speak (SPEAK a)
{
	real ratio;	
	real f_corr, g_corr, bw_corr, bw_parm, A, f_min;
	
	switch (a->design)
	{
	case 0:
		ratio = a->bw / a->f;
		switch (a->nstages)
		{
		case 4:
			bw_parm = 2.4;
			f_corr  = 1.0 - 0.160 * ratio + 1.440 * ratio * ratio;
			g_corr = 1.0 - 1.003 * ratio + 3.990 * ratio * ratio;
			break;
		default:
			bw_parm = 1.0;
			f_corr  = 1.0;
			g_corr = 1.0;
			break;
		}
		{
			real fn, qk, qr, csn;
			a->fgain = a->gain / g_corr;
			fn = a->f / (real)a->rate / f_corr;
			csn = cos (TWOPI * fn);
			qr = 1.0 - 3.0 * a->bw / (real)a->rate * bw_parm;
			qk = (1.0 - 2.0 * qr * csn + qr * qr) / (2.0 * (1.0 - csn));
			a->a0 = 1.0 - qk;
			a->a1 = 2.0 * (qk - qr) * csn;
			a->a2 = qr * qr - qk;
			a->b1 = 2.0 * qr * csn;
			a->b2 = - qr * qr;
		}
		break;

	case 1:
		if (a->f < 200.0) a->f = 200.0;
		ratio = a->bw / a->f;
		switch (a->nstages)
		{
		case 4:
			bw_parm = 5.0;
			bw_corr = 1.13 * ratio - 0.956 * ratio * ratio;
			A = 2.5;
			f_min = 50.0;
			break;
		default:
			bw_parm = 1.0;
			bw_corr  = 1.0;
			g_corr = 1.0;
			A = 2.5;
			f_min = 50.0;
			break;
		}
		{
			real w0, sn, c, den;
			if (a->f < f_min) a->f = f_min;
			w0 = TWOPI * a->f / (real)a->rate;
			sn = sin (w0);
			a->cbw = bw_corr * a->f;
			c = sn * sinh(0.5 * log((a->f + 0.5 * a->cbw * bw_parm) / (a->f - 0.5 * a->cbw * bw_parm)) * w0 / sn);
			den = 1.0 + c / A;
			a->a0 = (1.0 + c * A) / den;
			a->a1 = - 2.0 * cos (w0) / den;
			a->a2 = (1 - c * A) / den;
			a->b1 = - a->a1;
			a->b2 = - (1 - c / A ) / den;
			a->fgain = a->gain / pow (A * A, (real)a->nstages);
		}
		break;
	}
	flush_speak (a);
}

SPEAK create_speak (int run, int size, real* in, real* out, int rate, real f, real bw, real gain, int nstages, int design)
{
	SPEAK a = (SPEAK) malloc0 (sizeof (speak));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = rate;
	a->f = f;
	a->bw = bw;
	a->gain = gain;
	a->nstages = nstages;
	a->design = design;
	a->x0 = (real *) malloc0 (a->nstages * sizeof (complex));
	a->x1 = (real *) malloc0 (a->nstages * sizeof (complex));
	a->x2 = (real *) malloc0 (a->nstages * sizeof (complex));
	a->y0 = (real *) malloc0 (a->nstages * sizeof (complex));
	a->y1 = (real *) malloc0 (a->nstages * sizeof (complex));
	a->y2 = (real *) malloc0 (a->nstages * sizeof (complex));
	InitializeCriticalSectionAndSpinCount ( &a->cs_update, 2500 );
	calc_speak (a);
	return a;
}

void destroy_speak (SPEAK a)
{
	DeleteCriticalSection (&a->cs_update);
	_aligned_free (a->y2);
	_aligned_free (a->y1);
	_aligned_free (a->y0);
	_aligned_free (a->x2);
	_aligned_free (a->x1);
	_aligned_free (a->x0);
	_aligned_free (a);
}

void flush_speak (SPEAK a)
{
	int i;
	for (i = 0; i < a->nstages; i++)
	{
		a->x1[2 * i + 0] = a->x2[2 * i + 0] = a->y1[2 * i + 0] = a->y2[2 * i + 0] = 0.0;
		a->x1[2 * i + 1] = a->x2[2 * i + 1] = a->y1[2 * i + 1] = a->y2[2 * i + 1] = 0.0;
	}
}

void xspeak (SPEAK a)
{
	EnterCriticalSection (&a->cs_update);
	if (a->run)
	{
		int i, j, n;
		for (i = 0; i < a->size; i++)
		{
			for (j = 0; j < 2; j++)
			{
				a->x0[j] = a->fgain * a->in[2 * i + j];
				for (n = 0; n < a->nstages; n++)
				{
					if (n > 0) a->x0[2 * n + j] = a->y0[2 * (n - 1) + j];
					a->y0[2 * n + j]	= a->a0 * a->x0[2 * n + j] 
										+ a->a1 * a->x1[2 * n + j] 
										+ a->a2 * a->x2[2 * n + j] 
										+ a->b1 * a->y1[2 * n + j] 
										+ a->b2 * a->y2[2 * n + j];
					a->y2[2 * n + j] = a->y1[2 * n + j];
					a->y1[2 * n + j] = a->y0[2 * n + j];
					a->x2[2 * n + j] = a->x1[2 * n + j];
					a->x1[2 * n + j] = a->x0[2 * n + j];
				}
				a->out[2 * i + j] = a->y0[2 * (a->nstages - 1) + j];
			}
		}
	}
	else if (a->out != a->in)
		memcpy (a->out, a->in, a->size * sizeof (complex));
	LeaveCriticalSection (&a->cs_update);
}

void setBuffers_speak (SPEAK a, real* in, real* out)
{
	a->in = in;
	a->out = out;
}

void setSamplerate_speak (SPEAK a, int rate)
{
	a->rate = rate;
	calc_speak (a);
}

void setSize_speak (SPEAK a, int size)
{
	a->size = size;
	flush_speak (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXASPCWRun (int channel, int run)
{
	SPEAK a = rxa[channel].speak.p;
	EnterCriticalSection (&a->cs_update);
	a->run = run;
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXASPCWFreq (int channel, real freq)
{
	SPEAK a = rxa[channel].speak.p;
	EnterCriticalSection (&a->cs_update);
	a->f = freq;
	calc_speak (a);
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXASPCWBandwidth (int channel, real bw)
{
	SPEAK a = rxa[channel].speak.p;
	EnterCriticalSection (&a->cs_update);
	a->bw = bw;
	calc_speak (a);
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXASPCWGain (int channel, real gain)
{
	SPEAK a = rxa[channel].speak.p;
	EnterCriticalSection (&a->cs_update);
	a->gain = gain;
	calc_speak (a);
	LeaveCriticalSection (&a->cs_update);
}

/********************************************************************************************************
*																										*
*										Complex Multiple Peaking										*
*																										*
********************************************************************************************************/

void calc_mpeak (MPEAK a)
{
	int i;
	a->tmp = (real *) malloc0 (a->size * sizeof (complex));
	a->mix = (real *) malloc0 (a->size * sizeof (complex));
	for (i = 0; i < a->npeaks; i++)
	{
		a->pfil[i] = create_speak (	1, 
									a->size, 
									a->in, 
									a->tmp, 
									a->rate, 
									a->f[i], 
									a->bw[i], 
									a->gain[i], 
									a->nstages, 
									1 );
	}
}

void decalc_mpeak (MPEAK a)
{
	int i;
	for (i = 0; i < a->npeaks; i++)
		destroy_speak (a->pfil[i]);
	_aligned_free (a->mix);
	_aligned_free (a->tmp);
}

MPEAK create_mpeak (int run, int size, real* in, real* out, int rate, int npeaks, int* enable, real* f, real* bw, real* gain, int nstages)
{
	MPEAK a = (MPEAK) malloc0 (sizeof (mpeak));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = rate;
	a->npeaks = npeaks;
	a->nstages = nstages;
	a->enable  = (int *) malloc0 (a->npeaks * sizeof (int));
	a->f    = (real *) malloc0 (a->npeaks * sizeof (real));
	a->bw   = (real *) malloc0 (a->npeaks * sizeof (real));
	a->gain = (real *) malloc0 (a->npeaks * sizeof (real));
	memcpy (a->enable, enable, a->npeaks * sizeof (int));
	memcpy (a->f, f, a->npeaks * sizeof (real));
	memcpy (a->bw, bw, a->npeaks * sizeof (real));
	memcpy (a->gain, gain, a->npeaks * sizeof (real));
	a->pfil = (SPEAK *) malloc0 (a->npeaks * sizeof (SPEAK));
	InitializeCriticalSectionAndSpinCount ( &a->cs_update, 2500 );
	calc_mpeak (a);
	return a;
}

void destroy_mpeak (MPEAK a)
{
	decalc_mpeak (a);
	DeleteCriticalSection (&a->cs_update);
	_aligned_free (a->pfil);
	_aligned_free (a->gain);
	_aligned_free (a->bw);
	_aligned_free (a->f);
	_aligned_free (a->enable);
	_aligned_free (a);
}

void flush_mpeak (MPEAK a)
{
	int i;
	for (i = 0; i < a->npeaks; i++)
		flush_speak (a->pfil[i]);
}

void xmpeak (MPEAK a)
{
	EnterCriticalSection (&a->cs_update);
	if (a->run)
	{
		int i, j;
		memset (a->mix, 0, a->size * sizeof (complex));
		for (i = 0; i < a->npeaks; i++)
		{
			if (a->enable[i])
			{
				xspeak (a->pfil[i]);
				for (j = 0; j < 2 * a->size; j++)
					a->mix[j] += a->tmp[j];
			}
		}
		memcpy (a->out, a->mix, a->size * sizeof (complex));
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
	LeaveCriticalSection (&a->cs_update);
}

void setBuffers_mpeak (MPEAK a, real* in, real* out)
{
	decalc_mpeak (a);
	a->in = in;
	a->out = out;
	calc_mpeak (a);
}

void setSamplerate_mpeak (MPEAK a, int rate)
{
	decalc_mpeak (a);
	a->rate = rate;
	calc_mpeak (a);
}

void setSize_mpeak (MPEAK a, int size)
{
	decalc_mpeak (a);
	a->size = size;
	calc_mpeak (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXAmpeakRun (int channel, int run)
{
	MPEAK a = rxa[channel].mpeak.p;
	EnterCriticalSection (&a->cs_update);
	a->run = run;
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXAmpeakNpeaks (int channel, int npeaks)
{
	MPEAK a = rxa[channel].mpeak.p;
	EnterCriticalSection (&a->cs_update);
	a->npeaks = npeaks;
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXAmpeakFilEnable (int channel, int fil, int enable)
{
	MPEAK a = rxa[channel].mpeak.p;
	EnterCriticalSection (&a->cs_update);
	a->enable[fil] = enable;
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXAmpeakFilFreq (int channel, int fil, real freq)
{
	MPEAK a = rxa[channel].mpeak.p;
	EnterCriticalSection (&a->cs_update);
	a->f[fil] = freq;
	a->pfil[fil]->f = freq;
	calc_speak(a->pfil[fil]);
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXAmpeakFilBw (int channel, int fil, real bw)
{
	MPEAK a = rxa[channel].mpeak.p;
	EnterCriticalSection (&a->cs_update);
	a->bw[fil] = bw;
	a->pfil[fil]->bw = bw;
	calc_speak(a->pfil[fil]);
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetRXAmpeakFilGain (int channel, int fil, real gain)
{
	MPEAK a = rxa[channel].mpeak.p;
	EnterCriticalSection (&a->cs_update);
	a->gain[fil] = gain;
	a->pfil[fil]->gain = gain;
	calc_speak(a->pfil[fil]);
	LeaveCriticalSection (&a->cs_update);
}


/********************************************************************************************************
*																										*
*										    Phase Rotator												*
*																										*
********************************************************************************************************/

void calc_phrot (PHROT a)
{
	real g;
	a->x0 = (real *) malloc0 (a->nstages * sizeof (real));
	a->x1 = (real *) malloc0 (a->nstages * sizeof (real));
	a->y0 = (real *) malloc0 (a->nstages * sizeof (real));
	a->y1 = (real *) malloc0 (a->nstages * sizeof (real));
	g = tan (PI * a->fc / (real)a->rate);
	a->b0 = (g - 1.0) / (g + 1.0);
	a->b1 = 1.0;
	a->a1 = a->b0;
}

PHROT create_phrot (int run, int size, real* in, real* out, int rate, real fc, int nstages)
{
	PHROT a = (PHROT) malloc0 (sizeof (phrot));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = rate;
	a->fc = fc;
	a->nstages = nstages;
	InitializeCriticalSectionAndSpinCount ( &a->cs_update, 2500 );
	calc_phrot (a);
	return a;
}

void decalc_phrot (PHROT a)
{
	_aligned_free (a->y1);
	_aligned_free (a->y0);
	_aligned_free (a->x1);
	_aligned_free (a->x0);
}

void destroy_phrot (PHROT a)
{
	decalc_phrot (a);
	DeleteCriticalSection (&a->cs_update);
	_aligned_free (a);
}

void flush_phrot (PHROT a)
{
	memset (a->x0, 0, a->nstages * sizeof (real));
	memset (a->x1, 0, a->nstages * sizeof (real));
	memset (a->y0, 0, a->nstages * sizeof (real));
	memset (a->y1, 0, a->nstages * sizeof (real));
}

void xphrot (PHROT a)
{
	EnterCriticalSection (&a->cs_update);
	if (a->run)
	{
		int i, n;
		for (i = 0; i < a->size; i++)
		{
			a->x0[0] = a->in[2 * i + 0];
			for (n = 0; n < a->nstages; n++)
			{
				if (n > 0) a->x0[n] = a->y0[n - 1];
				a->y0[n]	= a->b0 * a->x0[n]
							+ a->b1 * a->x1[n]
							- a->a1 * a->y1[n];
				a->y1[n] = a->y0[n];
				a->x1[n] = a->x0[n];
			}
			a->out[2 * i + 0] = a->y0[a->nstages - 1];
		}
	}
	else if (a->out != a->in)
		memcpy (a->out, a->in, a->size * sizeof (complex));
	LeaveCriticalSection (&a->cs_update);
}

void setBuffers_phrot (PHROT a, real* in, real* out)
{
	a->in = in;
	a->out = out;
}

void setSamplerate_phrot (PHROT a, int rate)
{
	decalc_phrot (a);
	a->rate = rate;
	calc_phrot (a);
}

void setSize_phrot (PHROT a, int size)
{
	a->size = size;
	flush_phrot (a);
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetTXAPHROTRun (int channel, int run)
{
	PHROT a = txa[channel].phrot.p;
	EnterCriticalSection (&a->cs_update);
	a->run = run;
	if (a->run) flush_phrot (a);
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetTXAPHROTCorner (int channel, real corner)
{
	PHROT a = txa[channel].phrot.p;
	EnterCriticalSection (&a->cs_update);
	decalc_phrot (a);
	a->fc = corner;
	calc_phrot (a);
	LeaveCriticalSection (&a->cs_update);
}

PORT
void SetTXAPHROTNstages (int channel, int nstages)
{
	PHROT a = txa[channel].phrot.p;
	EnterCriticalSection (&a->cs_update);
	decalc_phrot (a);
	a->nstages = nstages;
	calc_phrot (a);
	LeaveCriticalSection (&a->cs_update);
}