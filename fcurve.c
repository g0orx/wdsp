/*  fcurve.c

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

#include "comm.h"

double* fc_mults (int size, double f0, double f1, double g0, double g1, int curve, double samplerate, double scale, int ctfmode, int method)
{
	double* A  = (double *) malloc0 ((size / 2 + 1) * sizeof (double));
	int i;
	double fn, f;
	double* impulse;
	double* mults;
	int mid = size / 2;
	double g0_lin = pow(10.0, g0 / 20.0);
	for (i = 0; i <= mid; i++)
	{
		fn = (double)i / (double)mid;
		f = fn * samplerate / 2.0;
		switch (curve)
		{
		case 0:	// fm pre-emphasis
			if (f0 > 0.0)
				A[i] = scale * (g0_lin * f / f0);
			else
				A[i] = 0.0;
			break;
		case 1:	// fm de-emphasis
			if (f > 0.0)
				A[i] = scale * (g0_lin * f0 / f);
			else
				A[i] = 0.0;
			break;
		}
	}
	if (ctfmode == 0)
	{
		int k;
		int low  = (int)(2.0 * f0 / samplerate * mid);
		int high = (int)(2.0 * f1 / samplerate * mid + 0.5);
		double lowmag = A[low];
		double highmag = A[high];
		double flow4 = pow((double)low / (double)mid, 4.0);
		double fhigh4 = pow((double)high / (double)mid, 4.0);
		k = low;
		while (--k >= 0)
		{
			f = (double)k / (double)mid;
			lowmag *= (f * f * f * f) / flow4;
			if (lowmag < 1.0e-100) lowmag = 1.0e-100;
			A[k] = lowmag;
		}
		k = high;
		while (++k <= mid)
		{
			f = (double)k / (double)mid;
			highmag *= fhigh4 / (f * f * f * f);
			if (highmag < 1.0e-100) highmag = 1.0e-100;
			A[k] = highmag;
		}
	}
	if (method == 0)
		impulse = fir_fsamp(size + 1, A, 1, 1.0, -1);
	else
		impulse = fir_fsamp_odd(size + 1, A, 1, 1.0, -1);
	// print_impulse ("emph.txt", size + 1, impulse, 1, 0);
	mults = fftcv_mults(2 * size, impulse);
	_aligned_free (impulse);
	_aligned_free (A);
	return mults;
}