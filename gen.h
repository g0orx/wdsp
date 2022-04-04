/*  gen.h

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

#ifndef _gen_h
#define _gen_h

typedef struct _gen
{
	int run;					// run
	int size;					// number of samples per buffer
	real* in;					// input buffer (retained in case I want to mix in a generated signal)
	real* out;				// output buffer
	real rate;				// sample rate
	int mode;					
	struct _tone
	{
		real mag;
		real freq;
		real phs;
		real delta;
		real cosdelta;
		real sindelta;
	} tone;
	struct _tt
	{
		real mag1;
		real mag2;
		real f1;
		real f2;
		real phs1;
		real phs2;
		real delta1;
		real delta2;
		real cosdelta1;
		real cosdelta2;
		real sindelta1;
		real sindelta2;
	} tt;
	struct _noise
	{
		real mag;
	} noise;
	struct _sweep
	{
		real mag;
		real f1;
		real f2;
		real sweeprate;
		real phs;
		real dphs;
		real d2phs;
		real dphsmax;
	} sweep;
	struct _saw
	{
		real mag;
		real f;
		real period;
		real delta;
		real t;
	} saw;
	struct _tri
	{
		real mag;
		real f;
		real period;
		real half;
		real delta;
		real t;
		real t1;
	} tri;
	struct _pulse
	{
		real mag;
		real pf;
		real pdutycycle;
		real ptranstime;
		real* ctrans;
		int pcount;
		int pnon;
		int pntrans;
		int pnoff;
		real pperiod;
		real tf;
		real tphs;
		real tdelta;
		real tcosdelta;
		real tsindelta;
		int state;
	} pulse;
} gen, *GEN;

extern GEN create_gen (int run, int size, real* in, real* out, int rate, int mode);

extern void destroy_gen (GEN a);

extern void flush_gen (GEN a);

extern void xgen (GEN a);

extern void setBuffers_gen (GEN a, real* in, real* out);

extern void setSamplerate_gen (GEN a, int rate);

extern void setSize_gen (GEN a, int size);

// TXA Properties

extern __declspec (dllexport) void SetTXAgenRun (int channel, int run);

#endif