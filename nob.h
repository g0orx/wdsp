/*  nob.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2013, 2014 Warren Pratt, NR0V

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

#ifndef _anb_h
#define _anb_h

typedef struct _anb
{
	int run;
	int buffsize;					// size of input/output buffer
	real* in;						// input buffer
	real* out;					// output buffer
	int dline_size;					// length of delay line which is 'real dline[length][2]'
	real *dline;					// pointer to delay line
	real samplerate;				// samplerate, used to convert times into sample counts
	real tau;						// transition time, signal<->zero
	real hangtime;				// time to stay at zero after noise is no longer detected
	real advtime;					// deadtime (zero output) in advance of detected noise
	real backtau;					// time constant used in averaging the magnitude of the input signal
	real threshold;				// triggers if (noise > threshold * average_signal_magnitude)
    real *wave;                   // pointer to array holding transition waveform
    int state;                      // state of the state machine
    real avg;                     // average value of the signal magnitude
    int dtime;                      // count when decreasing the signal magnitude
    int htime;                      // count when hanging
    int itime;                      // count when increasing the signal magnitude
    int atime;                      // count at zero before the noise burst (advance count)
    real coef;					// parameter in calculating transition waveform
    int trans_count;                // number of samples to equal 'tau' time
    int hang_count;                 // number of samples to equal 'hangtime' time
    int adv_count;                  // number of samples to equal 'advtime' time
    int in_idx;                     // ring buffer position into which new samples are inserted
    int out_idx;                    // ring buffer position from which delayed samples are pulled
    real power;					// level at which signal was increasing when a new decrease is started
    int count;						// set each time a noise sample is detected, counts down
    real backmult;				// multiplier for waveform averaging
    real ombackmult;				// multiplier for waveform averaging
	CRITICAL_SECTION cs_update;
	real *legacy;																										////////////  legacy interface - remove
} anb, *ANB;

__declspec (dllexport) ANB create_anb	(
	int run,
	int buffsize,
	real* in,
	real* out,
	real samplerate,
	real tau,
	real hangtime,
	real advtime,
	real backtau,
	real threshold
						);

__declspec (dllexport) void destroy_anb (ANB a);

__declspec (dllexport) void flush_anb (ANB a);

__declspec (dllexport) void xanb (ANB a);

extern __declspec (dllexport) void create_anbEXT	(
	int id,
	int run,
	int buffsize,
	real samplerate,
	real tau,
	real hangtime,
	real advtime,
	real backtau,
	real threshold
					);

extern __declspec (dllexport) void destroy_anbEXT (int id);

extern __declspec (dllexport) void flush_anbEXT (int id);

extern __declspec (dllexport) void xanbEXT (int id, real* in, real* out);

extern void setBuffers_anb (ANB a, real* in, real* out);

extern void setSamplerate_anb (ANB a, int rate);

extern void setSize_anb (ANB a, int size);


extern __declspec (dllexport) void pSetRCVRANBRun (ANB a, int run);

extern __declspec (dllexport) void pSetRCVRANBBuffsize (ANB a, int size);

extern __declspec (dllexport) void pSetRCVRANBSamplerate (ANB a, int rate);

extern __declspec (dllexport) void pSetRCVRANBTau (ANB a, real tau);

extern __declspec (dllexport) void pSetRCVRANBHangtime (ANB a, real time);

extern __declspec (dllexport) void pSetRCVRANBAdvtime (ANB a, real time);

extern __declspec (dllexport) void pSetRCVRANBBacktau (ANB a, real tau);

extern __declspec (dllexport) void pSetRCVRANBThreshold (ANB a, real thresh);

#endif