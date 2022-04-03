/*  cfcomp.h

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

#ifndef _cfcomp_h
#define _cfcomp_h

typedef struct _cfcomp
{
	int run;
	int position;
	int bsize;
	real* in;
	real* out;
	int fsize;
	int ovrlp;
	int incr;
	real* window;
	int iasize;
	real* inaccum;
	real* forfftin;
	real* forfftout;
	int msize;
	real* mask;
	real* revfftin;
	real* revfftout;
	real** save;
	int oasize;
	real* outaccum;
	real rate;
	int wintype;
	real pregain;
	real postgain;
	int nsamps;
	int iainidx;
	int iaoutidx;
	int init_oainidx;
	int oainidx;
	int oaoutidx;
	int saveidx;
	fftw_plan Rfor;
	fftw_plan Rrev;

	int comp_method;
	int nfreqs;
	real* F;
	real* G;
	real* E;
	real* fp;
	real* gp;
	real* ep;
	real* comp;
	real precomp;
	real precomplin;
	real* peq;
	int peq_run;
	real prepeq;
	real prepeqlin;
	real winfudge;

	real gain;
	real mtau;
	real mmult;
}cfcomp, *CFCOMP;

extern CFCOMP create_cfcomp (int run, int position, int peq_run, int size, real* in, real* out, int fsize, int ovrlp, 
	int rate, int wintype, int comp_method, int nfreqs, real precomp, real prepeq, real* F, real* G, real* E, real mtau);

extern void destroy_cfcomp (CFCOMP a);

extern void flush_cfcomp (CFCOMP a);

extern void xcfcomp (CFCOMP a, int pos);

extern void setBuffers_cfcomp (CFCOMP a, real* in, real* out);

extern void setSamplerate_cfcomp (CFCOMP a, int rate);

extern void setSize_cfcomp (CFCOMP a, int size);

#endif
