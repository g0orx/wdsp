/*  iir.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2014 Warren Pratt, NR0V

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

/********************************************************************************************************
*																										*
*											Bi-Quad Notch												*
*																										*
********************************************************************************************************/

#ifndef _snotch_h
#define _snotch_h

typedef struct _snotch
{
	int run;
	int size;
	real* in;
	real* out;
	real rate;
	real f;
	real bw;
	real a0, a1, a2, b1, b2;
	real x0, x1, x2, y1, y2;
	CRITICAL_SECTION cs_update;
} snotch, *SNOTCH;

extern SNOTCH create_snotch (int run, int size, real* in, real* out, int rate, real f, real bw);

extern void destroy_snotch (SNOTCH a);

extern void flush_snotch (SNOTCH a);

extern void xsnotch (SNOTCH a);

extern void setBuffers_snotch (SNOTCH a, real* in, real* out);

extern void setSamplerate_snotch (SNOTCH a, int rate);

extern void setSize_snotch (SNOTCH a, int size);

extern void SetSNCTCSSFreq (SNOTCH a, real freq);

extern void SetSNCTCSSRun (SNOTCH a, int run);

#endif

/********************************************************************************************************
*																										*
*											Complex Bi-Quad Peaking										*
*																										*
********************************************************************************************************/

#ifndef _speak_h
#define _speak_h

typedef struct _speak
{
	int run;
	int size;
	real* in;
	real* out;
	real rate;
	real f;
	real bw;
	real cbw;
	real gain;
	real fgain;
	int nstages;
	int design;
	real a0, a1, a2, b1, b2;
	real *x0, *x1, *x2, *y0, *y1, *y2;
	CRITICAL_SECTION cs_update;
} speak, *SPEAK;

extern SPEAK create_speak (int run, int size, real* in, real* out, int rate, real f, real bw, real gain, int nstages, int design);

extern void destroy_speak (SPEAK a);

extern void flush_speak (SPEAK a);

extern void xspeak (SPEAK a);

extern void setBuffers_speak (SPEAK a, real* in, real* out);

extern void setSamplerate_speak (SPEAK a, int rate);

extern void setSize_speak (SPEAK a, int size);

#endif

/********************************************************************************************************
*																										*
*										Complex Multiple Peaking										*
*																										*
********************************************************************************************************/

#ifndef _mpeak_h
#define _mpeak_h

typedef struct _mpeak
{
	int run;
	int size;
	real* in;
	real* out;
	int rate;
	int npeaks;
	int* enable;
	real* f;
	real* bw;
	real* gain;
	int nstages;
	SPEAK* pfil;
	real* tmp;
	real* mix;
	CRITICAL_SECTION cs_update;
} mpeak, *MPEAK;

extern MPEAK create_mpeak (int run, int size, real* in, real* out, int rate, int npeaks, int* enable, real* f, real* bw, real* gain, int nstages);

extern void destroy_mpeak (MPEAK a);

extern void flush_mpeak (MPEAK a);

extern void xmpeak (MPEAK a);

extern void setBuffers_mpeak (MPEAK a, real* in, real* out);

extern void setSamplerate_mpeak (MPEAK a, int rate);

extern void setSize_mpeak (MPEAK a, int size);

#endif

/********************************************************************************************************
*																										*
*										     Phase Rotator      										*
*																										*
********************************************************************************************************/

#ifndef _phrot_h
#define _phrot_h

typedef struct _phrot
{
	int run;
	int size;
	real* in;
	real* out;
	int rate;
	real fc;
	int nstages;
	// normalized such that a0 = 1
	real a1, b0, b1;
	real *x0, *x1, *y0, *y1;
	CRITICAL_SECTION cs_update;
} phrot, *PHROT;

extern PHROT create_phrot (int run, int size, real* in, real* out, int rate, real fc, int nstages);

extern void destroy_phrot (PHROT a);

extern void flush_phrot (PHROT a);

extern void xphrot (PHROT a);

extern void setBuffers_phrot (PHROT a, real* in, real* out);

extern void setSamplerate_phrot (PHROT a, int rate);

extern void setSize_phrot (PHROT a, int size);

#endif