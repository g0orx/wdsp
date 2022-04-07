

#ifdef __cplusplus
extern "C" {
#endif

#define INREAL    float
#define OUTREAL   float
#define dINREAL   float
#define dOUTREAL  float

// analyzer
#define DETECTOR_MODE_PEAK         0
#define DETECTOR_MODE_ROSENFELL    1
#define DETECTOR_MODE_AVERAGE      2
#define DETECTOR_MODE_SAMPLE       3
#define DETECTOR_MODE_RMS          4

#define AVERAGE_PEAK_HOLD         -1
#define AVERAGE_MODE_NONE          0
#define AVERAGE_MODE_RECURSIVE     1
#define AVERAGE_MODE_TIME_WINDOW   2
#define AVERAGE_MODE_LOG_RECURSIVE 3

// from rxa.h
enum rxaMeterType {
        RXA_S_PK,
        RXA_S_AV,
        RXA_ADC_PK,
        RXA_ADC_AV,
        RXA_AGC_GAIN,
        RXA_AGC_PK,
        RXA_AGC_AV,
        RXA_METERTYPE_LAST
};

// from txa.h
enum txaMeterType {
  TXA_MIC_PK,
  TXA_MIC_AV,
  TXA_EQ_PK,
  TXA_EQ_AV,
  TXA_LVLR_PK,
  TXA_LVLR_AV,
  TXA_LVLR_GAIN,
  TXA_CFC_PK,
  TXA_CFC_AV,
  TXA_CFC_GAIN,
  TXA_COMP_PK,
  TXA_COMP_AV,
  TXA_ALC_PK,
  TXA_ALC_AV,
  TXA_ALC_GAIN,
  TXA_OUT_PK,
  TXA_OUT_AV,
  TXA_METERTYPE_LAST
};

// from comm.h
#define dMAX_M 1

//
// Take care of some "Windows specialities"
//
#define __stdcall 
#define LPCRITICAL_SECTION void*

//
// To make the interface simpler, use "void *" for
// pointers to some structures
//
#define EER      void*
#define ANB      void*
#define NOB      void*
#define RESAMPLE void*
#define GAIN     void*

////////////////////////////////////////////
//                                        //
// All what follows is machine-generated. //
//                                        //
////////////////////////////////////////////

//
// Interfaces from RXA.c
//

extern void SetRXAMode (int channel, int mode);
extern void RXASetPassband (int channel, double f_low, double f_high);
extern void RXASetNC (int channel, int nc);
extern void RXASetMP (int channel, int mp);

//
// Interfaces from TXA.c
//

extern void SetTXAMode (int channel, int mode);
extern void SetTXABandpassFreqs (int channel, double f_low, double f_high);
extern void TXASetNC (int channel, int nc);
extern void TXASetMP (int channel, int mp);

//
// Interfaces from amd.c
//

extern  void SetRXAAMDRun(int channel, int run);
extern  void SetRXAAMDSBMode(int channel, int sbmode);
extern  void SetRXAAMDFadeLevel(int channel, int levelfade);

//
// Interfaces from ammod.c
//

extern  void SetTXAAMCarrierLevel (int channel, double c_level);

//
// Interfaces from amsq.c
//

extern void SetRXAAMSQRun (int channel, int run);
extern void SetRXAAMSQThreshold (int channel, double threshold);
extern void SetRXAAMSQMaxTail (int channel, double tail);
extern void SetTXAAMSQRun (int channel, int run);
extern void SetTXAAMSQMutedGain (int channel, double dBlevel);
extern void SetTXAAMSQThreshold (int channel, double threshold);

//
// Interfaces from analyzer.c
//

extern void SetAnalyzer (	int disp,
					int n_pixout,
					int n_fft,
					int typ,
					int *flp,
					int sz,
					int bf_sz,
					int win_type,
					double pi,
					int ovrlp,
					int clp,
					double fscLin,
					double fscHin,
					int n_pix,
					int n_stch,
					int calset,
					double fmin,
					double fmax,
					int max_w
				 );
extern void XCreateAnalyzer(	int disp,
						int *success,
						int m_size,
						int m_num_fft,
						int m_stitch,
						char *app_data_path
						);
extern void DestroyAnalyzer(int disp);
extern void GetPixels	(	int disp,
					int pixout,
					dOUTREAL *pix,
					int *flag
				);
extern void SnapSpectrum(	int disp,
					int ss,
					int LO,
					double *snap_buff);
extern void SetCalibration (	int disp,
						int set_num,
						int n_points,
						double (*cal)[dMAX_M+1]
					);
extern void OpenBuffer(int disp, int ss, int LO, void **Ipointer, void **Qpointer);
extern void CloseBuffer(int disp, int ss, int LO);
extern void Spectrum(int disp, int ss, int LO, dINREAL* pI, dINREAL* pQ);
extern void Spectrum2(int run, int disp, int ss, int LO, dINREAL* pbuff);
extern void Spectrum0(int run, int disp, int ss, int LO, double* pbuff);
extern void SetDisplayDetectorMode (int disp, int pixout, int mode);
extern void SetDisplayAverageMode (int disp, int pixout, int mode);
extern void SetDisplayNumAverage (int disp, int pixout, int num);
extern void SetDisplayAvBackmult (int disp, int pixout, double mult);
extern void SetDisplaySampleRate (int disp, int rate);
extern void SetDisplayNormOneHz (int disp, int pixout, int norm);
extern double GetDisplayENB (int disp);

//
// Interfaces from anf.c
//

extern  void SetRXAANFRun (int channel, int run);
extern  void SetRXAANFVals (int channel, int taps, int delay, double gain, double leakage);
extern  void SetRXAANFTaps (int channel, int taps);
extern  void SetRXAANFDelay (int channel, int delay);
extern  void SetRXAANFGain (int channel, double gain);
extern  void SetRXAANFLeakage (int channel, double leakage);
extern  void SetRXAANFPosition (int channel, int position);

//
// Interfaces from anr.c
//

extern  void SetRXAANRRun (int channel, int run);
extern  void SetRXAANRVals (int channel, int taps, int delay, double gain, double leakage);
extern  void SetRXAANRTaps (int channel, int taps);
extern  void SetRXAANRDelay (int channel, int delay);
extern  void SetRXAANRGain (int channel, double gain);
extern  void SetRXAANRLeakage (int channel, double leakage);
extern  void SetRXAANRPosition (int channel, int position);

//
// Interfaces from bandpass.c
//

extern void SetRXABPSRun (int channel, int run);
extern void SetRXABPSFreqs (int channel, double f_low, double f_high);
extern void SetRXABPSWindow (int channel, int wintype);
extern void SetTXABPSRun (int channel, int run);
extern void SetTXABPSFreqs (int channel, double f_low, double f_high);
extern void SetTXABPSWindow (int channel, int wintype);
extern void SetRXABandpassRun (int channel, int run);
extern void SetRXABandpassFreqs (int channel, double f_low, double f_high);
extern void SetRXABandpassWindow (int channel, int wintype);
extern void SetRXABandpassNC (int channel, int nc);
extern void SetRXABandpassMP (int channel, int mp);
extern void SetTXABandpassRun (int channel, int run);
extern void SetTXABandpassWindow (int channel, int wintype);
extern void SetTXABandpassNC (int channel, int nc);
extern void SetTXABandpassMP (int channel, int mp);

//
// Interfaces from calcc.c
//

extern void pscc (int channel, int size, double* tx, double* rx);
extern void psccF (int channel, int size, float *Itxbuff, float *Qtxbuff, float *Irxbuff, float *Qrxbuff, int mox, int solidmox);
extern void PSSaveCorr (int channel, char* filename);
extern void PSRestoreCorr (int channel, char* filename);
extern void SetPSRunCal (int channel, int run);
extern void SetPSMox (int channel, int mox);
extern void GetPSInfo (int channel, int *info);
extern void SetPSReset (int channel, int reset);
extern void SetPSMancal (int channel, int mancal);
extern void SetPSAutomode (int channel, int automode);
extern void SetPSTurnon (int channel, int turnon);
extern void SetPSControl (int channel, int reset, int mancal, int automode, int turnon);
extern void SetPSLoopDelay (int channel, double delay);
extern void SetPSMoxDelay (int channel, double delay);
extern double SetPSTXDelay (int channel, double delay);
extern void SetPSHWPeak (int channel, double peak);
extern void GetPSHWPeak (int channel, double* peak);
extern void GetPSMaxTX (int channel, double* maxtx);
extern void SetPSPtol (int channel, double ptol);
extern void GetPSDisp (int channel, double* x, double* ym, double* yc, double* ys, double* cm, double* cc, double* cs);
extern void SetPSFeedbackRate (int channel, int rate);
extern void SetPSPinMode (int channel, int pin);
extern void SetPSMapMode (int channel, int map);
extern void SetPSStabilize (int channel, int stbl);
extern void SetPSIntsAndSpi (int channel, int ints, int spi);

//
// Interfaces from cblock.c
//

extern  void SetRXACBLRun(int channel, int setit);

//
// Interfaces from cfcomp.c
//

extern void SetTXACFCOMPRun (int channel, int run);
extern void SetTXACFCOMPPosition (int channel, int pos);
extern void SetTXACFCOMPprofile (int channel, int nfreqs, double* F, double* G, double *E);
extern void SetTXACFCOMPPrecomp (int channel, double precomp);
extern void SetTXACFCOMPPeqRun (int channel, int run);
extern void SetTXACFCOMPPrePeq (int channel, double prepeq);
extern void GetTXACFCOMPDisplayCompression (int channel, double* comp_values, int* ready);

//
// Interfaces from cfir.c
//

extern void SetTXACFIRRun (int channel, int run);
extern void SetTXACFIRNC(int channel, int nc);

//
// Interfaces from channel.c
//

extern void OpenChannel (int channel, int in_size, int dsp_size, int input_samplerate, int dsp_rate, int output_samplerate,
	int type, int state, double tdelayup, double tslewup, double tdelaydown, double tslewdown, int bfo);
extern void CloseChannel (int channel);
extern void SetType (int channel, int type);
extern void SetInputBuffsize (int channel, int in_size);
extern void SetDSPBuffsize (int channel, int dsp_size);
extern void SetInputSamplerate (int channel, int in_rate);
extern void SetDSPSamplerate (int channel, int dsp_rate);
extern void SetOutputSamplerate (int channel, int out_rate);
extern void SetAllRates (int channel, int in_rate, int dsp_rate, int out_rate);
extern int SetChannelState (int channel, int state, int dmode);
extern void SetChannelTDelayUp (int channel, double time);
extern void SetChannelTSlewUp (int channel, double time);
extern void SetChannelTDelayDown (int channel, double time);
extern void SetChannelTSlewDown (int channel, double time);

//
// Interfaces from compress.c
//

extern  void SetTXACompressorRun (int channel, int run);
extern  void SetTXACompressorGain (int channel, double gain);

//
// Interfaces from dexp.c
//

extern void create_dexp (int id, int run_dexp, int size, double* in, double* out, int rate, double dettau, double tattack, double tdecay,
	double thold, double exp_ratio, double hyst_ratio, double attack_thresh, int nc, int wtype, double lowcut, double highcut,
	int run_filt, int run_vox, int run_audelay, double audelay, void (__stdcall *pushvox)(int id, int active),
	int antivox_run, int antivox_size, int antivox_rate, double antivox_gain, double antivox_tau);
extern void destroy_dexp (int id);
extern void flush_dexp (int id);
extern void xdexp (int id);
extern void SendCBPushDexpVox (int id, void (__stdcall *pushvox)(int id, int active));
extern void SetDEXPRun (int id, int run);
extern void SetDEXPSize (int id, int size);
extern void SetDEXPIOBuffers (int id, double* in, double* out);
extern void SetDEXPRate (int id, double rate);
extern void SetDEXPDetectorTau (int id, double tau);
extern void SetDEXPAttackTime (int id, double time);
extern void SetDEXPReleaseTime (int id, double time);
extern void SetDEXPHoldTime (int id, double time);
extern void SetDEXPExpansionRatio (int id, double ratio);
extern void SetDEXPHysteresisRatio (int id, double ratio);
extern void SetDEXPAttackThreshold (int id, double thresh);
extern void SetDEXPFilterTaps (int id, int taps);
extern void SetDEXPWindowType (int id, int type);
extern void SetDEXPLowCut (int id, double lowcut);
extern void SetDEXPHighCut (int id, double highcut);
extern void SetDEXPRunSideChannelFilter (int id, int run);
extern void SetDEXPRunVox (int id, int run);
extern void SetDEXPRunAudioDelay (int id, int run);
extern void SetDEXPAudioDelay (int id, double delay);
extern void GetDEXPPeakSignal (int id, double* peak);
extern void SetAntiVOXRun (int id, int run);
extern void SetAntiVOXSize (int id, int size);
extern void SetAntiVOXRate (int id, double rate);
extern void SetAntiVOXGain (int id, double gain);
extern void SetAntiVOXDetectorTau (int id, double tau);
extern void SendAntiVOXData (int id, int nsamples, double* data);

//
// Interfaces from div.c
//

extern void create_divEXT (int id, int run, int nr, int size);
extern void destroy_divEXT (int id);
extern void flush_divEXT (int id);
extern void xdivEXT (int id, int nsamples, double **in, double *out);
extern void SetEXTDIVRun (int id, int run);
extern void SetEXTDIVBuffsize (int id, int size);
extern void SetEXTDIVNr (int id, int nr);
extern void SetEXTDIVOutput (int id, int output);
extern void SetEXTDIVRotate (int id, int nr, double *Irotate, double *Qrotate);
extern void xdivEXTF (int id, int size, float **input, float *Iout, float *Qout);

//
// Interfaces from eer.c
//

extern EER create_eer (int run, int size, double* in, double* out, double* outM, int rate, double mgain, double pgain, int rundelays, double mdelay, double pdelay, int amiq);
extern void destroy_eer (EER a);
extern void flush_eer (EER a);
extern void xeer (EER a);
extern void create_eerEXT (int id, int run, int size, int rate, double mgain, double pgain, int rundelays, double mdelay, double pdelay, int amiq);
extern void destroy_eerEXT (int id);
extern void flush_eerEXT (int id);
extern void SetEERRun (int id, int run);
extern void SetEERAMIQ (int id, int amiq);
extern void SetEERMgain (int id, double gain);
extern void SetEERPgain (int id, double gain);
extern void SetEERRunDelays (int id, int run);
extern void SetEERMdelay (int id, double delay);
extern void SetEERPdelay (int id, double delay);
extern void SetEERSize (int id, int size);
extern void SetEERSamplerate (int id, int rate);
extern void pSetEERRun (EER a, int run);
extern void pSetEERAMIQ (EER a, int amiq);
extern void pSetEERMgain (EER a, double gain);
extern void pSetEERPgain (EER a, double gain);
extern void pSetEERRunDelays (EER a, int run);
extern void pSetEERMdelay (EER a, double delay);
extern void pSetEERPdelay (EER a, double delay);
extern void pSetEERSize (EER a, int size);
extern void pSetEERSamplerate (EER a, int rate);
extern void xeerEXTF (int id, float* inI, float* inQ, float* outI, float* outQ, float* outMI, float* outMQ, int mox, int size);

//
// Interfaces from emnr.c
//

extern void SetRXAEMNRRun (int channel, int run);
extern void SetRXAEMNRgainMethod (int channel, int method);
extern void SetRXAEMNRnpeMethod (int channel, int method);
extern void SetRXAEMNRaeRun (int channel, int run);
extern void SetRXAEMNRPosition (int channel, int position);
extern void SetRXAEMNRaeZetaThresh (int channel, double zetathresh);
extern void SetRXAEMNRaePsi (int channel, double psi);

//
// Interfaces from emph.c
//

extern void SetTXAFMEmphPosition (int channel, int position);
extern void SetTXAFMEmphMP (int channel, int mp);
extern void SetTXAFMEmphNC (int channel, int nc);
extern void SetTXAFMEmphPosition (int channel, int position);

//
// Interfaces from eq.c
//

extern void SetRXAEQRun (int channel, int run);
extern void SetRXAEQNC (int channel, int nc);
extern void SetRXAEQMP (int channel, int mp);
extern void SetRXAEQProfile (int channel, int nfreqs, double* F, double* G);
extern void SetRXAEQCtfmode (int channel, int mode);
extern void SetRXAEQWintype (int channel, int wintype);
extern void SetRXAGrphEQ (int channel, int *rxeq);
extern void SetRXAGrphEQ10 (int channel, int *rxeq);
extern void SetTXAEQRun (int channel, int run);
extern void SetTXAEQNC (int channel, int nc);
extern void SetTXAEQMP (int channel, int mp);
extern void SetTXAEQProfile (int channel, int nfreqs, double* F, double* G);
extern void SetTXAEQCtfmode (int channel, int mode);
extern void SetTXAEQWintype (int channel, int wintype);
extern void SetTXAGrphEQ (int channel, int *txeq);
extern void SetTXAGrphEQ10 (int channel, int *txeq);
extern void SetRXAEQRun (int channel, int run);
extern void SetRXAEQProfile (int channel, int nfreqs, double* F, double* G);
extern void SetRXAEQCtfmode (int channel, int mode);
extern void SetRXAEQWintype (int channel, int wintype);
extern void SetRXAGrphEQ (int channel, int *rxeq);
extern void SetRXAGrphEQ10 (int channel, int *rxeq);
extern void SetTXAEQRun (int channel, int run);
extern void SetTXAEQProfile (int channel, int nfreqs, double* F, double* G);
extern void SetTXAEQCtfmode (int channel, int mode);
extern void SetTXAEQMethod (int channel, int wintype);
extern void SetTXAGrphEQ (int channel, int *txeq);
extern void SetTXAGrphEQ10 (int channel, int *txeq);

//
// Interfaces from fmd.c
//

extern void SetRXAFMDeviation (int channel, double deviation);
extern void SetRXACTCSSFreq (int channel, double freq);
extern void SetRXACTCSSRun (int channel, int run);
extern void SetRXAFMNCde (int channel, int nc);
extern void SetRXAFMMPde (int channel, int mp);
extern void SetRXAFMNCaud (int channel, int nc);
extern void SetRXAFMMPaud (int channel, int mp);

//
// Interfaces from fmmod.c
//

extern void SetTXAFMDeviation (int channel, double deviation);
extern void SetTXACTCSSFreq (int channel, double freq);
extern void SetTXACTCSSRun (int channel, int run);
extern void SetTXAFMNC (int channel, int nc);
extern void SetTXAFMMP (int channel, int mp);

//
// Interfaces from fmsq.c
//

extern void SetRXAFMSQRun (int channel, int run);
extern void SetRXAFMSQThreshold (int channel, double threshold);
extern void SetRXAFMSQNC (int channel, int nc);
extern void SetRXAFMSQMP (int channel, int mp);

//
// Interfaces from gain.c
//

extern GAIN create_gain (int run, int* prun, int size, double* in, double* out, double Igain, double Qgain);
extern void destroy_gain (GAIN a);
extern void flush_gain (GAIN a);
extern void xgain (GAIN a);
extern void pSetTXOutputLevel (GAIN a, double level);
extern void pSetTXOutputLevelRun (GAIN a, int run);
extern void pSetTXOutputLevelSize (GAIN a, int size);

//
// Interfaces from gen.c
//

extern void SetRXAPreGenRun (int channel, int run);
extern void SetRXAPreGenMode (int channel, int mode);
extern void SetRXAPreGenToneMag (int channel, double mag);
extern void SetRXAPreGenToneFreq (int channel, double freq);
extern void SetRXAPreGenNoiseMag (int channel, double mag);
extern void SetRXAPreGenSweepMag (int channel, double mag);
extern void SetRXAPreGenSweepFreq (int channel, double freq1, double freq2);
extern void SetRXAPreGenSweepRate (int channel, double rate);
extern void SetTXAPreGenRun (int channel, int run);
extern void SetTXAPreGenMode (int channel, int mode);
extern void SetTXAPreGenToneMag (int channel, double mag);
extern void SetTXAPreGenToneFreq (int channel, double freq);
extern void SetTXAPreGenNoiseMag (int channel, double mag);
extern void SetTXAPreGenSweepMag (int channel, double mag);
extern void SetTXAPreGenSweepFreq (int channel, double freq1, double freq2);
extern void SetTXAPreGenSweepRate (int channel, double rate);
extern void SetTXAPreGenSawtoothMag (int channel, double mag);
extern void SetTXAPreGenSawtoothFreq (int channel, double freq);
extern void SetTXAPreGenTriangleMag (int channel, double mag);
extern void SetTXAPreGenTriangleFreq (int channel, double freq);
extern void SetTXAPreGenPulseMag (int channel, double mag);
extern void SetTXAPreGenPulseFreq (int channel, double freq);
extern void SetTXAPreGenPulseDutyCycle (int channel, double dc);
extern void SetTXAPreGenPulseToneFreq (int channel, double freq);
extern void SetTXAPreGenPulseTransition (int channel, double transtime);
extern void SetTXAPostGenRun (int channel, int run);
extern void SetTXAPostGenMode (int channel, int mode);
extern void SetTXAPostGenToneMag (int channel, double mag);
extern void SetTXAPostGenToneFreq (int channel, double freq);
extern void SetTXAPostGenTTMag (int channel, double mag1, double mag2);
extern void SetTXAPostGenTTFreq (int channel, double freq1, double freq2);
extern void SetTXAPostGenSweepMag (int channel, double mag);
extern void SetTXAPostGenSweepFreq (int channel, double freq1, double freq2);
extern void SetTXAPostGenSweepRate (int channel, double rate);

//
// Interfaces from iir.c
//

extern void SetRXASPCWRun (int channel, int run);
extern void SetRXASPCWFreq (int channel, double freq);
extern void SetRXASPCWBandwidth (int channel, double bw);
extern void SetRXASPCWGain (int channel, double gain);
extern void SetRXAmpeakRun (int channel, int run);
extern void SetRXAmpeakNpeaks (int channel, int npeaks);
extern void SetRXAmpeakFilEnable (int channel, int fil, int enable);
extern void SetRXAmpeakFilFreq (int channel, int fil, double freq);
extern void SetRXAmpeakFilBw (int channel, int fil, double bw);
extern void SetRXAmpeakFilGain (int channel, int fil, double gain);
extern void SetTXAPHROTRun (int channel, int run);
extern void SetTXAPHROTCorner (int channel, double corner);
extern void SetTXAPHROTNstages (int channel, int nstages);

//
// Interfaces from iobuffs.c
//

extern void fexchange0 (int channel, double* in, double* out, int* error);
extern void fexchange2 (int channel, INREAL *Iin, INREAL *Qin, OUTREAL *Iout, OUTREAL *Qout, int* error);

//
// Interfaces from iqc.c
//

extern void GetTXAiqcValues (int channel, double* cm, double* cc, double* cs);
extern void SetTXAiqcValues (int channel, double* cm, double* cc, double* cs);
extern void SetTXAiqcSwap (int channel, double* cm, double* cc, double* cs);
extern void SetTXAiqcStart (int channel, double* cm, double* cc, double* cs);
extern void SetTXAiqcEnd (int channel);

//
// Interfaces from meter.c
//

extern double GetRXAMeter (int channel, int mt);
extern double GetTXAMeter (int channel, int mt);

//
// Interfaces from nbp.c
//

extern int RXANBPAddNotch (int channel, int notch, double fcenter, double fwidth, int active);
extern int RXANBPGetNotch (int channel, int notch, double* fcenter, double* fwidth, int* active);
extern int RXANBPDeleteNotch (int channel, int notch);
extern int RXANBPEditNotch (int channel, int notch, double fcenter, double fwidth, int active);
extern void RXANBPGetNumNotches (int channel, int* nnotches);
extern void RXANBPSetTuneFrequency (int channel, double tunefreq);
extern void RXANBPSetShiftFrequency (int channel, double shift);
extern void RXANBPSetNotchesRun (int channel, int run);
extern void RXANBPSetRun (int channel, int run);
extern void RXANBPSetFreqs (int channel, double flow, double fhigh);
extern void RXANBPSetWindow (int channel, int wintype);
extern void RXANBPSetNC (int channel, int nc);
extern void RXANBPSetMP (int channel, int mp);
extern void RXANBPGetMinNotchWidth (int channel, double* minwidth);
extern void RXANBPSetAutoIncrease (int channel, int autoincr);

//
// Interfaces from nob.c
//

extern ANB create_anb	(
	int run,
	int buffsize,
	double* in,
	double* out,
	double samplerate,
	double tau,
	double hangtime,
	double advtime,
	double backtau,
	double threshold
				);
extern void destroy_anb (ANB a);
extern void flush_anb (ANB a);
extern void xanb (ANB a);
extern void pSetRCVRANBRun (ANB a, int run);
extern void pSetRCVRANBBuffsize (ANB a, int size);
extern void pSetRCVRANBSamplerate (ANB a, int rate);
extern void pSetRCVRANBTau (ANB a, double tau);
extern void pSetRCVRANBHangtime (ANB a, double time);
extern void pSetRCVRANBAdvtime (ANB a, double time);
extern void pSetRCVRANBBacktau (ANB a, double tau);
extern void pSetRCVRANBThreshold (ANB a, double thresh);
extern void create_anbEXT	(
	int id,
	int run,
	int buffsize,
	double samplerate,
	double tau,
	double hangtime,
	double advtime,
	double backtau,
	double threshold
					);
extern void destroy_anbEXT (int id);
extern void flush_anbEXT (int id);
extern void xanbEXT (int id, double* in, double* out);
extern void SetEXTANBRun (int id, int run);
extern void SetEXTANBBuffsize (int id, int size);
extern void SetEXTANBSamplerate (int id, int rate);
extern void SetEXTANBTau (int id, double tau);
extern void SetEXTANBHangtime (int id, double time);
extern void SetEXTANBAdvtime (int id, double time);
extern void SetEXTANBBacktau (int id, double tau);
extern void SetEXTANBThreshold (int id, double thresh);
extern void xanbEXTF (int id, float *I, float *Q);

//
// Interfaces from nobII.c
//

extern NOB create_nob (
	int run,
	int buffsize,
	double* in,
	double* out,
	double samplerate,
	int mode,
	double advslewtime,
	double advtime,
	double hangslewtime,
	double hangtime,
	double max_imp_seq_time,
	double backtau,
	double threshold
	);
extern void destroy_nob (NOB a);
extern void flush_nob (NOB a);
extern void xnob (NOB a);
extern void pSetRCVRNOBRun (NOB a, int run);
extern void pSetRCVRNOBMode (NOB a, int mode);
extern void pSetRCVRNOBBuffsize (NOB a, int size);
extern void pSetRCVRNOBSamplerate (NOB a, int rate);
extern void pSetRCVRNOBTau (NOB a, double tau);
extern void pSetRCVRNOBHangtime (NOB a, double time);
extern void pSetRCVRNOBAdvtime (NOB a, double time);
extern void pSetRCVRNOBBacktau (NOB a, double tau);
extern void pSetRCVRNOBThreshold (NOB a, double thresh);
extern void create_nobEXT	(
	int id,
	int run,
	int mode,
	int buffsize,
	double samplerate,
	double slewtime,
	double hangtime,
	double advtime,
	double backtau,
	double threshold
					);
extern void destroy_nobEXT (int id);
extern void flush_nobEXT (int id);
extern void xnobEXT (int id, double* in, double* out);
extern void SetEXTNOBRun (int id, int run);
extern void SetEXTNOBMode (int id, int mode);
extern void SetEXTNOBBuffsize (int id, int size);
extern void SetEXTNOBSamplerate (int id, int rate);
extern void SetEXTNOBTau (int id, double tau);
extern void SetEXTNOBHangtime (int id, double time);
extern void SetEXTNOBAdvtime (int id, double time);
extern void SetEXTNOBBacktau (int id, double tau);
extern void SetEXTNOBThreshold (int id, double thresh);
extern void xnobEXTF (int id, float *I, float *Q);

//
// Interfaces from osctrl.c
//

extern void SetTXAosctrlRun (int channel, int run);

//
// Interfaces from patchpanel.c
//

extern void SetRXAPanelRun (int channel, int run);
extern void SetRXAPanelSelect (int channel, int select);
extern void SetRXAPanelGain1 (int channel, double gain);
extern void SetRXAPanelGain2 (int channel, double gainI, double gainQ);
extern void SetRXAPanelPan (int channel, double pan);
extern void SetRXAPanelCopy (int channel, int copy);
extern void SetRXAPanelBinaural (int channel, int bin);
extern void SetTXAPanelRun (int channel, int run);
extern void SetTXAPanelGain1 (int channel, double gain);
extern void SetTXAPanelSelect (int channel, int select);

//
// Interfaces from resample.c
//

extern RESAMPLE create_resample ( int run, int size, double* in, double* out, int in_rate, int out_rate, double fc, int ncoef, double gain);
extern void destroy_resample (RESAMPLE a);
extern void flush_resample (RESAMPLE a);
extern int xresample (RESAMPLE a);
extern void* create_resampleV (int in_rate, int out_rate);
extern void xresampleV (double* input, double* output, int numsamps, int* outsamps, void* ptr);
extern void destroy_resampleV (void* ptr);
extern void* create_resampleFV (int in_rate, int out_rate);
extern void xresampleFV (float* input, float* output, int numsamps, int* outsamps, void* ptr);
extern void destroy_resampleFV (void* ptr);

//
// Interfaces from rmatch.c
//

extern void xrmatchIN (void* b, double* in);
extern void xrmatchOUT (void* b, double* out);
extern void getRMatchDiags (void* b, int* underflows, int* overflows, double* var, int* ringsize, int* nring);
extern void resetRMatchDiags (void* b);
extern void forceRMatchVar (void* b, int force, double fvar);
extern void* create_rmatchV(int in_size, int out_size, int nom_inrate, int nom_outrate, int ringsize, double var);
extern void destroy_rmatchV (void* ptr);
extern void setRMatchInsize (void* ptr, int insize);
extern void setRMatchOutsize (void* ptr, int outsize);
extern void setRMatchNomInrate (void* ptr, int nom_inrate);
extern void setRMatchNomOutrate (void* ptr, int nom_outrate);
extern void setRMatchRingsize (void* ptr, int ringsize);
extern void setRMatchFeedbackGain (void* b, double feedback_gain);
extern void setRMatchSlewTime (void* b, double slew_time);
extern void setRMatchSlewTime1(void* b, double slew_time);
extern void setRMatchPropRingMin(void* ptr, int prop_min);
extern void setRMatchPropRingMax(void* ptr, int prop_max);
extern void setRMatchFFRingMin(void* ptr, int ff_ringmin);
extern void setRMatchFFRingMax(void* ptr, int ff_ringmax);
extern void setRMatchFFAlpha(void* ptr, double ff_alpha);
extern void getControlFlag(void* ptr, int* control_flag);
extern void* create_rmatchLegacyV(int in_size, int out_size, int nom_inrate, int nom_outrate, int ringsize);

//
// Interfaces from sender.c
//

extern void SetRXASpectrum (int channel, int flag, int disp, int ss, int LO);

//
// Interfaces from shift.c
//

extern void SetRXAShiftRun (int channel, int run);
extern void SetRXAShiftFreq (int channel, double fshift);

//
// Interfaces from siphon.c
//

extern void RXAGetaSipF (int channel, float* out, int size);
extern void RXAGetaSipF1 (int channel, float* out, int size);
extern void TXASetSipPosition (int channel, int pos);
extern void TXASetSipMode (int channel, int mode);
extern void TXASetSipDisplay (int channel, int disp);
extern void TXAGetaSipF (int channel, float* out, int size);
extern void TXAGetaSipF1 (int channel, float* out, int size);
extern void TXASetSipSpecmode (int channel, int mode);
extern void TXAGetSpecF1 (int channel, float* out);
extern void create_siphonEXT (int id, int run, int insize, int sipsize, int fftsize, int specmode);
extern void destroy_siphonEXT (int id);
extern void flush_siphonEXT (int id);
extern void xsiphonEXT (int id, double* buff);
extern void GetaSipF1EXT (int id, float* out, int size);
extern void SetSiphonInsize (int id, int size);

//
// Interfaces from snb.c
//

extern  void SetRXASNBARun (int channel, int run) ;
extern  void SetRXASNBAovrlp (int channel, int ovrlp) ;
extern  void SetRXASNBAasize (int channel, int size) ;
extern  void SetRXASNBAnpasses (int channel, int npasses) ;
extern  void SetRXASNBAk1 (int channel, double k1) ;
extern  void SetRXASNBAk2 (int channel, double k2) ;
extern  void SetRXASNBAbridge (int channel, int bridge) ;
extern  void SetRXASNBApresamps (int channel, int presamps) ;
extern  void SetRXASNBApostsamps (int channel, int postsamps) ;
extern  void SetRXASNBApmultmin (int channel, double pmultmin) ;
extern  void SetRXASNBAOutputBandwidth (int channel, double flow, double fhigh) ;
extern void RXABPSNBASetNC (int channel, int nc);
extern void RXABPSNBASetMP (int channel, int mp);

//
// Interfaces from utilities.c
//

extern void *malloc0 (int size);
extern  void *NewCriticalSection();
extern  void DestroyCriticalSection (LPCRITICAL_SECTION cs_ptr);
extern void analyze_bandpass_filter (int N, double f_low, double f_high, double samplerate, int wintype, int rtype, double scale);
extern void print_buffer_parameters (const char* filename, int channel);

//
// Interfaces from varsamp.c
//

extern void* create_varsampV (int in_rate, int out_rate, int R);
extern void xvarsampV (double* input, double* output, int numsamps, double var, int* outsamps, void* ptr);
extern void destroy_varsampV (void* ptr);

//
// Interfaces from version.c
//

extern int GetWDSPVersion();

//
// Interfaces from wcpAGC.c
//

extern  void SetRXAAGCMode (int channel, int mode);
extern  void SetRXAAGCAttack (int channel, int attack);
extern  void SetRXAAGCDecay (int channel, int decay);
extern  void SetRXAAGCHang (int channel, int hang);
extern  void GetRXAAGCHangLevel(int channel, double *hangLevel);
extern  void SetRXAAGCHangLevel(int channel, double hangLevel);
extern  void GetRXAAGCHangThreshold(int channel, int *hangthreshold);
extern  void SetRXAAGCHangThreshold (int channel, int hangthreshold);
extern  void GetRXAAGCThresh(int channel, double *thresh, double size, double rate);
extern  void SetRXAAGCThresh(int channel, double thresh, double size, double rate);
extern  void GetRXAAGCTop(int channel, double *max_agc);
extern  void SetRXAAGCTop (int channel, double max_agc);
extern  void SetRXAAGCSlope (int channel, int slope);
extern  void SetRXAAGCFixed (int channel, double fixed_agc);
extern  void SetRXAAGCMaxInputLevel (int channel, double level);
extern  void SetTXAALCSt (int channel, int state);
extern  void SetTXAALCAttack (int channel, int attack);
extern  void SetTXAALCDecay (int channel, int decay);
extern  void SetTXAALCHang (int channel, int hang);
extern  void SetTXAALCMaxGain (int channel, double maxgain);
extern  void SetTXALevelerSt (int channel, int state);
extern  void SetTXALevelerAttack (int channel, int attack);
extern  void SetTXALevelerDecay (int channel, int decay);
extern  void SetTXALevelerHang (int channel, int hang);
extern  void SetTXALevelerTop (int channel, double maxgain);

//
// Interfaces from wisdom.c
//

extern char* wisdom_get_status();
extern void WDSPwisdom (char* directory);
#ifdef __cplusplus
}
#endif
