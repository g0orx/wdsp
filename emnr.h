/*  emnr.h

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

#ifndef _emnr_h
#define _emnr_h

typedef struct _emnr
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
	real ogain;
	real gain;
	int nsamps;
	int iainidx;
	int iaoutidx;
	int init_oainidx;
	int oainidx;
	int oaoutidx;
	int saveidx;
	fftw_plan Rfor;
	fftw_plan Rrev;
	struct _g
	{
		int gain_method;
		int npe_method;
		int ae_run;
		real msize;
		real* mask;
		real* y;
		real* lambda_y;
		real* lambda_d;
		real* prev_mask;
		real* prev_gamma;
		real gf1p5;
		real alpha;
		real eps_floor;
		real gamma_max;
		real q;
		real gmax;
		//
		real* GG;
		real* GGS;
		FILE* fileb;
	} g;
	struct _npest
	{
		int incr;
		real rate;
		int msize;
		real* lambda_y;
		real* lambda_d;
		real* p;
		real* alphaOptHat;
		real alphaC;
		real alphaCsmooth;
		real alphaCmin;
		real* alphaHat;
		real alphaMax;
		real* sigma2N;
		real alphaMin_max_value;
		real snrq;
		real betamax;
		real* pbar;
		real* p2bar;
		real invQeqMax;
		real av;
		real* Qeq;
		int U;
		real Dtime;
		int V;
		int D;
		real MofD;
		real MofV;
		real* bmin;
		real* bmin_sub;
		int* k_mod;
		real* actmin;
		real* actmin_sub;
		int subwc;
		int* lmin_flag;
		real* pmin_u;
		real invQbar_points[4];
		real nsmax[4];
		real** actminbuff;
		int amb_idx;
	} np;
	struct _npests
	{
		int incr;
		real rate;
		int msize;
		real* lambda_y;
		real* lambda_d;
		
		real alpha_pow;
		real alpha_Pbar;
		real epsH1;
		real epsH1r;

		real* sigma2N;
		real* PH1y;
		real* Pbar;
		real* EN2y;
	} nps;
	struct _ae
	{
		int msize;
		real* lambda_y;
		real zetaThresh;
		real psi;
		real* nmask;
	} ae;
}emnr, *EMNR;

extern EMNR create_emnr (int run, int position, int size, real* in, real* out, int fsize, int ovrlp, 
	int rate, int wintype, real gain, int gain_method, int npe_method, int ae_run);

extern void destroy_emnr (EMNR a);

extern void flush_emnr (EMNR a);

extern void xemnr (EMNR a, int pos);

extern void setBuffers_emnr (EMNR a, real* in, real* out);

extern void setSamplerate_emnr (EMNR a, int rate);

extern void setSize_emnr (EMNR a, int size);

#endif
