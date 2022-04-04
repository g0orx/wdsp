/*  fir.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2013, 2016 Warren Pratt, NR0V

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

extern real* fftcv_mults (int NM, real* c_impulse);

extern real* fir_fsamp_odd (int N, real* A, int rtype, real scale, int wintype);

extern real* fir_fsamp (int N, real* A, int rtype, real scale, int wintype);

extern real* fir_bandpass (int N, real f_low, real f_high, real samplerate, int wintype, int rtype, real scale);

extern real* get_fsamp_window(int N, int wintype);

extern real *fir_read (int N, const char *filename, int rtype, real scale);

extern void mp_imp (int N, real* fir, real* mpfir, int pfactor, int polarity);