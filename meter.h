/*  meter.h

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

#ifndef _meter_h
#define _meter_h

typedef struct _meter
{
	int run;
	int* prun;
	int size;
	real* buff;
	real rate;
	real tau_average;
	real tau_peak_decay;
	real mult_average;
	real mult_peak;
	real* result;
	int enum_av;
	int enum_pk;
	int enum_gain;
	real* pgain;
	real avg;
	real peak;
	CRITICAL_SECTION mtupdate;
} meter, *METER;

extern METER create_meter (int run, int* prun, int size, real* buff, int rate, real tau_av, real tau_decay, real* result, CRITICAL_SECTION** pmtupdate, int enum_av, int enum_pk, int enum_gain, real* pgain);

extern void destroy_meter (METER a);

extern void flush_meter (METER a);

extern void xmeter (METER a);

extern void setBuffers_meter (METER a, real* in);

extern void setSamplerate_meter (METER a, int rate);

extern void setSize_meter (METER a, int size);

// RXA Properties

extern __declspec (dllexport) real GetRXAMeter (int channel, int mt);

// TXA Properties

extern __declspec (dllexport) real GetTXAMeter (int channel, int mt);

#endif