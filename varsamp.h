/*  varsamp.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2017 Warren Pratt, NR0V

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

#ifndef _varsamp_h
#define _varsamp_h

typedef struct _varsamp
{
	int run;
	int size;
	real* in;
	real* out;
	int in_rate;
	int out_rate;
	real fcin;
	real fc;
	real fc_low;
	real gain;
	int idx_in;
	int ncoef;
	real* h;
	int rsize;
	real* ring;
	real var;
	int varmode;
	real cvar;
	real inv_cvar;
	real old_inv_cvar;
	real dicvar;
	real delta;
	real* hs;
	int R;
	real h_offset;
	real isamps;
	real nom_ratio;
} varsamp, *VARSAMP;

extern VARSAMP create_varsamp ( int run, int size, real* in, real* out,  
	int in_rate, int out_rate, real fc, real fc_low, int R, real gain, real var, int varmode);

extern void destroy_varsamp (VARSAMP a);

extern void flush_varsamp (VARSAMP a);

extern int xvarsamp (VARSAMP a, real var);

extern void setBuffers_varsamp (VARSAMP a, real* in, real* out);

extern void setSize_varsamp (VARSAMP a, int size);

extern void setInRate_varsamp (VARSAMP a, int rate);

extern void setOutRate_varsamp (VARSAMP a, int rate);

extern void setFCLow_varsamp (VARSAMP a, real fc_low);

extern void setBandwidth_varsamp (VARSAMP a, real fc_low, real fc_high);

#endif
