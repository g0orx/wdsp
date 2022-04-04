/*  amsq.h

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
#ifndef _amsq_h
#define _amsq_h

typedef struct _amsq
{
	int run;							// 0 if squelch system is OFF; 1 if it's ON
	int size;							// size of input/output buffers
	real* in;							// squelch input signal buffer
	real* out;						// squelch output signal buffer
	real* trigger;					// pointer to trigger data source
	real* trigsig;					// buffer containing trigger signal
	real rate;						// sample rate
	real avtau;						// time constant for averaging noise
	real avm;						
	real onem_avm;
	real avsig;
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
	real muted_gain;
} amsq, *AMSQ;

extern AMSQ create_amsq (int run, int size, real* in, real* out, real* trigger, int rate, real avtau, real tup, real tdown, real tail_thresh, real unmute_thresh, real min_tail, real max_tail, real muted_gain);

extern void destroy_amsq (AMSQ a);

extern void flush_amsq (AMSQ a);

extern void xamsq (AMSQ a);

extern void xamsqcap (AMSQ a);

extern void setBuffers_amsq (AMSQ a, real* in, real* out, real* trigger);

extern void setSamplerate_amsq (AMSQ a, int rate);

extern void setSize_amsq (AMSQ a, int size);

// RXA Properties

extern __declspec (dllexport) void SetRXAAMSQRun (int channel, int run);

extern __declspec (dllexport) void SetRXAAMSQThreshold (int channel, real threshold);

extern __declspec (dllexport) void SetRXAAMSQMaxTail (int channel, real tail);

// TXA Properties

extern __declspec (dllexport) void SetTXAAMSQRun (int channel, int run);

extern __declspec (dllexport) void SetTXAAMSQMutedGain (int channel, real dBlevel);

extern __declspec (dllexport) void SetTXAAMSQThreshold (int channel, real threshold);

#endif