/*  nbp.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2015, 2016 Warren Pratt, NR0V

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

#ifndef _nbp_h
#define _nbp_h
#include "firmin.h"
typedef struct _notchdb
{
	int master_run;
	real tunefreq;
	real shift;
	int nn;
	int* active;
	real* fcenter;
	real* fwidth;
	real* nlow;
	real* nhigh;
	int maxnotches;
} notchdb, *NOTCHDB;

extern NOTCHDB create_notchdb (int master_run, int maxnotches);

extern void destroy_notchdb (NOTCHDB b);

typedef struct _nbp
{
	int run;				// run the filter
	int fnfrun;				// use the notches
	int position;			// position in processing pipeline
	int size;				// buffer size
	int nc;					// number of filter coefficients
	int mp;					// minimum phase flag
	real* in;				// input buffer
	real* out;			// output buffer
	real flow;			// low bandpass cutoff freq
	real fhigh;			// high bandpass cutoff freq
	real* impulse;		// filter impulse response
	real rate;			// sample rate
	int wintype;			// filter window type
	real gain;			// filter gain
	int autoincr;			// auto-increment notch width
	int maxpb;				// maximum number of passbands
	NOTCHDB* ptraddr;		// ptr to addr of notch-database data structure
	real* bplow;			// array of passband lows
	real* bphigh;			// array of passband highs
	int numpb;				// number of passbands
	FIRCORE p;
	int havnotch;
	int hadnotch;
} nbp, *NBP;

extern NBP create_nbp(int run, int fnfrun, int position, int size, int nc, int mp, real* in, real* out, 
	real flow, real fhigh, int rate, int wintype, real gain, int autoincr, int maxpb, NOTCHDB* ptraddr);

extern void destroy_nbp (NBP a);

extern void flush_nbp (NBP a);

extern void xnbp (NBP a, int pos);

extern void setBuffers_nbp (NBP a, real* in, real* out);

extern void setSamplerate_nbp (NBP a, int rate);

extern void setSize_nbp (NBP a, int size);

extern void calc_nbp_impulse (NBP a);

extern void setNc_nbp (NBP a);

extern void setMp_nbp (NBP a);

__declspec (dllexport) void RXANBPSetFreqs (int channel, real flow, real fhigh);

__declspec (dllexport) void RXANBPSetNC (int channel, int nc);

__declspec (dllexport) void RXANBPSetMP (int channel, int mp);

#endif
