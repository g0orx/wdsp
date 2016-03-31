/*  nbp.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2015 Warren Pratt, NR0V

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

typedef struct _notchdb
{
	int fnfrun;
	double tunefreq;
	double shift;
	int nn;
	int* active;
	double* fcenter;
	double* fwidth;
	double* nlow;
	double* nhigh;
	int maxnotches;
} notchdb, *NOTCHDB;

extern NOTCHDB create_notchdb (int fnfrun, int maxnotches);

extern void destroy_notchdb (NOTCHDB b);

typedef struct _nbp
{
	int run;
	int position;
	int size;
	double* in;
	double* out;
	double flow;
	double fhigh;
	double* infilt;
	double* product;
	double* mults;
	double rate;
	int wintype;
	double gain;
	int autoincr;
	int maxpb;
	NOTCHDB* ptraddr;
	double* bplow;
	double* bphigh;
	int numpb;
	fftw_plan CFor;
	fftw_plan CRev;

	int havnotch;
	int hadnotch;
} nbp, *NBP;

extern NBP create_nbp(int run, int position, int size, double* in, double* out, 
	double flow, double fhigh, int rate, int wintype, double gain, int autoincr, int maxpb, NOTCHDB* ptraddr);

extern void destroy_nbp (NBP a);

extern void flush_nbp (NBP a);

extern void xnbp (NBP a, int pos);

extern void setBuffers_nbp (NBP a, double* in, double* out);

extern void setSamplerate_nbp (NBP a, int rate);

extern void setSize_nbp (NBP a, int size);

extern __declspec (dllexport) int RXANBPAddNotch (int channel, int notch, 
	double fcenter, double fwidth, int active);

extern __declspec (dllexport) void RXANBPSetNotchesRun (int channel, int  run);

extern __declspec (dllexport) void RXANBPSetAutoIncrease (int channel, int autoincr);

#endif