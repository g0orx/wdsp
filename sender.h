/*  send.h

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

// 'send' copies samples from the sample stream and proactively pushes those samples to external
//	functions by calling them.  As such, the call and parameters are somewhat specific to the
//	need for the data.  Nevertheless, this code is written in somewhat of a generic form to 
//	facilitate adding additional functions in the future.

#ifndef _sender_h
#define _sender_h

typedef struct _sender
{
	int run;			// 0 = send OFF, 1 = send ON
	int flag;			// secondary 'run'; AND'd with 'run'
	int mode;			// selects the specific processing and function call
	int size;			// size of the data buffer (complex samples)
	real* in;			// buffer from which to take the data
	int arg0;			// parameters that can be passed to the function called
	int arg1;
	int arg2;
	int arg3;
	real* out;		// internally created buffer into which processed data is placed
						// a pointer to *out is passed to the external function that is called
} sender, *SENDER;

extern SENDER create_sender (int run, int flag, int mode, int size, real* in, int arg0, int arg1, int arg2, int arg3);

extern void destroy_sender (SENDER a);

extern void flush_sender (SENDER a);

extern void xsender (SENDER a);

extern void setBuffers_sender (SENDER a, real* in);

extern void setSamplerate_sender (SENDER a, int rate);

extern void setSize_sender (SENDER a, int size);

// RXA Properties

extern __declspec (dllexport) void SetRXASpectrum (int channel, int flag, int disp, int ss, int LO);

// TXA Properties

#endif