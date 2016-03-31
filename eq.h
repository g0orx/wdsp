/*  eq.h

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

#ifndef _eq_h
#define _eq_h

typedef struct _eq
{
	int run;
	int size;
	double* in;
	double* out;
	int nfreqs;
	double* F;
	double* G;
	double* infilt;
	double* product;
	double* mults;
	double scale;
	int ctfmode;
	int method;
	double samplerate;
	fftw_plan CFor;
	fftw_plan CRev;
}eq, *EQ;

extern double* eq_mults (int size, int nfreqs, double* F, double* G, double samplerate, double scale, int ctfmode, int method);

extern EQ create_eq (int run, int size, double *in, double *out, int nfreqs, double* F, double* G, int ctfmode, int method, int samplerate);

extern void destroy_eq (EQ a);

extern void flush_eq (EQ a);

extern void xeq (EQ a);

extern void setBuffers_eq (EQ a, double* in, double* out);

extern void setSamplerate_eq (EQ a, int rate);

extern void setSize_eq (EQ a, int size);

// RXA Properties

extern __declspec (dllexport) void SetRXAEQRun (int channel, int run);

extern __declspec (dllexport) void SetRXAEQProfile (int channel, int nfreqs, double* F, double* G);

extern __declspec (dllexport) void SetRXAEQCtfmode (int channel, int mode);

extern __declspec (dllexport) void SetRXAEQMethod (int channel, int method);

extern __declspec (dllexport) void SetRXAGrphEQ (int channel, int *rxeq);

extern __declspec (dllexport) void SetRXAGrphEQ10 (int channel, int *rxeq);

// TXA Properties

extern __declspec (dllexport) void SetTXAEQRun (int channel, int run);

extern __declspec (dllexport) void SetTXAEQProfile (int channel, int nfreqs, double* F, double* G);

extern __declspec (dllexport) void SetTXAEQCtfmode (int channel, int mode);

extern __declspec (dllexport) void SetTXAEQMethod (int channel, int method);

extern __declspec (dllexport) void SetTXAGrphEQ (int channel, int *txeq);

extern __declspec (dllexport) void SetTXAGrphEQ10 (int channel, int *txeq);

#endif