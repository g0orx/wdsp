/*  fmmod.h

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

#ifndef _fmmod_h
#define _fmmod_h
#include "firmin.h"
typedef struct _fmmod
{
	int run;
	int size;
	real* in;
	real* out;
	real samplerate;
	real deviation;
	real f_low;
	real f_high;
	int ctcss_run;
	real ctcss_level;
	real ctcss_freq;
	// for ctcss gen
	real tscale;
	real tphase;
	real tdelta;
	// mod
	real sphase;
	real sdelta;
	// bandpass
	int bp_run;
	real bp_fc;
	int nc;
	int mp;
	FIRCORE p;
}fmmod, *FMMOD;

extern FMMOD create_fmmod (int run, int size, real* in, real* out, int rate, real dev, real f_low, real f_high, 
	int ctcss_run, real ctcss_level, real ctcss_freq, int bp_run, int nc, int mp);

extern void destroy_fmmod (FMMOD a);

extern void flush_fmmod (FMMOD a);

extern void xfmmod (FMMOD a);

extern void setBuffers_fmmod (FMMOD a, real* in, real* out);

extern void setSamplerate_fmmod (FMMOD a, int rate);

extern void setSize_fmmod (FMMOD a, int size);

// TXA Properties

extern __declspec (dllexport) void SetTXAFMDeviation (int channel, real deviation);

extern __declspec (dllexport) void SetTXACTCSSFreq (int channel, real freq);

extern __declspec (dllexport) void SetTXACTCSSRun (int channel, int run);

extern __declspec (dllexport) void SetTXAFMMP (int channel, int mp);

extern __declspec (dllexport) void SetTXAFMNC (int channel, int nc);

#endif
