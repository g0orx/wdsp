/*  rmatch.h

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

#ifndef _rmatch_h
#define _rmatch_h

#include "varsamp.h"

typedef struct _mav
{
	int ringmin;
	int ringmax;		// must be a power of two
	int* ring;
	int mask;
	int i;
	int load;
	int sum;
	real nom_value;
} mav, *MAV;

typedef struct _aamav
{
	int ringmin;
	int ringmax;		// must be a power of two
	int* ring;
	int mask;
	int i;
	int load;
	int pos;
	int neg;
	real nom_ratio;
} aamav, *AAMAV;

typedef struct _rmatch
{
	volatile long run;
	real* in;
	real* out;
	int insize;
	int outsize;
	real* resout;
	int nom_inrate;
	int nom_outrate;
	real nom_ratio;
	real inv_nom_ratio;
	real fc_high;
	real fc_low;
	real gain;
	real startup_delay;
	int auto_ringsize;
	int ringsize;
	int rsize;
	real* ring;
	int n_ring;
	int iin;
	int iout;
	real var;
	int R;
	AAMAV ffmav;
	MAV propmav;
	int ff_ringmin;
	int ff_ringmax;			// must be a power of two
	real ff_alpha;
	real feed_forward;
	int prop_ringmin;
	int prop_ringmax;		// must be a power of two
	real prop_gain;
	real pr_gain;
	real av_deviation;
	VARSAMP v;
	int varmode;
	CRITICAL_SECTION cs_ring;
	CRITICAL_SECTION cs_var;
	// blend / slew
	real tslew;
	int ntslew;
	real* cslew;
	real* baux;
	real dlast[2];
	int ucnt;
	// variables to check start-up time for control to become active
	unsigned int readsamps;
	unsigned int writesamps;
	unsigned int read_startup;
	unsigned int write_startup;
	int control_flag;
	// diagnostics
	volatile long underflows;
	volatile long overflows;
	int force;
	real fvar;
} rmatch, *RMATCH;

extern __declspec (dllexport) void* create_rmatchV(int in_size, int out_size, int nom_inrate, int nom_outrate, int ringsize);

extern __declspec (dllexport) void destroy_rmatchV (void* ptr);

extern __declspec (dllexport) void xrmatchOUT (void* b, real* out);

extern __declspec (dllexport) void xrmatchIN (void* b, real* in);

extern __declspec (dllexport) void setRMatchInsize (void* ptr, int insize);

extern __declspec (dllexport) void setRMatchOutsize (void* ptr, int outsize);

extern __declspec (dllexport) void setRMatchNomInrate (void* ptr, int nom_inrate);

extern __declspec (dllexport) void setRMatchNomOutrate (void* ptr, int nom_outrate);

extern __declspec (dllexport) void setRMatchRingsize (void* ptr, int ringsize);

extern __declspec (dllexport) void getRMatchDiags (void* b, int* underflows, int* overflows, real* var, int* ringsize);

extern __declspec (dllexport) void resetRMatchDiags (void* b);

extern __declspec (dllexport) void forceRMatchVar (void* b, int force, real fvar);

#endif
