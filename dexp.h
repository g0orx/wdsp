/*  dexp.h

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2018, 2019 Warren Pratt, NR0V

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

#ifndef _dexp_h
#define _dexp_h

typedef struct _delring
{
	int rsize;							// ringsize (measured in complex samples)
	real* ring;						// ring buffer
	int inptr;							// ring input pointer (counts in complex samples)
	int outptr;							// ring output pointer (counts in complex samples)
	int rdelay;							// ring delay (measured in complex samples)
	int size;							// input/output size in complex samples
	real* in;							// source buffer
	real* out;						// destination buffer
} delring, *DELRING;

typedef struct _dexp
{
	int id;								// 'id' for this dexp
	int run_dexp;						// 0 if dexp is OFF; 1 if it's ON
	int size;							// size of input/output buffers
	real* in;							// audio input buffer
	real* out;						// audio output buffer; can be same as 'in'
	real rate;						// sample rate
	real dettau;						// detection averaging time constant
	real avm;							// averaging multiplier
	real onem_avm;					// one minus averaging multiplier
	real avsig;						// averaged detection signal
	int state;							// state machine control
	int count;							// count variable used within a state
	real tattack;						// attack time
	real tdecay;						// decay time
	int nattack;						// one less than total number of attack multipliers
	int ndecay;							// one less than total number of decay multipliers
	real* cattack;					// attack curve multipliers
	real* cdecay;						// decay curve multipliers
	real attack_thresh;				// attack threshold
	real hold_thresh;					// hold & decay threshold
	real thold;						// hold time
	int nhold;							// hold count
	real exp_ratio;					// expander ratio (high-gain to low-gain)
	real hysteresis_ratio;			// ratio hold_thresh/attack_thresh.  0.0 < ratio < 1.0
	real low_gain;					// gain when gate is closed
	real* trigsig;					// buffer for trigger signal (signal after side-channel filter)
	real* delsig;						// buffer for signal delayed to match trigger signal
	real peak;						// peak signal value to return to console
	// side-channel bandpass filter & and buffer for compensating delay
	int run_filt;						// 1 = side-channel filter and compensating delay are ON, 0 = OFF
	int nc;								// number of coefficients
	int wintype;						// window type
	real low_cut;						// low cutoff frequency
	real high_cut;					// high cutoff frequency
	FIRCORE p;							// filter structure
	DELRING scdring;					// delay ring for side channel
	// output audio delay to cover RF_Delay + Xmtr_delay_and_upslew
	real* audbuffer;					// buffer to serve as input to audring
	int run_audelay;					// 'run' variable for audio delay ring
	real audelay;						// audio output delay in seconds
	DELRING audring;					// audio delay ring
	// vox
	int run_vox;
	void (__stdcall *pushvox)(int channel, int active);
	int vox_count;
	// update critical section
	CRITICAL_SECTION cs_update;
	// anti-vox
	int antivox_run;					// 'run' for anti-vox
	int antivox_new;					// internal variable indicating new anti-vox data is available
	int antivox_size;					// size of anti-vox data buffer
	real antivox_rate;				// sample-rate of anti-vox data
	real antivox_tau;					// time-constant of anti-vox smoothing
	real antivox_gain;				// anti-vox gain factor
	real antivox_mult;				// multiplier for anti-vox smoothing
	real antivox_onemmult;			// one minus antivox_mult
	real antivox_level;				// current anti-vox smoothed signal level
	real* antivox_data;				// buffer to hold new anti-vox data
} dexp, *DEXP;

extern DEXP pdexp[];

__declspec (dllexport) void create_dexp (int id, int run_dexp, int size, real* in, real* out, int rate, real dettau, real tattack, real tdecay, 
	real thold, real exp_ratio, real hyst_ratio, real attack_thresh, int nc, int wtype, real lowcut, real highcut, 
	int run_filt, int run_vox, int run_audelay, real audelay, void (__stdcall *pushvox)(int id, int active),
	int antivox_run, int antivox_size, int antivox_rate, real antivox_gain, real antivox_tau);

__declspec (dllexport) void destroy_dexp (int id);

__declspec (dllexport) void flush_dexp (int id);

__declspec (dllexport) void xdexp (int id);

__declspec (dllexport) void SetDEXPSize (int id, int size);

__declspec (dllexport) void SetDEXPRate (int id, real rate);

__declspec (dllexport) void SendAntiVOXData (int id, int nsamples, real* data);

#endif
