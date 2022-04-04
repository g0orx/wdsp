/*  fmd.h

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

#ifndef _fmd_h
#define _fmd_h
#include "iir.h"
#include "firmin.h"
typedef struct _fmd
{
	int run;
	int size;
	real* in;
	real* out;
	real rate;
	real f_low;						// audio low cutoff
	real f_high;						// audio high cutoff
	// pll
	real fmin;						// pll - minimum carrier freq to lock
	real fmax;						// pll - maximum carrier freq to lock
	real omega_min;					// pll - minimum lock check parameter
	real omega_max;					// pll - maximum lock check parameter
	real zeta;						// pll - damping factor; as coded, must be <=1.0
	real omegaN;						// pll - natural frequency
	real phs;							// pll - phase accumulator
	real omega;						// pll - locked pll frequency
	real fil_out;						// pll - filter output
	real g1, g2;						// pll - filter gain parameters
	real pllpole;						// pll - pole frequency
	// for dc removal
	real tau;
	real mtau;
	real onem_mtau;
	real fmdc;
	// pll audio gain
	real deviation;
	real again;
	// for de-emphasis filter
	real* audio;
	FIRCORE pde;
	int nc_de;
	int mp_de;
	// for audio filter
	FIRCORE paud;
	int nc_aud;
	int mp_aud;
	real afgain;
	// CTCSS removal
	SNOTCH sntch;
	int sntch_run;
	real ctcss_freq;
} fmd, *FMD;

extern FMD create_fmd ( int run, int size, real* in, real* out, int rate, real deviation, 
	real f_low, real f_high, real fmin, real fmax, real zeta, real omegaN, real tau, 
	real afgain, int sntch_run, real ctcss_freq, int nc_de, int mp_de, int nc_aud, int mp_aud);

extern void destroy_fmd (FMD a);

extern void flush_fmd (FMD a);

extern void xfmd (FMD a);

extern void setBuffers_fmd (FMD a, real* in, real* out);

extern void setSamplerate_fmd (FMD a, int rate);

extern void setSize_fmd (FMD a, int size);

// RXA Properties

extern __declspec (dllexport) void SetRXAFMDeviation (int channel, real deviation);

extern __declspec (dllexport) void SetRXAFMNCde (int channel, int nc);

extern __declspec (dllexport) void SetRXAFMMPde (int channel, int mp);

extern __declspec (dllexport) void SetRXAFMNCaud (int channel, int nc);

extern __declspec (dllexport) void SetRXAFMMPaud (int channel, int mp);

#endif