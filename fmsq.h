/*  fmsq.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2013, 2016 Warren Pratt, NR0V

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

#ifndef _fmsq_h
#define _fmsq_h
#include "firmin.h"
typedef struct _fmsq
{
	int run;							// 0 if squelch system is OFF; 1 if it's ON
	int size;							// size of input/output buffers
	real* insig;						// squelch input signal buffer
	real* outsig;						// squelch output signal buffer
	real* trigger;					// buffer used to trigger mute/unmute (may be same as input; matches timing of input buffer)
	real rate;						// sample rate
	real* noise;
	real fc;							// corner frequency for sig / noise detection
	real* pllpole;					// pointer to pole frequency of the fm demodulator pll
	real F[4];
	real G[4];
	real avtau;						// time constant for averaging noise
	real avm;						
	real onem_avm;
	real avnoise;
	real longtau;						// time constant for long averaging
	real longavm;
	real onem_longavm;
	real longnoise;
	int state;							// state machine control
	int count;
	real tup;
	real tdown;
	int ntup;
	int ntdown;
	real* cup;
	real* cdown;
	real tail_thresh;
	real unmute_thresh;
	real min_tail;
	real max_tail;
	int ready;
	real ramp;
	real rstep;
	real tdelay;
	int nc;
	int mp;
	FIRCORE p;
} fmsq, *FMSQ;

extern FMSQ create_fmsq (int run, int size, real* insig, real* outsig, real* trigger, int rate, real fc, 
	real* pllpole, real tdelay, real avtau, real longtau, real tup, real tdown, real tail_thresh, 
	real unmute_thresh, real min_tail, real max_tail, int nc, int mp);

extern void destroy_fmsq (FMSQ a);

extern void flush_fmsq (FMSQ a);

extern void xfmsq (FMSQ a);

extern void setBuffers_fmsq (FMSQ a, real* in, real* out, real* trig);

extern void setSamplerate_fmsq (FMSQ a, int rate);

extern void setSize_fmsq (FMSQ a, int size);

// RXA Properties

extern __declspec (dllexport) void SetRXAFMSQThreshold (int channel, real threshold);

extern __declspec (dllexport) void SetRXAFMSQNC (int channel, int nc);

extern __declspec (dllexport) void SetRXAFMSQMP (int channel, int mp);

#endif