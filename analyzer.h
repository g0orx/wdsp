/*  analyzer.h

This file is part of a program that implements a Spectrum Analyzer
used in conjunction with software-defined-radio hardware.

Copyright (C) 2012, 2013, 2014 Warren Pratt, NR0V

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
#ifndef _analyzer_h
#define _analyzer_h
#include "comm.h"

typedef struct _dp
{
	int max_size;										//maximum fft size to be used
	int max_num_fft;									//maximum number of LO positions per sub-span to be used
	int max_stitch;										//maximum number of sub-spans to be concatenated
														//NOTE:  max_size, max_num_fft, and max_stitch MUST BE <= THE
															//	CORRESPONDING VALUES IN <analyzer.h>!!
	int num_fft;										//current number of ffts in use						
	int size;											//current size of fft input sample vector
	int out_size;										//current size of fft output vector
	int window_type;									//type of the window function to be applied
	int overlap;										//number of samples re-used per fft, range 0 to size-1
	int flip[dMAX_NUM_FFT];								//0 for low-side LO => do NOT flip; 1 for high-side LO => FLIP
	int clip;											//number of bins to clip off on EACH end of the sub-span fft
														//	ASSUMES size/2 IS AN EVEN NUMBER!!!
	int fsclipL;										//number of bins to clip off the lower end of the TOTAL SPAN
	int fsclipH;										//number of bins to clip off the upper end of the TOTAL SPAN
	int fscL;											//fsclipL modulo (out_size - 2 * clip)
	int fscH;											//fsclipH modulo (out_size - 2 * clip)
	int begin_ss;										//number of first sub-span that is NOT completely clipped off
	int end_ss;											//number of last sub-span that is NOT completely clipped off
	int ss_bins[dMAX_STITCH];							//number of bins delivered by eliminate()/Celiminate in each sub-span
	volatile LONG input_busy[dMAX_STITCH][dMAX_NUM_FFT];

	int num_pixels;										//number of pixels requested
	int num_stitch;										//number of results to be stitched together to generate the pixel frame
	unsigned long long stitch_flag;
	int spec_flag[dMAX_STITCH];							//flags showing if all ffts for a sub-span are done so elimination can proceed
	double pix_per_bin;									//number of pixels per fft bin, note that this is fractional, not integral
	double bin_per_pix;									//number of fft bins per pixel, this is fractional and != 1.0/pix_per_bin
	double scale;										//output amplitude scale factor
	double PiAlpha;										//parameter for Kaiser window function

	int cal_set;										//specifies which set of calibration data to use
	double f_min;										//frequency at first pixel (for calibration)
	double f_max;										//frequency at last pixel (for calibration)
	int cal_changed;									//flag to indicate that the calibration data has changed

	double *window;										//pointer to buffer to hold window coefficients	
	double *result[dMAX_STITCH];						//pointers to buffer to hold elimination results for each sub-span
	dOUTREAL *pixels[dNUM_PIXEL_BUFFS];					//pointers pixel output buffers
	dOUTREAL *napixels[dNUM_PIXEL_BUFFS];				//pointers to pixel output buffers for non-averaged data
	double *t_pixels;									//pointer to temporary pixel buffer
	double *na_tpixels;									//pointer to temporary pixel buffer for non-averaged data
	int w_pix_buff;										//number of pixel buffer owned by writing process
	int na_wpixbuff;
	int r_pix_buff;										//number of pixel buffer owned by reading process
	int na_rpixbuff;
	int last_pix_buff;									//number of the last pixel buffer written
	int na_lastpixbuff;
	volatile LONG pb_ready[dNUM_PIXEL_BUFFS];			//if value is 0, this data has already been read; 1 = fresh data to read
	volatile LONG na_pbready[dNUM_PIXEL_BUFFS];
	int num_average;									//number of spans to average to create the pixels
	int avail_frames;									//number of pixel frames currently available to average
	int av_in_idx;										//input index in averaging pixel buffer ring
	int av_out_idx;										//output index in averaging pixel buffer ring
	double *av_sum;										//pointer to sum buffer for averaging
	double *av_buff[dMAX_AVERAGE];						//pointers to ring of buffers to hold pixel frames for averaging
	double *pre_av_sum;
	double *pre_av_out;
	double *na_out;
	int av_mode;
	double av_backmult;									//back multiplier for weighted averaging
	double *cd;											//pointer to amplitude calibration buffer
	int n_freqs[dMAX_CAL_SETS];							//number of frequencies in each calibration set
	double *freqs[dMAX_CAL_SETS];						//pointers to vectors of calibration frequencies
	double (*ac3[dMAX_CAL_SETS][dMAX_M]);					//pointers to amplitude interpolant coefficients
	double (*ac2[dMAX_CAL_SETS][dMAX_M]);
	double (*ac1[dMAX_CAL_SETS][dMAX_M]);
	double (*ac0[dMAX_CAL_SETS][dMAX_M]);

	fftw_plan plan[dMAX_STITCH][dMAX_NUM_FFT];			//fftw plans
	fftw_plan Cplan[dMAX_STITCH][dMAX_NUM_FFT];
	double *fft_in[dMAX_STITCH][dMAX_NUM_FFT];			//pointers to fftw real input vectors
	fftw_complex *Cfft_in[dMAX_STITCH][dMAX_NUM_FFT];	//pointers to fftw complex input vectors
	fftw_complex *fft_out[dMAX_STITCH][dMAX_NUM_FFT];	//pointers to fftw complex output vectors
	volatile LONG *pnum_threads;						//pointer to current number of active worker threads
	int stop;											//when set, fft threads will be returned to the pool
	int end_dispatcher;									//set this flag to one to destroy the dispatcher thread
	int dispatcher;										//one if the dispatcher thread is alive & active
	int ss;												//sub-span being processed
	int LO;												//LO (within current sub-span) being processed 
	int flag;
	int have_samples[dMAX_STITCH][dMAX_NUM_FFT];		//number of unused samples remaining in a buffer
	int type;											//0 for REAL, 1 for COMPLEX
	int incr;											//size - overlap
	int buff_size;										//amount of data to be stored each time an input buffer is opened and closed = JanusAudio/BlockSize
	dINREAL* I_samples[dMAX_STITCH][dMAX_NUM_FFT];		//pointers to current input position in I/Q buffers
	dINREAL* Q_samples[dMAX_STITCH][dMAX_NUM_FFT];
	int bsize;											//size of I_samples[][] and Q_samples[][] (number of samples they hold)
	int IQout_index[dMAX_STITCH][dMAX_NUM_FFT];			//current output index for I_samples[ss][LO] and Q_samples[ss][LO]
	int IQO_idx[dMAX_STITCH][dMAX_NUM_FFT];
	int IQin_index[dMAX_STITCH][dMAX_NUM_FFT];			//current input index for I_samples[ss][LO] and Q_samples[ss][LO]
	volatile LONG buff_ready[dMAX_STITCH][dMAX_NUM_FFT];//1 if buffer ready to read; 0 if needs to be filled
	int max_writeahead;									//max allowed input samples ahead of where reading output samples

	volatile LONG snap[dMAX_STITCH][dMAX_NUM_FFT];		//set to 1 to allow a snap of raw spectrum data
	HANDLE hSnapEvent[dMAX_STITCH][dMAX_NUM_FFT];		//mutex handles; mutexes will be used to signal a snap is complete
	double *snap_buff[dMAX_STITCH][dMAX_NUM_FFT];		//pointers to buffers for the snap

	CRITICAL_SECTION PB_ControlsSection;
	CRITICAL_SECTION NA_PBControlsSection;
	CRITICAL_SECTION SetAnalyzerSection;
	CRITICAL_SECTION BufferControlSection[dMAX_STITCH][dMAX_NUM_FFT];
	CRITICAL_SECTION StitchSection;
	CRITICAL_SECTION EliminateSection[dMAX_STITCH];
	CRITICAL_SECTION ResampleSection;
}  dp, *DP;

DP pdisp[dMAX_DISPLAYS];									//array of pointers to instance data

extern __declspec( dllexport )    
void SetAnalyzer (	int disp,
					int n_fft,			//number of LO frequencies = number of ffts used in elimination
					int typ,			//0 for real input data (I only); 1 for complex input data (I & Q)
					int *flp,			//vector with one elt for each LO frequency, 1 if high-side LO, 0 otherwise 
					int sz,				//size of the fft, i.e., number of input samples
					int bf_sz,			//number of samples transferred for each OpenBuffer()/CloseBuffer()
					int win_type,		//integer specifying which window function to use
					double pi,			//PiAlpha parameter for Kaiser window
					int ovrlp,			//number of samples each fft (other than the first) is to re-use from the previous 
					int clp,			//number of fft output bins to be clipped from EACH side of each sub-span
					int fscLin,			//number of bins to clip from low end of entire span
					int fscHin,			//number of bins to clip from high end of entire span
					int n_pix,			//number of pixel values to return.  may be either <= or > number of bins 
					int n_stch,			//number of sub-spans to concatenate to form a complete span 
					int av_m,			//averaging mode
					int n_av,			//number of spans to (moving) average for pixel result 
					double av_b,		//back multiplier for weighted averaging
					int calset,			//identifier of which set of calibration data to use 
					double fmin,		//frequency at first pixel value 
					double fmax,		//frequency at last pixel value
					int max_w			//max samples to hold in input ring buffers
				 );

extern __declspec( dllexport )
void CreateAnalyzer (	int disp,
						int *success,
						char *app_data_path);

extern __declspec( dllexport )
void XCreateAnalyzer (	int disp,
						int *success,	//writes '0' to success if all went well, <0 if mem alloc failed
						int m_size,		//maximum fft size to be used
						int m_LO,		//maximum number of LO positions per subspan
						int m_stitch,	//maximum number of subspans to be concatenated
						char *app_data_path
					 );

extern __declspec( dllexport )   
void DestroyAnalyzer(int disp);

extern __declspec( dllexport )   
void GetPixels	(	int disp,
					dOUTREAL *pix,		//if new pixel values avail, copies to pix and sets flag = 1
					int *flag			//else, returns 0 (try again later)
				);

extern __declspec( dllexport )   
void GetNAPixels(	int disp,
					dOUTREAL *pix,		//if new non-averaged pixel values avail, copies to pix and sets flag = 1
					int *flag			//else, returns 0 (try again later)
				);

extern __declspec( dllexport )   
void SetCalibration (	int disp,
						int set_num,				//identifier for this calibration data set
						int n_points,				//number of calibration points in the set
						double (*cal)[dMAX_M+1]		//pointer to the calibration table, first
					);

extern __declspec( dllexport )   
void OpenBuffer(int disp, int ss, int LO, void **Ipointer, void **Qpointer);

extern __declspec( dllexport )   
void CloseBuffer(int disp, int ss, int LO);

extern __declspec( dllexport )
void Spectrum(int disp, int ss, int LO, dINREAL* pI, dINREAL* pQ);

extern __declspec( dllexport )
void Spectrum2(int disp, int ss, int LO, dINREAL* pbuff);

extern __declspec( dllexport )
void Spectrum0(int run, int disp, int ss, int LO, double* pbuff);

extern __declspec( dllexport )
void SnapSpectrum(	int disp,
					int ss,
					int LO,
					double *snap_buff);

#endif