/*  osctrl.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2014, 2017 Warren Pratt, NR0V

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

// This file is part of the implementation of the Overshoot Controller from
// "Controlled Envelope Single Sideband" by David L. Hershberger, W9GR, in
// the November/December 2014 issue of QEX.

#include "comm.h"

void calc_osctrl (OSCTRL a)
{
	a->pn = (int)((0.3 / a->bw) * a->rate + 0.5);
	if ((a->pn & 1) == 0) a->pn += 1;
	if (a->pn < 3) a->pn = 3;
	a->dl_len = a->pn >> 1;
	a->dl    = (real *) malloc0 (a->pn * sizeof (complex));
	a->dlenv = (real *) malloc0 (a->pn * sizeof (real));
	a->in_idx = 0;
	a->out_idx = a->in_idx + a->dl_len;
	a->max_env = 0.0;
}

void decalc_osctrl (OSCTRL a)
{
	_aligned_free (a->dlenv);
	_aligned_free (a->dl);
}

OSCTRL create_osctrl (
				int run,
				int size,
				real* inbuff,
				real* outbuff,
				int rate,
				real osgain )
{
	OSCTRL a = (OSCTRL) malloc0 (sizeof (osctrl));
	a->run = run;
	a->size = size;
	a->inbuff = inbuff;
	a->outbuff = outbuff;
	a->rate = rate;
	a->osgain = osgain;
	a->bw = 3000.0;
	calc_osctrl (a);
	return a;
}

void destroy_osctrl (OSCTRL a)
{
	decalc_osctrl (a);
	_aligned_free (a);
}

void flush_osctrl (OSCTRL a)
{
	memset (a->dl,    0, a->dl_len * sizeof (complex));
	memset (a->dlenv, 0, a->pn     * sizeof (real));
}

void xosctrl (OSCTRL a)
{
	if (a->run)
	{
		int i, j;
		real divisor;
		for (i = 0; i < a->size; i++)
		{
			a->dl[2 * a->in_idx + 0] = a->inbuff[2 * i + 0];							// put sample in delay line
			a->dl[2 * a->in_idx + 1] = a->inbuff[2 * i + 1];
			a->env_out = a->dlenv[a->in_idx];											// take env out of delay line
			a->dlenv[a->in_idx] = sqrt (a->inbuff[2 * i + 0] * a->inbuff[2 * i + 0]		// put env in delay line 
			                          + a->inbuff[2 * i + 1] * a->inbuff[2 * i + 1]);
			if (a->dlenv[a->in_idx]  >  a->max_env) a->max_env = a->dlenv[a->in_idx];
			if (a->env_out >= a->max_env && a->env_out > 0.0)							// run the buffer
			{
				a->max_env = 0.0;
				for (j = 0; j < a->pn; j++)
					if (a->dlenv[j] > a->max_env) a->max_env = a->dlenv[j];
			}
			if (a->max_env > 1.0) divisor = 1.0 + a->osgain * (a->max_env - 1.0);
			else                  divisor = 1.0;
			a->outbuff[2 * i + 0] = a->dl[2 * a->out_idx + 0] / divisor;				// output sample
			a->outbuff[2 * i + 1] = a->dl[2 * a->out_idx + 1] / divisor;
			if (--a->in_idx  < 0) a->in_idx  += a->pn;
			if (--a->out_idx < 0) a->out_idx += a->pn;
		}
	}
	else if (a->inbuff != a->outbuff)
		memcpy (a->outbuff, a->inbuff, a->size * sizeof (complex));
}

void setBuffers_osctrl (OSCTRL a, real* in, real* out)
{
	a->inbuff = in;
	a->outbuff = out;
}

void setSamplerate_osctrl (OSCTRL a, int rate)
{
	decalc_osctrl (a);
	a->rate = rate;
	calc_osctrl (a);
}

void setSize_osctrl (OSCTRL a, int size)
{
	a->size = size;
	flush_osctrl (a);
}

/********************************************************************************************************
*																										*
*											TXA Properties												*
*																										*
********************************************************************************************************/

PORT
void SetTXAosctrlRun (int channel, int run)
{
	if (txa[channel].osctrl.p->run != run)
	{
		EnterCriticalSection (&ch[channel].csDSP);
		txa[channel].osctrl.p->run = run;
		TXASetupBPFilters (channel);
		LeaveCriticalSection (&ch[channel].csDSP);
	}
}