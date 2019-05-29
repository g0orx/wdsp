#define INREAL float
#define OUTREAL float
#define dINREAL float

// WDSP vesion number
int GetWDSPVersion();

// channel
extern void OpenChannel (int channel, int in_size, int dsp_size, int input_samplerate, int dsp_rate, int output_samplerate, int type, int state, double tdelayup, double tslewup, double tdelaydown, double tslewdown, int bfo);
extern void CloseChannel (int channel);
extern void SetType (int channel, int type);
extern void SetInputBuffsize (int channel, int in_size);
extern void SetDSPBuffsize (int channel, int dsp_size);
extern void SetInputSamplerate  (int channel, int samplerate);
extern void SetDSPSamplerate (int channel, int samplerate);
extern void SetOutputSamplerate (int channel, int samplerate);
extern void SetAllRates (int channel, int in_rate, int dsp_rate, int out_rate);
int SetChannelState (int channel, int state, int dmode);
extern void SetChannelTDelayUp (int channel, double time);
extern void SetChannelTSlewUp (int channel, double time);
extern void SetChannelTDelayDown (int channel, double time);
extern void SetChannelTSlewDown (int channel, double time);

// iobuffs
extern void fexchange0 (int channel, double* in, double* out, int* error);
extern void fexchange2 (int channel, INREAL *Iin, INREAL *Qin, OUTREAL *Iout, OUTREAL *Qout, int* error);


// analyzer
#define DETECTOR_MODE_PEAK 0
#define DETECTOR_MODE_ROSENFELL 1
#define DETECTOR_MODE_AVERAGE 2
#define DETECTOR_MODE_SAMPLE 3

#define AVERAGE_MODE_NONE 0
#define AVERAGE_MODE_RECURSIVE 1
#define AVERAGE_MODE_TIME_WINDOW 2
#define AVERAGE_MODE_LOG_RECURSIVE 3

extern void XCreateAnalyzer(int disp, int *success, int m_size, int m_num_fft, int m_stitch, char *app_data_path);
extern void SetAnalyzer(int disp, int n_pixout, int n_fft, int typ, int *flp, int sz, int bf_sz, int win_type, double pi, int ovrlp, int clp, int fscLin, int fscHin, int n_pix, int n_stch, int calset, double fmin, double fmax, int max_w); 
extern void Spectrum0(int run, int disp, int ss, int LO, double* in);
extern void Spectrum(int disp, int ss, int LO, float* pI, float* pQ);
extern void GetPixels(int disp, int pixout, float *pix, int *flag);
extern void SetDisplayDetectorMode(int disp, int pixout, int mode);
extern void SetDisplayAverageMode(int disp, int pixout, int mode);
extern void SetDisplayNumAverage(int disp, int pixout, int num);
extern void SetDisplayAvBackmult (int disp, int pixout, double mult);
extern void DestroyAnalyzer(int disp);

// RXA
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

extern void SetRXAMode (int channel, int mode);
extern void SetRXABandpassRun (int channel, int run);
extern void SetRXABandpassFreqs (int channel, double low, double high);
extern void RXASetPassband (int channel, double f_low, double f_high);
extern void SetRXAFMSQRun (int channel, int run);
extern void SetRXAFMSQThreshold (int channel, double threshold);
extern void SetRXAAMSQRun (int channel, int run);
extern void SetRXAAMSQThreshold (int channel, double threshold);
extern void SetRXAEMNRRun (int channel, int run);
extern void SetRXAEMNRgainMethod (int channel, int method);
extern void SetRXAEMNRnpeMethod (int channel, int method);
extern void SetRXAEMNRPosition (int channel, int position);
extern void SetRXAANFRun(int channel, int run);
extern double GetRXAMeter (int channel, int mt);
extern void SetRXAPanelBinaural(int channel, int bin);
extern void SetRXAPanelPan (int channel, double pan);
extern void RXANBPSetFreqs (int channel, double low, double high);
extern void SetRXASNBAOutputBandwidth (int channel, double low, double high);

extern void SetRXAANRRun(int channel, int run);
extern void SetRXAEMNRaeRun (int channel, int run);
extern void SetRXASNBARun (int channel, int run);
extern void SetRXAANFRun(int channel, int run);

extern void SetRXAShiftRun (int channel, int run);
extern void SetRXAShiftFreq (int channel, double fshift);

extern void SetRXAAMDSBMode(int channel, int sbmode);
extern void SetRXAANRVals (int channel, int taps, int delay, double gain, double leakage);

extern void SetRXAAGCMode (int channel, int mode);
extern void SetRXAAGCFixed (int channel, double fixed_agc);
extern void SetRXAAGCAttack (int channel, int attack);
extern void SetRXAAGCDecay (int channel, int decay);
extern void SetRXAAGCHang (int channel, int hang);
extern void GetRXAAGCHangLevel(int channel, double *hangLevel);
extern void SetRXAAGCHangLevel(int channel, double hangLevel);
extern void GetRXAAGCHangThreshold(int channel, int *hangthreshold);
extern void SetRXAAGCHangThreshold (int channel, int hangthreshold);
extern void GetRXAAGCTop(int channel, double *max_agc);
extern void SetRXAAGCTop (int channel, double max_agc);
extern void SetRXAAGCSlope (int channel, int slope);
extern void SetRXAAGCThresh(int channel, double thresh, double size, double rate);
extern void GetRXAAGCThresh(int channel, double *thresh, double size, double rate);
extern void SetRXAFMDeviation (int channel, double deviation);
extern void RXASetNC(int channel, int nc);
extern void RXASetMP(int channel, int nc);
extern void SetRXAEQRun (int channel, int run);
extern void SetRXAGrphEQ (int channel, int *rxeq);
extern void RXANBPSetShiftFrequency (int channel, double shift);

// Diversity prototypes
extern void create_divEXT (int id, int run, int nr, int size);
extern void SetEXTDIVRun (int id, int run);
extern void SetEXTDIVBuffsize (int id, int size);
extern void SetEXTDIVNr (int id, int nr);
extern void SetEXTDIVOutput (int id, int output);
extern void SetEXTDIVRotate (int id, int nr, double *Irotate, double *Qrotate);
extern void xdivEXT (int id, int nsamples, double **in, double *out);

// Noise Blanker prototypes
extern void create_anbEXT( int id, int run, int buffsize, double samplerate, double tau, double hangtime, double advtime, double backtau, double threshold);
extern void destroy_anbEXT (int id);
extern void flush_anbEXT (int id);
extern void xanbEXT (int id, double* in, double* out);
extern void SetEXTANBRun (int id, int run);
extern void SetEXTANBSamplerate (int id, int rate);
extern void SetEXTANBTau (int id, double tau);
extern void SetEXTANBHangtime (int id, double time);
extern void SetEXTANBAdvtime (int id, double time);
extern void SetEXTANBBacktau (int id, double tau);
extern void SetEXTANBThreshold (int id, double thresh);
extern void xanbEXTF (int id, float *I, float *Q);

extern void create_nobEXT( int id, int run, int mode, int buffsize, double samplerate, double slewtime, double hangtime, double advtime, double backtau, double threshold);
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



// TXA Prototypes
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

extern void SetTXAMode (int channel, int mode);
extern void SetTXABandpassRun (int channel, int run);
extern void SetTXABandpassFreqs (int channel, double low, double high);
extern void SetTXABandpassWindow (int channel, int wintype);
extern void SetTXAEQRun (int channel, int run);
extern void SetTXACTCSSRun (int channel, int run);
extern void SetTXAAMSQRun (int channel, int run);
extern void SetTXACompressorGain (int channel, double gain);
extern void SetTXACompressorRun (int channel, int run);
extern void SetTXAosctrlRun (int channel, int run);
extern void SetTXACFIRRun (int channel, int run);
extern double GetTXAMeter (int channel, int mt);

extern void SetTXAALCSt (int channel, int state);
extern void SetTXAALCAttack (int channel, int attack);
extern void SetTXAALCDecay (int channel, int decay);
extern void SetTXAALCHang (int channel, int hang);

extern void SetTXALevelerSt (int channel, int state);
extern void SetTXALevelerAttack (int channel, int attack);
extern void SetTXALevelerDecay (int channel, int decay);
extern void SetTXALevelerHang (int channel, int hang);
extern void SetTXALevelerTop (int channel, double maxgain);

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

extern void SetTXAGrphEQ (int channel, int *txeq);

extern void SetTXAFMDeviation (int channel, double deviation);
extern void SetTXAFMEmphPosition (int channel, int position);

extern void TXASetNC(int channel, int nc);
extern void TXASetMP(int channel, int nc);

extern void SetTXAAMCarrierLevel (int channel, double c_level);

// PureSignal
extern void SetPSRunCal (int channel, int run);
extern void SetPSMox (int channel, int mox);
extern void SetPSReset (int channel, int reset);
extern void SetPSMancal (int channel, int mancal);
extern void SetPSAutomode (int channel, int automode);
extern void SetPSTurnon (int channel, int turnon);
extern void SetPSControl (int channel, int reset, int mancal, int automode, int turnon);
extern void SetPSLoopDelay (int channel, double delay);
extern void SetPSMoxDelay (int channel, double delay);
extern double SetPSTXDelay (int channel, double delay);
extern void SetPSHWPeak (int channel, double peak);
extern void SetPSPtol (int channel, double ptol);
extern void SetPSFeedbackRate (int channel, int rate);

extern void GetPSInfo (int channel, int *info);
extern void GetPSHWPeak (int channel, double* peak);
extern void GetPSMaxTX (int channel, double* maxtx);


extern void pscc (int channel, int size, double* tx, double* rx);

// EER
extern void create_eerEXT (int id, int run, int size, int rate, double mgain, double pgain, int rundelays, double mdelay, double pdelay, int amiq);
extern void xeerEXTF (int id, float* inI, float* inQ, float* outI, float* outQ, float* outMI, float* outMQ, int mox, int size);
extern void SetEERRun (int id, int run);
extern void SetEERAMIQ (int id, int amiq);
extern void SetEERRunDelays (int id, int run);
extern void SetEERPgain (int id, double gain);
extern void SetEERPdelay (int id, double delay);
extern void SetEERMgain (int id, double gain);
extern void SetEERMdelay (int id, double delay);

// resampler

extern void *create_resample (int run, int size, double* in, double* out, int in_rate, int out_rate, double fc, int ncoef, double gain);
extern void destroy_resample (void *a);
extern void flush_resample (void *a);
extern int xresample (void *a);

extern void* create_resampleFV (int in_rate, int out_rate);
extern void xresampleFV (float* input, float* output, int numsamps, int* outsamps, void* ptr);
extern void destroy_resampleFV (void* ptr);


// patchpanel

extern void SetRXAPanelRun (int channel, int run);
extern void SetRXAPanelSelect (int channel, int select);
extern void SetRXAPanelGain1 (int channel, double gain);
extern void SetRXAPanelGain2 (int channel, double gainI, double gainQ);
extern void SetRXAPanelPan (int channel, double pan);
extern void SetRXAPanelCopy (int channel, int copy);
extern void SetRXAPanelBinaural (int channel, int bin);

extern void SetTXAPanelRun (int channel, int run);
extern void SetTXAPanelGain1 (int channel, double gain);

// variable smapler

extern void* create_varsampV (int in_rate, int out_rate, int R);
extern void xvarsampV (double* input, double* output, int numsamps, double var, int* outsamps, void* ptr);
extern void destroy_varsampV (void* ptr);

// CTSCC
extern void SetTXACTCSSFreq (int channel, double freq);

// wisdom
char *wisdom_get_status();
extern void WDSPwisdom (char* directory);

