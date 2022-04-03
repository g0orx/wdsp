/*  meter.c

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

void calc_meter (METER a)
{
	a->mult_average = exp(-1.0 / (a->rate * a->tau_average));
	a->mult_peak = exp(-1.0 / (a->rate * a->tau_peak_decay));
	flush_meter(a);
}

METER create_meter (int run, int* prun, int size, real* buff, int rate, real tau_av, real tau_decay, real* result, CRITICAL_SECTION** pmtupdate, int enum_av, int enum_pk, int enum_gain, real* pgain)
{
	METER a = (METER) malloc0 (sizeof (meter));
	a->run = run;
	a->prun = prun;
	a->size = size;
	a->buff = buff;
	a->rate = (real)rate;
	a->tau_average = tau_av;
	a->tau_peak_decay = tau_decay;
	a->result = result;
	a->enum_av = enum_av;
	a->enum_pk = enum_pk;
	a->enum_gain = enum_gain;
	a->pgain = pgain;
	calc_meter(a);
	InitializeCriticalSectionAndSpinCount (&a->mtupdate, 2500);
	pmtupdate[enum_av]   = &a->mtupdate;
	pmtupdate[enum_pk]   = &a->mtupdate;
	pmtupdate[enum_gain] = &a->mtupdate;
	return a;
}

void destroy_meter (METER a)
{
	DeleteCriticalSection (&a->mtupdate);
	_aligned_free (a);
}

void flush_meter (METER a)
{
	a->avg  = 0.0;
	a->peak = 0.0;
	a->result[a->enum_av] = -400.0;
	a->result[a->enum_pk] = -400.0;
	if ((a->pgain != 0) && (a->enum_gain >= 0))
		a->result[a->enum_gain] = -400.0;
}

void xmeter (METER a)
{
	int srun;
	EnterCriticalSection (&a->mtupdate);
	if (a->prun != 0)
		srun = *(a->prun);
	else
		srun = 1;
	if (a->run && srun)
	{
		int i;
		real smag;
		real np = 0.0;
		for (i = 0; i < a->size; i++)
		{
			smag = a->buff[2 * i + 0] * a->buff[2 * i + 0] + a->buff[2 * i + 1] * a->buff[2 * i + 1];
			a->avg = a->avg * a->mult_average + (1.0 - a->mult_average) * smag;
			a->peak *= a->mult_peak;
			if (smag > np) np = smag;
		}
		if (np > a->peak) a->peak = np;
		a->result[a->enum_av] = 10.0 * mlog10 (a->avg + 1.0e-40);
		a->result[a->enum_pk] = 10.0 * mlog10 (a->peak + 1.0e-40);
		if ((a->pgain != 0) && (a->enum_gain >= 0))
			a->result[a->enum_gain] = 20.0 * mlog10 (*a->pgain + 1.0e-40);
	}
	else
	{
		if (a->enum_av   >= 0) a->result[a->enum_av]   = - 400.0;
		if (a->enum_pk   >= 0) a->result[a->enum_pk]   = - 400.0;
		if (a->enum_gain >= 0) a->result[a->enum_gain] = +   0.0;
	}
	LeaveCriticalSection (&a->mtupdate);
}

void setBuffers_meter (METER a, real* in)
{
	a->buff = in;
}

void setSamplerate_meter (METER a, int rate)
{
	a->rate = rate;
	calc_meter(a);
}

void setSize_meter (METER a, int size)
{
	a->size = size;
	flush_meter (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
real GetRXAMeter (int channel, int mt)
{
	real val;
	CRITICAL_SECTION* a = rxa[channel].pmtupdate[mt];
	EnterCriticalSection (a);
	val = rxa[channel].meter[mt];
	LeaveCriticalSection (a);
	return val;
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
real GetTXAMeter (int channel, int mt)
{
	real val;
	CRITICAL_SECTION* a = txa[channel].pmtupdate[mt];
	EnterCriticalSection (a);
	val = txa[channel].meter[mt];
	LeaveCriticalSection (a);
	return val;
}