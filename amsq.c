/*  amsq.c

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

void compute_slews(AMSQ a)
{
	int i;
	real delta, theta;
	delta = PI / (real)a->ntup;
	theta = 0.0;
	for (i = 0; i <= a->ntup; i++)
	{
		a->cup[i] = a->muted_gain + (1.0 - a->muted_gain) * 0.5 * (1.0 - cos (theta));
		theta += delta;
	}
	delta = PI / (real)a->ntdown;
	theta = 0.0;
	for (i = 0; i <= a->ntdown; i++)
	{
		a->cdown[i] = a->muted_gain + (1.0 - a->muted_gain) * 0.5 * (1.0 + cos (theta));
		theta += delta;
	}
}

void calc_amsq(AMSQ a)
{
	// signal averaging
	a->trigsig = (real *)malloc0(a->size * sizeof(complex));
	a->avm = exp(-1.0 / (a->rate * a->avtau));
	a->onem_avm = 1.0 - a->avm;
	a->avsig = 0.0;
	// level change
	a->ntup = (int)(a->tup * a->rate);
	a->ntdown = (int)(a->tdown * a->rate);
	a->cup = (real *)malloc0((a->ntup + 1) * sizeof(real));
	a->cdown = (real *)malloc0((a->ntdown + 1) * sizeof(real));
	compute_slews(a);
	// control
	a->state = 0;
}

void decalc_amsq (AMSQ a)
{
	_aligned_free (a->cdown);
	_aligned_free (a->cup);
	_aligned_free (a->trigsig);
}

AMSQ create_amsq (int run, int size, real* in, real* out, real* trigger, int rate, real avtau, 
	real tup, real tdown, real tail_thresh, real unmute_thresh, real min_tail, real max_tail, real muted_gain)
{
	AMSQ a = (AMSQ) malloc0 (sizeof (amsq));
	a->run = run;
	a->size = size;
	a->in = in;
	a->out = out;
	a->rate = (real)rate;
	a->muted_gain = muted_gain;
	a->trigger = trigger;
	a->avtau = avtau;
	a->tup = tup;
	a->tdown = tdown;
	a->tail_thresh = tail_thresh;
	a->unmute_thresh = unmute_thresh;
	a->min_tail = min_tail;
	a->max_tail = max_tail;
	calc_amsq (a);
	return a;
}

void destroy_amsq (AMSQ a)
{
	decalc_amsq (a);
	_aligned_free (a);
}

void flush_amsq (AMSQ a)
{
	memset (a->trigsig, 0, a->size * sizeof (complex));
	a->avsig = 0.0;
	a->state = 0;
}

enum _amsqstate
{
	MUTED,
	INCREASE,
	UNMUTED,
	TAIL,
	DECREASE
};

void xamsq (AMSQ a)
{
	if (a->run)
	{
		int i;
		real sig, siglimit;
		for (i = 0; i < a->size; i++)
		{
			sig = sqrt (a->trigsig[2 * i + 0] * a->trigsig[2 * i + 0] + a->trigsig[2 * i + 1] * a->trigsig[2 * i + 1]);
			a->avsig = a->avm * a->avsig + a->onem_avm * sig;
			switch (a->state)
			{
			case MUTED:
				if (a->avsig > a->unmute_thresh)
				{
					a->state = INCREASE;
					a->count = a->ntup;
				}
				a->out[2 * i + 0] = a->muted_gain * a->in[2 * i + 0];
				a->out[2 * i + 1] = a->muted_gain * a->in[2 * i + 1];
				break;
			case INCREASE:
				a->out[2 * i + 0] = a->in[2 * i + 0] * a->cup[a->ntup - a->count];
				a->out[2 * i + 1] = a->in[2 * i + 1] * a->cup[a->ntup - a->count];
				if (a->count-- == 0)
					a->state = UNMUTED;
				break;
			case UNMUTED:
				if (a->avsig < a->tail_thresh)
				{
					a->state = TAIL;
					if ((siglimit = a->avsig) > 1.0) siglimit = 1.0;
					a->count = (int)((a->min_tail + (a->max_tail - a->min_tail) * (1.0 - siglimit)) * a->rate);
				}
				a->out[2 * i + 0] = a->in[2 * i + 0];
				a->out[2 * i + 1] = a->in[2 * i + 1];
				break;
			case TAIL:
				a->out[2 * i + 0] = a->in[2 * i + 0];
				a->out[2 * i + 1] = a->in[2 * i + 1];
				if (a->avsig > a->unmute_thresh)
					a->state = UNMUTED;
				else if (a->count-- == 0)
				{
					a->state = DECREASE;
					a->count = a->ntdown;
				}
				break;
			case DECREASE:
				a->out[2 * i + 0] = a->in[2 * i + 0] * a->cdown[a->ntdown - a->count];
				a->out[2 * i + 1] = a->in[2 * i + 1] * a->cdown[a->ntdown - a->count];
				if (a->count-- == 0)
					a->state = MUTED;
				break;
			}
		}
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

void xamsqcap (AMSQ a)
{
	memcpy (a->trigsig, a->trigger, a->size * sizeof (complex));
}

void setBuffers_amsq (AMSQ a, real* in, real* out, real* trigger)
{
	a->in = in;
	a->out = out;
	a->trigger = trigger;
}

void setSamplerate_amsq (AMSQ a, int rate)
{
	decalc_amsq (a);
	a->rate = rate;
	calc_amsq (a);
}

void setSize_amsq (AMSQ a, int size)
{
	decalc_amsq (a);
	a->size = size;
	calc_amsq (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXAAMSQRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].amsq.p->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAAMSQThreshold (int channel, real threshold)
{
	real thresh = pow (10.0, threshold / 20.0);
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].amsq.p->tail_thresh = 0.9 * thresh;
	rxa[channel].amsq.p->unmute_thresh =  thresh;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAAMSQMaxTail (int channel, real tail)
{
	AMSQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].amsq.p;
	if (tail < a->min_tail) tail = a->min_tail;
	a->max_tail = tail;
	LeaveCriticalSection (&ch[channel].csDSP);
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetTXAAMSQRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	txa[channel].amsq.p->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAAMSQMutedGain (int channel, real dBlevel)
{	// dBlevel is negative
	AMSQ a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = txa[channel].amsq.p;
	a->muted_gain = pow (10.0, dBlevel / 20.0);
	compute_slews(a);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetTXAAMSQThreshold (int channel, real threshold)
{
	real thresh = pow (10.0, threshold / 20.0);
	EnterCriticalSection (&ch[channel].csDSP);
	txa[channel].amsq.p->tail_thresh = 0.9 * thresh;
	txa[channel].amsq.p->unmute_thresh =  thresh;
	LeaveCriticalSection (&ch[channel].csDSP);
}