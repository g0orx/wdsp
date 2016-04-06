/*  nbp.c

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

#include "comm.h"

/********************************************************************************************************
*																										*
*											Notch Database												*
*																										*
********************************************************************************************************/

NOTCHDB create_notchdb (int master_run, int maxnotches)
{
	NOTCHDB a = (NOTCHDB) malloc0 (sizeof (notchdb));
	a->master_run = master_run;
	a->maxnotches = maxnotches;
	a->nn = 0;
	a->fcenter = (double *) malloc0 (a->maxnotches * sizeof (double));
	a->fwidth  = (double *) malloc0 (a->maxnotches * sizeof (double));
	a->nlow    = (double *) malloc0 (a->maxnotches * sizeof (double));
	a->nhigh   = (double *) malloc0 (a->maxnotches * sizeof (double));
	a->active  = (int    *) malloc0 (a->maxnotches * sizeof (int   ));
	return a;
}

void destroy_notchdb (NOTCHDB b)
{
	_aligned_free (b->active);
	_aligned_free (b->nhigh);
	_aligned_free (b->nlow);
	_aligned_free (b->fwidth);
	_aligned_free (b->fcenter);
}

/********************************************************************************************************
*																										*
*										Notched Bandpass Filter											*
*																										*
********************************************************************************************************/

double* fir_mbandpass (int N, int nbp, double* flow, double* fhigh, double rate, double scale, int wintype)
{
	int i, k;
	double* impulse = (double *) malloc0 (N * sizeof (complex));
	double* imp;
	for (k = 0; k < nbp; k++)
	{
		imp = fir_bandpass (N, flow[k], fhigh[k], rate, wintype, 1, scale);
		for (i = 0; i < N; i++)
		{
			impulse[2 * i + 0] += imp[2 * i + 0];
			impulse[2 * i + 1] += imp[2 * i + 1];
		}
		_aligned_free (imp);
	}
	return impulse;
}

double min_notch_width (NBP a)
{
	double min_width;
	switch (a->wintype)
	{
	case 0:
		min_width = 1600.0 / (a->size / 256) * (a->rate / 48000);
		break;
	case 1:
		min_width = 2200.0 / (a->size / 256) * (a->rate / 48000);
		break;
	}
	return min_width;
}

int make_nbp (int nn, int* active, double* center, double* width, double* nlow, double* nhigh, 
	double minwidth, int autoincr, double flow, double fhigh, double* bplow, double* bphigh, int* havnotch)
{
	int nbp;
	int nnbp, adds;
	int i, j, k;
	double nl, nh;
	int* del = (int *) malloc0 (1024 * sizeof (int));
	if (fhigh > flow)
	{
		bplow[0]  = flow;
		bphigh[0] = fhigh;
		nbp = 1;
	}
	else
	{
		nbp = 0;
		return nbp;
	}
	*havnotch = 0;
	for (k = 0; k < nn; k++)
	{
		if (autoincr && width[k] < minwidth)
		{
			nl = center[k] - 0.5 * minwidth;
			nh = center[k] + 0.5 * minwidth;
		}
		else
		{
			nl = nlow[k];
			nh = nhigh[k];
		}
		if (active[k] && (nh > flow && nl < fhigh))
		{
			*havnotch = 1;
			adds = 0;
			for (i = 0; i < nbp; i++)
			{
				if (nh > bplow[i] && nl < bphigh[i])
				{
					if (nl <= bplow[i] && nh >= bphigh[i])
					{
						del[i] = 1;
					}
					else if (nl > bplow[i] && nh < bphigh[i])
					{
						
						bplow[nbp + adds] = nh;
						bphigh[nbp + adds] = bphigh[i];
						bphigh[i] = nl;
						adds++;
					}
					else if (nl <= bplow[i] && nh > bplow[i])	
					{
						bplow[i] = nh;
					}
					else if (nl < bphigh[i] && nh >= bphigh[i])
					{
						bphigh[i] = nl;
					}
				}
			}
			nbp += adds;
			nnbp = nbp;
			for (i = 0; i < nbp; i++)
			{
				if (del[i] == 1)
				{
					nnbp--;
					for (j = i; j < nnbp; j++)
					{
						bplow[j] = bplow[j + 1];
						bphigh[j] = bphigh[j + 1];
					}
					del[i] = 0;
				}
			}
			nbp = nnbp;
		}
	}
	_aligned_free (del);
	return nbp;
}

void calc_nbp_lightweight (NBP a)
{
	int i;
	double* impulse;
	double fl, fh;
	double offset;
	NOTCHDB b = *a->ptraddr;
	if (a->fnfrun)
	{
		offset = b->tunefreq + b->shift;
		fl = a->flow  + offset;
		fh = a->fhigh + offset;
		a->numpb = make_nbp (b->nn, b->active, b->fcenter, b->fwidth, b->nlow, b->nhigh, 
			min_notch_width (a), a->autoincr, fl, fh, a->bplow, a->bphigh, &a->havnotch);
		// when tuning, no need to recalc filter if there were not and are not any notches in passband
		if (a->hadnotch || a->havnotch)
		{
			for (i = 0; i < a->numpb; i++)
			{
				a->bplow[i]  -=	offset;
				a->bphigh[i] -= offset;
			}
			impulse = fir_mbandpass (a->size + 1, a->numpb, a->bplow, a->bphigh,
				a->rate, 1.0 / (double)(2 * a->size), a->wintype);
			_aligned_free (a->mults);
			a->mults = fftcv_mults(2 * a->size, impulse);
			// print_impulse ("nbp.txt", a->size + 1, impulse, 1, 0);
			_aligned_free(impulse);
		}
		a->hadnotch = a->havnotch;
	}
	else
		a->hadnotch = 1;
}

void calc_nbp_impulse (NBP a)
{
	int i;
	double fl, fh;
	double offset;
	NOTCHDB b = *a->ptraddr;
	if (a->fnfrun)
	{
		offset = b->tunefreq + b->shift;
		fl = a->flow  + offset;
		fh = a->fhigh + offset;
		a->numpb = make_nbp (b->nn, b->active, b->fcenter, b->fwidth, b->nlow, b->nhigh, 
			min_notch_width (a), a->autoincr, fl, fh, a->bplow, a->bphigh, &a->havnotch);
		for (i = 0; i < a->numpb; i++)
		{
			a->bplow[i]  -=	offset;
			a->bphigh[i] -= offset;
		}
		a->impulse = fir_mbandpass (a->size + 1, a->numpb, a->bplow, a->bphigh,
			a->rate, 1.0 / (double)(2 * a->size), a->wintype);
	}
	else
	{
		a->impulse = fir_bandpass(a->size + 1, a->flow, a->fhigh, a->rate, a->wintype, 1, 1.0 / (double)(2 * a->size));
	}
}

void calc_nbp (NBP a)
{
	calc_nbp_impulse (a);
	a->infilt = (double *)malloc0(2 * a->size * sizeof(complex));
	a->product = (double *)malloc0(2 * a->size * sizeof(complex));
	a->mults = fftcv_mults(2 * a->size, a->impulse);
	a->CFor = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->infilt, (fftw_complex *)a->product, FFTW_FORWARD, FFTW_PATIENT);
	a->CRev = fftw_plan_dft_1d(2 * a->size, (fftw_complex *)a->product, (fftw_complex *)a->out, FFTW_BACKWARD, FFTW_PATIENT);
	// print_impulse ("nbp.txt", a->size + 1, impulse, 1, 0);
	_aligned_free(a->impulse);
}

void decalc_nbp (NBP a)
{
	fftw_destroy_plan(a->CRev);
	fftw_destroy_plan(a->CFor);
	_aligned_free(a->mults);
	_aligned_free(a->product);
	_aligned_free(a->infilt);
}

NBP create_nbp(int run, int fnfrun, int position, int size, double* in, double* out, 
	double flow, double fhigh, int rate, int wintype, double gain, int autoincr, int maxpb, NOTCHDB* ptraddr)
{
	NBP a = (NBP) malloc0 (sizeof (nbp));
	a->run = run;
	a->fnfrun = fnfrun;
	a->position = position;
	a->size = size;
	a->rate = (double)rate;
	a->wintype = wintype;
	a->gain = gain;
	a->in = in;
	a->out = out;
	a->autoincr = autoincr;
	a->flow = flow;
	a->fhigh = fhigh;
	a->maxpb = maxpb;
	a->ptraddr = ptraddr;
	a->bplow   = (double *) malloc0 (a->maxpb * sizeof (double));
	a->bphigh  = (double *) malloc0 (a->maxpb * sizeof (double));
	calc_nbp (a);
	return a;
}

void destroy_nbp (NBP a)
{
	decalc_nbp (a);
	_aligned_free (a->bphigh);
	_aligned_free (a->bplow);
	_aligned_free (a);
}

void flush_nbp (NBP a)
{
	memset (a->infilt, 0, 2 * a->size * sizeof (complex));
}

void xnbp (NBP a, int pos)
{
	int i;
	double I, Q;
	if (a->run && pos == a->position)
	{
		memcpy (&(a->infilt[2 * a->size]), a->in, a->size * sizeof (complex));
		fftw_execute (a->CFor);
		for (i = 0; i < 2 * a->size; i++)
		{
			I = a->gain * a->product[2 * i + 0];
			Q = a->gain * a->product[2 * i + 1];
			a->product[2 * i + 0] = I * a->mults[2 * i + 0] - Q * a->mults[2 * i + 1];
			a->product[2 * i + 1] = I * a->mults[2 * i + 1] + Q * a->mults[2 * i + 0];
		}
		fftw_execute (a->CRev);
		memcpy (a->infilt, &(a->infilt[2 * a->size]), a->size * sizeof(complex));
	}
	else if (a->in != a->out)
		memcpy (a->out, a->in, a->size * sizeof (complex));
}

void setBuffers_nbp (NBP a, double* in, double* out)
{
	decalc_nbp (a);
	a->in = in;
	a->out = out;
	calc_nbp (a);
}

void setSamplerate_nbp (NBP a, int rate)
{
	decalc_nbp (a);
	a->rate = rate;
	calc_nbp (a);
}

void setSize_nbp (NBP a, int size)
{
	decalc_nbp (a);
	a->size = size;
	calc_nbp (a);
}

void recalc_nbp_filter (NBP a)
{
	_aligned_free (a->mults);
	calc_nbp_impulse (a);
	a->mults = fftcv_mults(2 * a->size, a->impulse);
	_aligned_free (a->impulse);
}

/********************************************************************************************************
*																										*
*											RXA Properties												*
*																										*
********************************************************************************************************/

// DATABASE PROPERTIES

void UpdateNBPFiltersLightWeight (int channel)
{
	calc_nbp_lightweight (rxa[channel].nbp0.p);
	calc_nbp_lightweight (rxa[channel].bpsnba.p->bpsnba);
}

void UpdateNBPFilters(int channel)
{
	NBP a = rxa[channel].nbp0.p;
	BPSNBA b = rxa[channel].bpsnba.p;
	if (a->fnfrun)
	{
		recalc_nbp_filter (a);
	}
	if (b->bpsnba->fnfrun)
	{
		recalc_bpsnba_filter (b);
	}
}

PORT
int RXANBPAddNotch (int channel, int notch, double fcenter, double fwidth, int active)
{
	NOTCHDB b;
	int i, j;
	int rval;
	EnterCriticalSection (&ch[channel].csDSP);
	b = rxa[channel].ndb.p;
	if (notch <= b->nn && b->nn < b->maxnotches)
	{
		b->nn++;
		for (i = b->nn - 2, j = b->nn - 1; i >= notch; i--, j--)
		{
			b->fcenter[j] = b->fcenter[i];
			b->fwidth[j] = b->fwidth[i];
			b->nlow[j] = b->nlow[i];
			b->nhigh[j] = b->nhigh[i];
			b->active[j] = b->active[i];
		}
		b->fcenter[notch] = fcenter;
		b->fwidth[notch] = fwidth;
		b->nlow[notch] = fcenter - 0.5 * fwidth;
		b->nhigh[notch] = fcenter + 0.5 * fwidth;
		b->active[notch] = active;
		UpdateNBPFilters (channel);
		rval = 0;
	}
	else
		rval = -1;
	LeaveCriticalSection (&ch[channel].csDSP);
	return rval;
}

PORT
int RXANBPGetNotch (int channel, int notch, double* fcenter, double* fwidth, int* active)
{
	NOTCHDB a;
	int rval;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	if (notch < a->nn)
	{
		*fcenter = a->fcenter[notch];
		*fwidth = a->fwidth[notch];
		*active = a->active[notch];
		rval = 0;
	}
	else
	{
		*fcenter = -1.0;
		*fwidth = 0.0;
		*active = -1;
		rval = -1;
	}
	LeaveCriticalSection (&ch[channel].csDSP);
	return rval;
}

PORT
int RXANBPDeleteNotch (int channel, int notch)
{
	int i, j;
	int rval;
	NOTCHDB a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	if (notch < a->nn)
	{
		a->nn--;
		for (i = notch, j = notch + 1; i < a->nn; i++, j++)
		{
			a->fcenter[i] = a->fcenter[j];
			a->fwidth[i] = a->fwidth[j];
			a->nlow[i] = a->nlow[j];
			a->nhigh[i] = a->nhigh[j];
			a->active[i] = a->active[j];
		}
		UpdateNBPFilters (channel);
		rval = 0;
	}
	else
		rval = -1;
	LeaveCriticalSection (&ch[channel].csDSP);
	return rval;
}

PORT
int RXANBPEditNotch (int channel, int notch, double fcenter, double fwidth, int active)
{
	NOTCHDB a;
	int rval;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	if (notch < a->nn)
	{
		a->fcenter[notch] = fcenter;
		a->fwidth[notch] = fwidth;
		a->nlow[notch] = fcenter - 0.5 * fwidth;
		a->nhigh[notch] = fcenter + 0.5 * fwidth;
		a->active[notch] = active;
		UpdateNBPFilters (channel);
		rval = 0;
	}
	else
		rval = -1;
	LeaveCriticalSection (&ch[channel].csDSP);
	return rval;
}

PORT
void RXANBPGetNumNotches (int channel, int* nnotches)
{
	NOTCHDB a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	*nnotches = a->nn;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPSetTuneFrequency (int channel, double tunefreq)
{
	NOTCHDB a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	if (tunefreq != a->tunefreq)
	{
		a->tunefreq = tunefreq;
		UpdateNBPFiltersLightWeight (channel);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPSetShiftFrequency (int channel, double shift)
{
	NOTCHDB a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	if (shift != a->shift)
	{
		a->shift = shift;
		UpdateNBPFiltersLightWeight (channel);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPSetNotchesRun (int channel, int run)
{
	NOTCHDB a; 
	NBP b;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].ndb.p;
	b = rxa[channel].nbp0.p;
	if ( run != a->master_run)
	{
		a->master_run = run;
		b->fnfrun = a->master_run;		// update nbp0 'run'
		recalc_nbp_filter (b);			// recalc nbp0 filter
		RXAbpsnbaCheck (channel);		// update bpsnba 'run' & recalc bpsnba filter
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

// FILTER PROPERTIES

PORT
void RXANBPSetRun (int channel, int run)
{
	NBP a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].nbp0.p;
	a->run = run;
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPSetFreqs (int channel, double flow, double fhigh)
{
	NBP a;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].nbp0.p;
	if ((flow != a->flow) || (fhigh != a->fhigh))
	{
		a->flow = flow;
		a->fhigh = fhigh;
		recalc_nbp_filter (a);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPSetWindow (int channel, int wintype)
{
	NBP a;
	BPSNBA b;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].nbp0.p;
	b = rxa[channel].bpsnba.p;
	if ((a->wintype != wintype))
	{
		a->wintype = wintype;
		recalc_nbp_filter (a);
	}
	if ((b->wintype != wintype))
	{
		b->wintype = wintype;
		recalc_bpsnba_filter (b);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPGetMinNotchWidth (int channel, double* minwidth)
{
	NBP a0;
	EnterCriticalSection (&ch[channel].csDSP);
	a0 = rxa[channel].nbp0.p;
	*minwidth = min_notch_width (a0);
	LeaveCriticalSection (&ch[channel].csDSP);
}

PORT
void RXANBPSetAutoIncrease (int channel, int autoincr)
{
	NBP a;
	BPSNBA b;
	EnterCriticalSection (&ch[channel].csDSP);
	a = rxa[channel].nbp0.p;
	b = rxa[channel].bpsnba.p;
	if ((a->autoincr != autoincr))
	{
		a->autoincr = autoincr;
		recalc_nbp_filter (a);
	}
	if ((b->autoincr != autoincr))
	{
		b->autoincr = autoincr;
		recalc_bpsnba_filter (b);
	}
	LeaveCriticalSection (&ch[channel].csDSP);
}
