/*  emnr.c

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
#define _CRT_SECURE_NO_WARNINGS
#include "comm.h"

#if defined(linux) || defined(__APPLE__)
#include "calculus.h"
#endif
	
/********************************************************************************************************
*																										*
*											Special Functions											*
*																										*
********************************************************************************************************/

// MODIFIED BESSEL FUNCTIONS OF THE 0TH AND 1ST ORDERS, Polynomial Approximations
// M. Abramowitz and I. Stegun, Eds., "Handbook of Mathematical Functions."  Washington, DC:  National
//      Bureau of Standards, 1964.
// Shanjie Zhang and Jianming Jin, "Computation of Special Functions."  New York, NY, John Wiley and Sons,
//      Inc., 1996.  [Sample code given in FORTRAN]

real bessI0 (real x)
{
	real res, p;
	if (x == 0.0)
		res = 1.0;
	else
	{
		if (x < 0.0) x = -x;
		if (x <= 3.75)
		{
			p = x / 3.75;
			p = p * p;
			res = ((((( 0.0045813  * p
					  + 0.0360768) * p
					  + 0.2659732) * p
					  + 1.2067492) * p
					  + 3.0899424) * p
					  + 3.5156229) * p
					  + 1.0;
		}
		else
		{
			p = 3.75 / x;
			res = exp (x) / sqrt (x)
				  * (((((((( + 0.00392377  * p
						     - 0.01647633) * p
						     + 0.02635537) * p
						     - 0.02057706) * p
						     + 0.00916281) * p
						     - 0.00157565) * p
						     + 0.00225319) * p
						     + 0.01328592) * p
						     + 0.39894228);
		}
	}
	return res;
}

real bessI1 (real x)
{
	
	real res, p;
	if (x == 0.0)
		res = 0.0;
	else
	{
		if (x < 0.0) x = -x;
		if (x <= 3.75)
		{
			p = x / 3.75;
			p = p * p;
			res = x 
				  * (((((( 0.00032411  * p
					     + 0.00301532) * p
					     + 0.02658733) * p
					     + 0.15084934) * p
					     + 0.51498869) * p
					     + 0.87890594) * p
					     + 0.5);
		}
		else
		{
			p = 3.75 / x;
			res = exp (x) / sqrt (x)
				  * (((((((( - 0.00420059  * p
						     + 0.01787654) * p
						     - 0.02895312) * p
						     + 0.02282967) * p
						     - 0.01031555) * p
						     + 0.00163801) * p
						     - 0.00362018) * p
						     - 0.03988024) * p
						     + 0.39894228);
		}
	}
	return res;
}

// EXPONENTIAL INTEGRAL, E1(x)
// M. Abramowitz and I. Stegun, Eds., "Handbook of Mathematical Functions."  Washington, DC:  National
//      Bureau of Standards, 1964.
// Shanjie Zhang and Jianming Jin, "Computation of Special Functions."  New York, NY, John Wiley and Sons,
//      Inc., 1996.  [Sample code given in FORTRAN]

real e1xb (real x)
{
	real e1, ga, r, t, t0;
	int k, m;
	if (x == 0.0) 
		e1 = REAL_MAX;
	else if (x <= 1.0)
	{
        e1 = 1.0;
        r = 1.0;

        for (k = 1; k <= 25; k++)
		{
			r = -r * k * x / ((k + 1.0)*(k + 1.0));
			e1 = e1 + r;
			if ( fabs (r) <= fabs (e1) * 1.0e-15 )
				break;
        }

        ga = 0.5772156649015328;
        e1 = - ga - log (x) + x * e1;
	}
      else
	{
        m = 20 + (int)(80.0 / x);
        t0 = 0.0;
        for (k = m; k >= 1; k--)
			t0 = (real)k / (1.0 + k / (x + t0));
        t = 1.0 / (x + t0);
        e1 = exp (- x) * t;
	}
    return e1;
}

/********************************************************************************************************
*																										*
*											Main Body of Code											*
*																										*
********************************************************************************************************/

void calc_window (EMNR a)
{
	int i;
	real arg, sum, inv_coherent_gain;
	switch (a->wintype)
	{
	case 0:
		arg = 2.0 * PI / (real)a->fsize;
		sum = 0.0;
		for (i = 0; i < a->fsize; i++)
		{
			a->window[i] = sqrt (0.54 - 0.46 * cos((real)i * arg));
			sum += a->window[i];
		}
		inv_coherent_gain = (real)a->fsize / sum;
		for (i = 0; i < a->fsize; i++)
			a->window[i] *= inv_coherent_gain;
		break;
	}
}

void interpM (real* res, real x, int nvals, real* xvals, real* yvals)
{
	if (x <= xvals[0])
		*res = yvals[0];
	else if (x >= xvals[nvals - 1])
		*res = yvals[nvals - 1];
	else
	{
		int idx = 0;
		real xllow, xlhigh, frac;
		while (x >= xvals[idx])  idx++;
		xllow = log10 (xvals[idx - 1]);
		xlhigh = log10(xvals[idx]);
		frac = (log10 (x) - xllow) / (xlhigh - xllow);
		*res = yvals[idx - 1] + frac * (yvals[idx] - yvals[idx - 1]);
	}
}

void calc_emnr(EMNR a)
{
	int i;
	real Dvals[18] = { 1.0, 2.0, 5.0, 8.0, 10.0, 15.0, 20.0, 30.0, 40.0,
		60.0, 80.0, 120.0, 140.0, 160.0, 180.0, 220.0, 260.0, 300.0 };
	real Mvals[18] = { 0.000, 0.260, 0.480, 0.580, 0.610, 0.668, 0.705, 0.762, 0.800,
		0.841, 0.865, 0.890, 0.900, 0.910, 0.920, 0.930, 0.935, 0.940 };
	real Hvals[18] = { 0.000, 0.150, 0.480, 0.780, 0.980, 1.550, 2.000, 2.300, 2.520,
		3.100, 3.380, 4.150, 4.350, 4.250, 3.900, 4.100, 4.700, 5.000 };
	a->incr = a->fsize / a->ovrlp;
	a->gain = a->ogain / a->fsize / (real)a->ovrlp;
	if (a->fsize > a->bsize)
		a->iasize = a->fsize;
	else
		a->iasize = a->bsize + a->fsize - a->incr;
	a->iainidx = 0;
	a->iaoutidx = 0;
	if (a->fsize > a->bsize)
	{
		if (a->bsize > a->incr)  a->oasize = a->bsize;
		else					 a->oasize = a->incr;
		a->oainidx = (a->fsize - a->bsize - a->incr) % a->oasize;
	}
	else
	{
		a->oasize = a->bsize;
		a->oainidx = a->fsize - a->incr;
	}
	a->init_oainidx = a->oainidx;
	a->oaoutidx = 0;
	a->msize = a->fsize / 2 + 1;
	a->window = (real *)malloc0(a->fsize * sizeof(real));
	a->inaccum = (real *)malloc0(a->iasize * sizeof(real));
	a->forfftin = (real *)malloc0(a->fsize * sizeof(real));
	a->forfftout = (real *)malloc0(a->msize * sizeof(complex));
	a->mask = (real *)malloc0(a->msize * sizeof(real));
	a->revfftin = (real *)malloc0(a->msize * sizeof(complex));
	a->revfftout = (real *)malloc0(a->fsize * sizeof(real));
	a->save = (real **)malloc0(a->ovrlp * sizeof(real *));
	for (i = 0; i < a->ovrlp; i++)
		a->save[i] = (real *)malloc0(a->fsize * sizeof(real));
	a->outaccum = (real *)malloc0(a->oasize * sizeof(real));
	a->nsamps = 0;
	a->saveidx = 0;
	a->Rfor = fftw_plan_dft_r2c_1d(a->fsize, a->forfftin, (fftw_complex *)a->forfftout, FFTW_ESTIMATE);
	a->Rrev = fftw_plan_dft_c2r_1d(a->fsize, (fftw_complex *)a->revfftin, a->revfftout, FFTW_ESTIMATE);
	calc_window(a);

	a->g.msize = a->msize;
	a->g.mask = a->mask;
	a->g.y = a->forfftout;
	a->g.lambda_y = (real *)malloc0(a->msize * sizeof(real));
	a->g.lambda_d = (real *)malloc0(a->msize * sizeof(real));
	a->g.prev_gamma = (real *)malloc0(a->msize * sizeof(real));
	a->g.prev_mask = (real *)malloc0(a->msize * sizeof(real));

	a->g.gf1p5 = sqrt(PI) / 2.0;
	{
		real tau = -128.0 / 8000.0 / log(0.98);
		a->g.alpha = exp(-a->incr / a->rate / tau);
	}
	a->g.eps_floor = REAL_EPSILON;
	a->g.gamma_max = 1000.0;
	a->g.q = 0.2;
	for (i = 0; i < a->g.msize; i++)
	{
		a->g.prev_mask[i] = 1.0;
		a->g.prev_gamma[i] = 1.0;
	}
	a->g.gmax = 10000.0;
	//
	a->g.GG = (real *)malloc0(241 * 241 * sizeof(real));
	a->g.GGS = (real *)malloc0(241 * 241 * sizeof(real));
#if defined(linux) || defined(__APPLE__)
        memcpy(a->g.GG, GG, 241 * 241 * sizeof(real));
        memcpy(a->g.GGS, GGS, 241 * 241 * sizeof(real));
#else

	a->g.fileb = fopen("calculus", "rb");
	fread(a->g.GG, sizeof(real), 241 * 241, a->g.fileb);
	fread(a->g.GGS, sizeof(real), 241 * 241, a->g.fileb);
	fclose(a->g.fileb);
#endif
	//

	a->np.incr = a->incr;
	a->np.rate = a->rate;
	a->np.msize = a->msize;
	a->np.lambda_y = a->g.lambda_y;
	a->np.lambda_d = a->g.lambda_d;

	{
		real tau = -128.0 / 8000.0 / log(0.7);
		a->np.alphaCsmooth = exp(-a->np.incr / a->np.rate / tau);
	}
	{
		real tau = -128.0 / 8000.0 / log(0.96);
		a->np.alphaMax = exp(-a->np.incr / a->np.rate / tau);
	}
	{
		real tau = -128.0 / 8000.0 / log(0.7);
		a->np.alphaCmin = exp(-a->np.incr / a->np.rate / tau);
	}
	{
		real tau = -128.0 / 8000.0 / log(0.3);
		a->np.alphaMin_max_value = exp(-a->np.incr / a->np.rate / tau);
	}
	a->np.snrq = -a->np.incr / (0.064 * a->np.rate);
	{
		real tau = -128.0 / 8000.0 / log(0.8);
		a->np.betamax = exp(-a->np.incr / a->np.rate / tau);
	}
	a->np.invQeqMax = 0.5;
	a->np.av = 2.12;
	a->np.Dtime = 8.0 * 12.0 * 128.0 / 8000.0;
	a->np.U = 8;
	a->np.V = (int)(0.5 + (a->np.Dtime * a->np.rate / (a->np.U * a->np.incr)));
	if (a->np.V < 4) a->np.V = 4;
	if ((a->np.U = (int)(0.5 + (a->np.Dtime * a->np.rate / (a->np.V * a->np.incr)))) < 1) a->np.U = 1;
	a->np.D = a->np.U * a->np.V;
	interpM(&a->np.MofD, a->np.D, 18, Dvals, Mvals);
	interpM(&a->np.MofV, a->np.V, 18, Dvals, Mvals);
	a->np.invQbar_points[0] = 0.03;
	a->np.invQbar_points[1] = 0.05;
	a->np.invQbar_points[2] = 0.06;
	a->np.invQbar_points[3] = REAL_MAX;
	{
		real db;
		db = 10.0 * log10(8.0) / (12.0 * 128 / 8000);
		a->np.nsmax[0] = pow(10.0, db / 10.0 * a->np.V * a->np.incr / a->np.rate);
		db = 10.0 * log10(4.0) / (12.0 * 128 / 8000);
		a->np.nsmax[1] = pow(10.0, db / 10.0 * a->np.V * a->np.incr / a->np.rate);
		db = 10.0 * log10(2.0) / (12.0 * 128 / 8000);
		a->np.nsmax[2] = pow(10.0, db / 10.0 * a->np.V * a->np.incr / a->np.rate);
		db = 10.0 * log10(1.2) / (12.0 * 128 / 8000);
		a->np.nsmax[3] = pow(10.0, db / 10.0 * a->np.V * a->np.incr / a->np.rate);
	}

	a->np.p = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.alphaOptHat = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.alphaHat = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.sigma2N = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.pbar = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.p2bar = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.Qeq = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.bmin = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.bmin_sub = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.k_mod = (int *)malloc0(a->np.msize * sizeof(int));
	a->np.actmin = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.actmin_sub = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.lmin_flag = (int *)malloc0(a->np.msize * sizeof(int));
	a->np.pmin_u = (real *)malloc0(a->np.msize * sizeof(real));
	a->np.actminbuff = (real**)malloc0(a->np.U     * sizeof(real*));
	for (i = 0; i < a->np.U; i++)
		a->np.actminbuff[i] = (real *)malloc0(a->np.msize * sizeof(real));

	{
		int k, ku;
		a->np.alphaC = 1.0;
		a->np.subwc = a->np.V;
		a->np.amb_idx = 0;
		for (k = 0; k < a->np.msize; k++) a->np.lambda_y[k] = 0.5;
		memcpy(a->np.p, a->np.lambda_y, a->np.msize * sizeof(real));
		memcpy(a->np.sigma2N, a->np.lambda_y, a->np.msize * sizeof(real));
		memcpy(a->np.pbar, a->np.lambda_y, a->np.msize * sizeof(real));
		memcpy(a->np.pmin_u, a->np.lambda_y, a->np.msize * sizeof(real));
		for (k = 0; k < a->np.msize; k++)
		{
			a->np.p2bar[k] = a->np.lambda_y[k] * a->np.lambda_y[k];
			a->np.actmin[k] = REAL_MAX;
			a->np.actmin_sub[k] = REAL_MAX;
			for (ku = 0; ku < a->np.U; ku++)
				a->np.actminbuff[ku][k] = REAL_MAX;
		}
		memset(a->np.lmin_flag, 0, a->np.msize * sizeof(int));
	}

	a->nps.incr = a->incr;
	a->nps.rate = a->rate;
	a->nps.msize = a->msize;
	a->nps.lambda_y = a->g.lambda_y;
	a->nps.lambda_d = a->g.lambda_d;

	{
		real tau = -128.0 / 8000.0 / log(0.8);
		a->nps.alpha_pow = exp(-a->nps.incr / a->nps.rate / tau);
	}
	{
		real tau = -128.0 / 8000.0 / log(0.9);
		a->nps.alpha_Pbar = exp(-a->nps.incr / a->nps.rate / tau);
	}
	a->nps.epsH1 = pow(10.0, 15.0 / 10.0);
	a->nps.epsH1r = a->nps.epsH1 / (1.0 + a->nps.epsH1);

	a->nps.sigma2N = (real *)malloc0(a->nps.msize * sizeof(real));
	a->nps.PH1y = (real *)malloc0(a->nps.msize * sizeof(real));
	a->nps.Pbar = (real *)malloc0(a->nps.msize * sizeof(real));
	a->nps.EN2y = (real *)malloc0(a->nps.msize * sizeof(real));

	for (i = 0; i < a->nps.msize; i++)
	{
		a->nps.sigma2N[i] = 0.5;
		a->nps.Pbar[i] = 0.5;
	}

	a->ae.msize = a->msize;
	a->ae.lambda_y = a->g.lambda_y;

	a->ae.zetaThresh = 0.75;
	a->ae.psi = 10.0;

	a->ae.nmask = (real *)malloc0(a->ae.msize * sizeof(real));
}

void decalc_emnr(EMNR a)
{
	int i;
	_aligned_free(a->ae.nmask);

	_aligned_free(a->nps.EN2y);
	_aligned_free(a->nps.Pbar);
	_aligned_free(a->nps.PH1y);
	_aligned_free(a->nps.sigma2N);

	for (i = 0; i < a->np.U; i++)
		_aligned_free(a->np.actminbuff[i]);
	_aligned_free(a->np.actminbuff);
	_aligned_free(a->np.pmin_u);
	_aligned_free(a->np.lmin_flag);
	_aligned_free(a->np.actmin_sub);
	_aligned_free(a->np.actmin);
	_aligned_free(a->np.k_mod);
	_aligned_free(a->np.bmin_sub);
	_aligned_free(a->np.bmin);
	_aligned_free(a->np.Qeq);
	_aligned_free(a->np.p2bar);
	_aligned_free(a->np.pbar);
	_aligned_free(a->np.sigma2N);
	_aligned_free(a->np.alphaHat);
	_aligned_free(a->np.alphaOptHat);
	_aligned_free(a->np.p);

	_aligned_free(a->g.GGS);
	_aligned_free(a->g.GG);
	_aligned_free(a->g.prev_mask);
	_aligned_free(a->g.prev_gamma);
	_aligned_free(a->g.lambda_d);
	_aligned_free(a->g.lambda_y);

	fftw_destroy_plan(a->Rrev);
	fftw_destroy_plan(a->Rfor);
	_aligned_free(a->outaccum);
	for (i = 0; i < a->ovrlp; i++)
		_aligned_free(a->save[i]);
	_aligned_free(a->save);
	_aligned_free(a->revfftout);
	_aligned_free(a->revfftin);
	_aligned_free(a->mask);
	_aligned_free(a->forfftout);
	_aligned_free(a->forfftin);
	_aligned_free(a->inaccum);
	_aligned_free(a->window);
}

EMNR create_emnr (int run, int position, int size, real* in, real* out, int fsize, int ovrlp, 
	int rate, int wintype, real gain, int gain_method, int npe_method, int ae_run)
{
	EMNR a = (EMNR) malloc0 (sizeof (emnr));
	
	a->run = run;
	a->position = position;
	a->bsize = size;
	a->in = in;
	a->out = out;
	a->fsize = fsize;
	a->ovrlp = ovrlp;
	a->rate = rate;
	a->wintype = wintype;
	a->ogain = gain;
	a->g.gain_method = gain_method;
	a->g.npe_method = npe_method;
	a->g.ae_run = ae_run;
	calc_emnr (a);
	return a;
}

void flush_emnr (EMNR a)
{
	int i;
	memset (a->inaccum, 0, a->iasize * sizeof (real));
	for (i = 0; i < a->ovrlp; i++)
		memset (a->save[i], 0, a->fsize * sizeof (real));
	memset (a->outaccum, 0, a->oasize * sizeof (real));
	a->nsamps   = 0;
	a->iainidx  = 0;
	a->iaoutidx = 0;
	a->oainidx  = a->init_oainidx;
	a->oaoutidx = 0;
	a->saveidx  = 0;
}

void destroy_emnr (EMNR a)
{
	decalc_emnr (a);
	_aligned_free (a);
}

void LambdaD(EMNR a)
{
	int k;
	real f0, f1, f2, f3;
	real sum_prev_p;
	real sum_lambda_y;
	real alphaCtilda;
	real sum_prev_sigma2N;
	real alphaMin, SNR;
	real beta, varHat, invQeq;
	real invQbar;
	real bc;
	real QeqTilda, QeqTildaSub;
	real noise_slope_max;
	
	sum_prev_p = 0.0;
	sum_lambda_y = 0.0;
	sum_prev_sigma2N = 0.0;
	for (k = 0; k < a->np.msize; k++)
	{
		sum_prev_p += a->np.p[k];
		sum_lambda_y += a->np.lambda_y[k];
		sum_prev_sigma2N += a->np.sigma2N[k];
	}
	for (k = 0; k < a->np.msize; k++)
	{
		f0 = a->np.p[k] / a->np.sigma2N[k] - 1.0;
		a->np.alphaOptHat[k] = 1.0 / (1.0 + f0 * f0);
	}
	SNR = sum_prev_p / sum_prev_sigma2N;
	alphaMin = min (a->np.alphaMin_max_value, pow (SNR, a->np.snrq));
	for (k = 0; k < a->np.msize; k++)
		if (a->np.alphaOptHat[k] < alphaMin) a->np.alphaOptHat[k] = alphaMin;
	f1 = sum_prev_p / sum_lambda_y - 1.0;
	alphaCtilda = 1.0 / (1.0 + f1 * f1);
	a->np.alphaC = a->np.alphaCsmooth * a->np.alphaC + (1.0 - a->np.alphaCsmooth) * max (alphaCtilda, a->np.alphaCmin);
	f2 = a->np.alphaMax * a->np.alphaC;
	for (k = 0; k < a->np.msize; k++)
		a->np.alphaHat[k] = f2 * a->np.alphaOptHat[k];
	for (k = 0; k < a->np.msize; k++)
		a->np.p[k] = a->np.alphaHat[k] * a->np.p[k] + (1.0 - a->np.alphaHat[k]) * a->np.lambda_y[k];
	invQbar = 0.0;
	for (k = 0; k < a->np.msize; k++)
	{
		beta = min (a->np.betamax, a->np.alphaHat[k] * a->np.alphaHat[k]);
		a->np.pbar[k] = beta * a->np.pbar[k] + (1.0 - beta) * a->np.p[k];
		a->np.p2bar[k] = beta * a->np.p2bar[k] + (1.0 - beta) * a->np.p[k] * a->np.p[k];
		varHat = a->np.p2bar[k] - a->np.pbar[k] * a->np.pbar[k];
		invQeq = varHat / (2.0 * a->np.sigma2N[k] * a->np.sigma2N[k]);
		if (invQeq > a->np.invQeqMax) invQeq = a->np.invQeqMax;
		a->np.Qeq[k] = 1.0 / invQeq;
		invQbar += invQeq;
	}
	invQbar /= (real)a->np.msize;
	bc = 1.0 + a->np.av * sqrt (invQbar);
	for (k = 0; k < a->np.msize; k++)
	{
		QeqTilda    = (a->np.Qeq[k] - 2.0 * a->np.MofD) / (1.0 - a->np.MofD);
		QeqTildaSub = (a->np.Qeq[k] - 2.0 * a->np.MofV) / (1.0 - a->np.MofV);
		a->np.bmin[k]     = 1.0 + 2.0 * (a->np.D - 1.0) / QeqTilda;
		a->np.bmin_sub[k] = 1.0 + 2.0 * (a->np.V - 1.0) / QeqTildaSub;
	}
	memset (a->np.k_mod, 0, a->np.msize * sizeof (int));
	for (k = 0; k < a->np.msize; k++)
	{
		f3 = a->np.p[k] * a->np.bmin[k] * bc;
		if (f3 < a->np.actmin[k])
		{
			a->np.actmin[k] = f3;
			a->np.actmin_sub[k] = a->np.p[k] * a->np.bmin_sub[k] * bc;
			a->np.k_mod[k] = 1;
		}
	}
	if (a->np.subwc == a->np.V)
	{
		if      (invQbar < a->np.invQbar_points[0]) noise_slope_max = a->np.nsmax[0];
		else if (invQbar < a->np.invQbar_points[1]) noise_slope_max = a->np.nsmax[1];
		else if (invQbar < a->np.invQbar_points[2]) noise_slope_max = a->np.nsmax[2];
		else                                        noise_slope_max = a->np.nsmax[3];

		for (k = 0; k < a->np.msize; k++)
		{
			int ku;
			real min;
			if (a->np.k_mod[k])
				a->np.lmin_flag[k] = 0;
			a->np.actminbuff[a->np.amb_idx][k] = a->np.actmin[k];
			min = REAL_MAX;
			for (ku = 0; ku < a->np.U; ku++)
				if (a->np.actminbuff[ku][k] < min) min = a->np.actminbuff[ku][k];
			a->np.pmin_u[k] = min;
			if ((a->np.lmin_flag[k] == 1) 
				&& (a->np.actmin_sub[k] < noise_slope_max * a->np.pmin_u[k])
				&& (a->np.actmin_sub[k] >                   a->np.pmin_u[k]))
			{
				a->np.pmin_u[k] = a->np.actmin_sub[k];
				for (ku = 0; ku < a->np.U; ku++)
					a->np.actminbuff[ku][k] = a->np.actmin_sub[k];
			}
			a->np.lmin_flag[k] = 0;
			a->np.actmin[k] = REAL_MAX;
			a->np.actmin_sub[k] = REAL_MAX;
		}
		if (++a->np.amb_idx == a->np.U) a->np.amb_idx = 0;
		a->np.subwc = 1;
	}
	else 
	{
		if (a->np.subwc > 1)
		{
			for (k = 0; k < a->np.msize; k++)
			{
				if (a->np.k_mod[k])
				{
					a->np.lmin_flag[k] = 1;
					a->np.sigma2N[k] = min (a->np.actmin_sub[k], a->np.pmin_u[k]);
					a->np.pmin_u[k] = a->np.sigma2N[k];
				}
			}
		}
		++a->np.subwc;
	}
	memcpy (a->np.lambda_d, a->np.sigma2N, a->np.msize * sizeof (real));
}

void LambdaDs (EMNR a)
{
	int k;
	for (k = 0; k < a->nps.msize; k++)
	{
		a->nps.PH1y[k] = 1.0 / (1.0 + (1.0 + a->nps.epsH1) * exp (- a->nps.epsH1r * a->nps.lambda_y[k] / a->nps.sigma2N[k]));
		a->nps.Pbar[k] = a->nps.alpha_Pbar * a->nps.Pbar[k] + (1.0 - a->nps.alpha_Pbar) * a->nps.PH1y[k];
		if (a->nps.Pbar[k] > 0.99)
			a->nps.PH1y[k] = min (a->nps.PH1y[k], 0.99);
		a->nps.EN2y[k] = (1.0 - a->nps.PH1y[k]) * a->nps.lambda_y[k] + a->nps.PH1y[k] * a->nps.sigma2N[k];
		a->nps.sigma2N[k] = a->nps.alpha_pow * a->nps.sigma2N[k] + (1.0 - a->nps.alpha_pow) * a->nps.EN2y[k];
	}
	memcpy (a->nps.lambda_d, a->nps.sigma2N, a->nps.msize * sizeof (real));
}

void aepf(EMNR a)
{
	int k, m;
	int N, n;
	real sumPre, sumPost, zeta, zetaT;
	sumPre = 0.0;
	sumPost = 0.0;
	for (k = 0; k < a->ae.msize; k++)
	{
		sumPre += a->ae.lambda_y[k];
		sumPost += a->mask[k] * a->mask[k] * a->ae.lambda_y[k];
	}
	zeta = sumPost / sumPre;
	if (zeta >= a->ae.zetaThresh)
		zetaT = 1.0;
	else
		zetaT = zeta;
	if (zetaT == 1.0)
		N = 1;
	else
		N = 1 + 2 * (int)(0.5 + a->ae.psi * (1.0 - zetaT / a->ae.zetaThresh));
	n = N / 2;
	for (k = n; k < (a->ae.msize - n); k++)
	{
		a->ae.nmask[k] = 0.0;
		for (m = k - n; m <= (k + n); m++)
			a->ae.nmask[k] += a->mask[m];
		a->ae.nmask[k] /= (real)N;
	}
	memcpy (a->mask + n, a->ae.nmask, (a->ae.msize - 2 * n) * sizeof (real));
}

real getKey(real* type, real gamma, real xi)
{
	int ngamma1, ngamma2, nxi1, nxi2;
	real tg, tx, dg, dx;
	const real dmin = 0.001;
	const real dmax = 1000.0;
	if (gamma <= dmin)
	{
		ngamma1 = ngamma2 = 0;
		tg = 0.0;
	}
	else if (gamma >= dmax)
	{
		ngamma1 = ngamma2 = 240;
		tg = 60.0;
	}
	else
	{
		tg = 10.0 * log10(gamma / dmin);
		ngamma1 = (int)(4.0 * tg);
		ngamma2 = ngamma1 + 1;
	}
	if (xi <= dmin)
	{
		nxi1 = nxi2 = 0;
		tx = 0.0;
	}
	else if (xi >= dmax)
	{
		nxi1 = nxi2 = 240;
		tx = 60.0;
	}
	else
	{
		tx = 10.0 * log10(xi / dmin);
		nxi1 = (int)(4.0 * tx);
		nxi2 = nxi1 + 1;
	}
	dg = (tg - 0.25 * ngamma1) / 0.25;
	dx = (tx - 0.25 * nxi1) / 0.25;
	return (1.0 - dg)  * (1.0 - dx) * type[241 * nxi1 + ngamma1]
		+  (1.0 - dg)  *        dx  * type[241 * nxi2 + ngamma1]
		+         dg   * (1.0 - dx) * type[241 * nxi1 + ngamma2]
		+         dg   *        dx  * type[241 * nxi2 + ngamma2];
}

void calc_gain (EMNR a)
{
	int k;
	for (k = 0; k < a->g.msize; k++)
	{
		a->g.lambda_y[k] = a->g.y[2 * k + 0] * a->g.y[2 * k + 0] + a->g.y[2 * k + 1] * a->g.y[2 * k + 1];
	}
	switch (a->g.npe_method)
	{
	case 0:
		LambdaD(a);
		break;
	case 1:
		LambdaDs(a);
		break;
	}
	switch (a->g.gain_method)
	{
	case 0:
		{
			real gamma, eps_hat, v;
			for (k = 0; k < a->msize; k++)
			{
				gamma = min (a->g.lambda_y[k] / a->g.lambda_d[k], a->g.gamma_max);
				eps_hat = a->g.alpha * a->g.prev_mask[k] * a->g.prev_mask[k] * a->g.prev_gamma[k]
					+ (1.0 - a->g.alpha) * max (gamma - 1.0, a->g.eps_floor);
				v = (eps_hat / (1.0 + eps_hat)) * gamma;
				a->g.mask[k] = a->g.gf1p5 * sqrt (v) / gamma * exp (- 0.5 * v)
					* ((1.0 + v) * bessI0 (0.5 * v) + v * bessI1 (0.5 * v));
				{
					real v2 = min (v, 700.0);
					real eta = a->g.mask[k] * a->g.mask[k] * a->g.lambda_y[k] / a->g.lambda_d[k];
					real eps = eta / (1.0 - a->g.q);
					real witchHat = (1.0 - a->g.q) / a->g.q * exp (v2) / (1.0 + eps);
					a->g.mask[k] *= witchHat / (1.0 + witchHat);
				}
				if (a->g.mask[k] > a->g.gmax) a->g.mask[k] = a->g.gmax;
				if (a->g.mask[k] != a->g.mask[k]) a->g.mask[k] = 0.01;
				a->g.prev_gamma[k] = gamma;
				a->g.prev_mask[k] = a->g.mask[k];
			}
			break;
		}
	case 1:
		{
			real gamma, eps_hat, v, ehr;
			for (k = 0; k < a->g.msize; k++)
			{
				gamma = min (a->g.lambda_y[k] / a->g.lambda_d[k], a->g.gamma_max);
				eps_hat = a->g.alpha * a->g.prev_mask[k] * a->g.prev_mask[k] * a->g.prev_gamma[k]
					+ (1.0 - a->g.alpha) * max (gamma - 1.0, a->g.eps_floor);
				ehr = eps_hat / (1.0 + eps_hat);
				v = ehr * gamma;
				if((a->g.mask[k] = ehr * exp (min (700.0, 0.5 * e1xb(v)))) > a->g.gmax) a->g.mask[k] = a->g.gmax;
				if (a->g.mask[k] != a->g.mask[k])a->g.mask[k] = 0.01;
				a->g.prev_gamma[k] = gamma;
				a->g.prev_mask[k] = a->g.mask[k];
			}
			break;
		}
	case 2:
		{
			real gamma, eps_hat, eps_p;
			for (k = 0; k < a->msize; k++)
			{
				gamma = min(a->g.lambda_y[k] / a->g.lambda_d[k], a->g.gamma_max);
				eps_hat = a->g.alpha * a->g.prev_mask[k] * a->g.prev_mask[k] * a->g.prev_gamma[k]
					+ (1.0 - a->g.alpha) * max(gamma - 1.0, a->g.eps_floor);
				eps_p = eps_hat / (1.0 - a->g.q);
				a->g.mask[k] = getKey(a->g.GG, gamma, eps_hat) * getKey(a->g.GGS, gamma, eps_p);
				a->g.prev_gamma[k] = gamma;
				a->g.prev_mask[k] = a->g.mask[k];
			}
			break;
		}
	}
	if (a->g.ae_run) aepf(a);
}

void xemnr (EMNR a, int pos)
{
	if (a->run && pos == a->position)
	{
		int i, j, k, sbuff, sbegin;
		real g1;
		for (i = 0; i < 2 * a->bsize; i += 2)
		{
			a->inaccum[a->iainidx] = a->in[i];
			a->iainidx = (a->iainidx + 1) % a->iasize;
		}
		a->nsamps += a->bsize;
		while (a->nsamps >= a->fsize)
		{
			for (i = 0, j = a->iaoutidx; i < a->fsize; i++, j = (j + 1) % a->iasize)
				a->forfftin[i] = a->window[i] * a->inaccum[j];
			a->iaoutidx = (a->iaoutidx + a->incr) % a->iasize;
			a->nsamps -= a->incr;
			fftw_execute (a->Rfor);
			calc_gain(a);
			for (i = 0; i < a->msize; i++)
			{
				g1 = a->gain * a->mask[i];
				a->revfftin[2 * i + 0] = g1 * a->forfftout[2 * i + 0];
				a->revfftin[2 * i + 1] = g1 * a->forfftout[2 * i + 1];
			}
			fftw_execute (a->Rrev);
			for (i = 0; i < a->fsize; i++)
				a->save[a->saveidx][i] = a->window[i] * a->revfftout[i];
			for (i = a->ovrlp; i > 0; i--)
			{
				sbuff = (a->saveidx + i) % a->ovrlp;
				sbegin = a->incr * (a->ovrlp - i);
				for (j = sbegin, k = a->oainidx; j < a->incr + sbegin; j++, k = (k + 1) % a->oasize)
				{
					if ( i == a->ovrlp)
						a->outaccum[k]  = a->save[sbuff][j];
					else
						a->outaccum[k] += a->save[sbuff][j];
				}
			}
			a->saveidx = (a->saveidx + 1) % a->ovrlp;
			a->oainidx = (a->oainidx + a->incr) % a->oasize;
		}
		for (i = 0; i < a->bsize; i++)
		{
			a->out[2 * i + 0] = a->outaccum[a->oaoutidx];
			a->out[2 * i + 1] = 0.0;
			a->oaoutidx = (a->oaoutidx + 1) % a->oasize;
		}
	}
	else if (a->out != a->in)
		memcpy (a->out, a->in, a->bsize * sizeof (complex));
}

void setBuffers_emnr (EMNR a, real* in, real* out)
{
	a->in = in;
	a->out = out;
}

void setSamplerate_emnr (EMNR a, int rate)
{
	decalc_emnr (a);
	a->rate = rate;
	calc_emnr (a);
}

void setSize_emnr (EMNR a, int size)
{
	decalc_emnr (a);
	a->bsize = size;
	calc_emnr (a);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetRXAEMNRRun (int channel, int run)
{
	EMNR a = rxa[channel].emnr.p;
	if (a->run != run)
	{
		RXAbp1Check (channel, rxa[channel].amd.p->run, rxa[channel].snba.p->run, 
			run, rxa[channel].anf.p->run, rxa[channel].anr.p->run);
		EnterCriticalSection (&ch[channel].csDSP);
		a->run = run;
		RXAbp1Set (channel);
		LeaveCriticalSection (&ch[channel].csDSP);
	}
}

PORT
void SetRXAEMNRgainMethod (int channel, int method)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].emnr.p->g.gain_method = method;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEMNRnpeMethod (int channel, int method)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].emnr.p->g.npe_method = method;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEMNRaeRun (int channel, int run)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].emnr.p->g.ae_run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEMNRPosition (int channel, int position)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].emnr.p->position = position;
	rxa[channel].bp1.p->position  = position;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEMNRaeZetaThresh (int channel, real zetathresh)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].emnr.p->ae.zetaThresh = zetathresh;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void SetRXAEMNRaePsi (int channel, real psi)
{
	EnterCriticalSection (&ch[channel].csDSP);
	rxa[channel].emnr.p->ae.psi = psi;
	LeaveCriticalSection (&ch[channel].csDSP);
}
