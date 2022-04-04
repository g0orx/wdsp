/*  snb.h

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

#ifndef _snba_h
#define _snba_h

#include "resample.h"

typedef struct _snba
{
	int run;
	real* in;
	real* out;
	int inrate;
	int internalrate;
	int bsize;
	int xsize;
	int ovrlp;
	int incr;
	int iasize;
	int iainidx;
	int iaoutidx;
	real* inaccum;
	real* xbase;
	real* xaux;
	int nsamps;
	int oasize;
	int oainidx;
	int oaoutidx;
	int init_oaoutidx;
	real* outaccum;

	int resamprun;
	int isize;
	RESAMPLE inresamp;
	RESAMPLE outresamp;
	real* inbuff;
	real* outbuff;
	struct _exec
	{
		int asize;
		real* a;
		real* v;
		int* detout;
		real* savex;
		real* xHout;
		int* unfixed;
		int npasses;
	} exec;
	struct _det
	{
		real k1;
		real k2;
		int b;
		int pre;
		int post;
		real* vp;
		real* vpwr;
	} sdet;
	struct _scan
	{
		real pmultmin;
	} scan;
	real out_low_cut;
	real out_high_cut;
} snba, *SNBA;

extern SNBA create_snba (int run, real* in, real* out, int inrate, int internalrate, int bsize, int ovrlp, int xsize,
	int asize, int npasses, real k1, real k2, int b, int pre, int post, real pmultmin, real out_low_cut, real out_high_cut);

extern void destroy_snba (SNBA d);

extern void flush_snba (SNBA d);

extern void xsnba (SNBA d);

extern void setBuffers_snba (SNBA a, real* in, real* out);

extern void setSamplerate_snba (SNBA a, int rate);

extern void setSize_snba (SNBA a, int size);

__declspec (dllexport) void SetRXASNBAOutputBandwidth (int channel, real flow, real fhigh);

typedef struct _bpsnba
{
		int run;						// run the filter
		int run_notches;				// use the notches, vs straight bandpass
		int position;					// position in the processing pipeline
		int size;						// buffer size
		int nc;							// number of filter coefficients
		int mp;							// minimum phase flag
		real* in;						// input buffer
		real* out;					// output buffer
		int rate;						// sample rate
		real* buff;					// internal buffer
		NBP bpsnba;						// pointer to the notched bandpass filter, nbp
		real f_low;					// low cutoff frequency
		real f_high;					// high cutoff frequency
		real abs_low_freq;			// lowest positive freq supported by SNB
		real abs_high_freq;			// highest positive freq supported by SNG
		int wintype;					// filter window type
		real gain;					// filter gain
		int autoincr;					// use auto increment for notch width
		int maxpb;						// maximum passband segments supported
		NOTCHDB* ptraddr;				// pointer to address of NOTCH DATABASE
} bpsnba, *BPSNBA;

extern void calc_bpsnba (BPSNBA a);

extern void decalc_bpsnba (BPSNBA a);

extern BPSNBA create_bpsnba (int run, int run_notches, int position, int size, int nc, int mp, real* in, real* out, int rate,  
	real abs_low_freq, real abs_high_freq, real f_low, real f_high, int wintype, real gain, int autoincr, 
	int maxpb, NOTCHDB* ptraddr);

extern void destroy_bpsnba (BPSNBA a);

extern void flush_bpsnba (BPSNBA a);

extern void setBuffers_bpsnba (BPSNBA a, real* in, real* out);

extern void setSamplerate_bpsnba (BPSNBA a, int rate);

extern void setSize_bpsnba (BPSNBA a, int size);

extern void xbpsnbain (BPSNBA a, int position);

extern void xbpsnbaout (BPSNBA a, int position);

extern void recalc_bpsnba_filter (BPSNBA a, int update);

__declspec (dllexport) void RXABPSNBASetNC (int channel, int nc);

__declspec (dllexport) void RXABPSNBASetMP (int channel, int mp);

#endif
