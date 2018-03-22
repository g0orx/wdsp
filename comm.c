/*  comm.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2017  Warren Pratt, NR0V, Jae Stutzman, K5JAE

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


*/

#include "comm.h"

#ifdef _WINDOWS_
uintptr_t __cdecl wdsp_beginthread(void(__cdecl *start_address)(void *), unsigned stack_size, void *arglist)
{
	return _beginthread(start_address, stack_size, arglist);
}
#endif
