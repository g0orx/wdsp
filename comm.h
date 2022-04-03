/*  comm.h

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

#if defined(linux) || defined(__APPLE__)
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "linux_port.h"
#ifdef ANDROID
#include <android/log.h>
#define APPNAME "WDSP"
#define LOGD(LOG_TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(LOG_TAG, ...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG,__VA_ARGS__)
#define LOGV(LOG_TAG, ...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGW(LOG_TAG, ...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(LOG_TAG, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif
#else
#include <Windows.h>
#include <process.h>
#include <intrin.h>
#include <avrt.h>
#endif
#include <math.h>
#include <time.h>
#include <float.h>
#include "fftw3.h"

#if USE_FLOAT32
typedef float real;
#define fftw_complex fftwf_complex
#define fftw_plan fftwf_plan
#define fftw_plan_dft_1d fftwf_plan_dft_1d
#define fftw_plan_dft_r2c_1d fftwf_plan_dft_r2c_1d
#define fftw_plan_dft_c2r_1d fftwf_plan_dft_c2r_1d
#define fftw_destroy_plan fftwf_destroy_plan
#define fftw_execute fftwf_execute
#define fabs fabsf
#define pow powf
#define cos cosf
#define sin sinf
#define exp expf
#define sqrt sqrtf
#define log10 log10f
#define REAL "%e"
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#define REAL_EPSILON FLT_EPSILON
#else
typedef double real;
typedef fftw_complex fftw_complex;
#define REAL "%le"
#define REAL_MAX DBL_MAX
#define REAL_MIN DBL_MIN
#define REAL_EPSILON DBL_EPSILON
#endif

#include "amd.h"
#include "ammod.h"
#include "amsq.h"
#include "analyzer.h"
#include "anf.h"
#include "anr.h"
#include "bandpass.h"
#include "calcc.h"
#include "cblock.h"
#include "cfcomp.h"
#include "cfir.h"
#include "channel.h"
#include "compress.h"
#include "delay.h"
#include "dexp.h"
#include "div.h"
#include "eer.h"
#include "emnr.h"
#include "emph.h"
#include "eq.h"
#include "fcurve.h"
#include "fir.h"
#include "firmin.h"
#include "fmd.h"
#include "fmmod.h"
#include "fmsq.h"
#include "gain.h"
#include "gen.h"
#include "icfir.h"
#include "iir.h"
#include "iobuffs.h"
#include "iqc.h"
#include "lmath.h"
#include "main.h"
#include "meter.h"
#include "meterlog10.h"
#include "nbp.h"
#include "nob.h"
#include "nobII.h"
#include "osctrl.h"
#include "patchpanel.h"
#include "resample.h"
#include "rmatch.h"
#include "RXA.h"
#include "sender.h"
#include "shift.h"
#include "siphon.h"
#include "slew.h"
#include "snb.h"
#include "syncbuffs.h"
#include "TXA.h"
#include "utilities.h"
#include "varsamp.h"
#include "wcpAGC.h"

// manage differences among consoles
#define _Thetis

// channel definitions
#define MAX_CHANNELS					32					// maximum number of supported channels
#define DSP_MULT						2					// number of dsp_buffsizes that are held in an iobuff pseudo-ring
#define INREAL							float				// data type for channel input buffer
#define OUTREAL							float				// data type for channel output buffer

// display definitions
#define dMAX_DISPLAYS					64					// maximum number of displays = max instances
#define dMAX_STITCH						4					// maximum number of sub-spans to stitch together
#define dMAX_NUM_FFT					1					// maximum number of ffts for an elimination
#define dMAX_PIXELS						16384				// maximum number of pixels that can be requested
#define dMAX_AVERAGE					60					// maximum number of pixel frames that will be window-averaged
#ifdef _Thetis
#define dINREAL							real
#else
#define dINREAL							float
#endif
#define dOUTREAL						float
#define dSAMP_BUFF_MULT					2					// ratio of input sample buffer size to fft size (for overlap)
#define dNUM_PIXEL_BUFFS				3					// number of pixel output buffers
#define dMAX_M							1					// number of variables to calibrate
#define dMAX_N							100					// maximum number of frequencies at which to calibrate
#define dMAX_CAL_SETS					2					// maximum number of calibration data sets
#define dMAX_PIXOUTS					4					// maximum number of det/avg/outputs per display instance

// wisdom definitions
#define MAX_WISDOM_SIZE_DISPLAY			262144
#define MAX_WISDOM_SIZE_FILTER			262144				// was 32769

// math definitions
#define PI								3.1415926535897932
#define TWOPI							6.2831853071795864

// miscellaneous
typedef real complex[2];
#define PORT							__declspec( dllexport )
