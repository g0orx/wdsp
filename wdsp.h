#define PORT extern
#define INREAL float
#define OUTREAL float
#define dINREAL float


// channel
PORT void OpenChannel (int channel, int in_size, int dsp_size, int input_samplerate, int dsp_rate, int output_samplerate, int type, int state, double tdelayup, double tslewup, double tdelaydown, double tslewdown, int bfo);
PORT void CloseChannel (int channel);
PORT void SetType (int channel, int type);
PORT void SetInputBuffsize (int channel, int in_size);
PORT void SetDSPBuffsize (int channel, int dsp_size);
PORT void SetInputSamplerate  (int channel, int samplerate);
PORT void SetDSPSamplerate (int channel, int samplerate);
PORT void SetOutputSamplerate (int channel, int samplerate);
PORT void SetAllRates (int channel, int in_rate, int dsp_rate, int out_rate);
PORT void SetChannelState (int channel, int state, int dmode);
PORT void SetChannelTDelayUp (int channel, double time);
PORT void SetChannelTSlewUp (int channel, double time);
PORT void SetChannelTDelayDown (int channel, double time);
PORT void SetChannelTSlewDown (int channel, double time);

// iobuffs
PORT void fexchange0 (int channel, double* in, double* out, int* error);
PORT void fexchange2 (int channel, INREAL *Iin, INREAL *Qin, OUTREAL *Iout, OUTREAL *Qout, int* error);


// analyzer
#define DETECTOR_MODE_PEAK 0
#define DETECTOR_MODE_ROSENFELL 1
#define DETECTOR_MODE_AVERAGE 2
#define DETECTOR_MODE_SAMPLE 3

#define AVERAGE_MODE_NONE 0
#define AVERAGE_MODE_RECURSIVE 1
#define AVERAGE_MODE_TIME_WINDOW 2
#define AVERAGE_MODE_LOG_RECURSIVE 3

PORT void XCreateAnalyzer(int disp, int *success, int m_size, int m_num_fft, int m_stitch, char *app_data_path);
PORT void SetAnalyzer(int disp, int n_pixout, int n_fft, int typ, int *flp, int sz, int bf_sz, int win_type, double pi, int ovrlp, int clp, int fscLin, int fscHin, int n_pix, int n_stch, int calset, double fmin, double fmax, int max_w); 
PORT void Spectrum0(int run, int disp, int ss, int LO, double* in);
PORT void Spectrum(int disp, int ss, int LO, float* pI, float* pQ);
PORT void GetPixels(int disp, int pixout, float *pix, int *flag);
PORT void SetDisplayDetectorMode(int disp, int pixout, int mode);
PORT void SetDisplayAverageMode(int disp, int pixout, int mode);
PORT void SetDisplayNumAverage(int disp, int pixout, int num);

// RXA
PORT void SetRXAMode (int channel, int mode);
PORT void SetRXABandpassRun (int channel, int run);
PORT void SetRXABandpassFreqs (int channel, double low, double high);
PORT void SetRXAFMSQRun (int channel, int run);
PORT void SetRXAEMNRRun (int channel, int run);
PORT void SetRXAEMNRgainMethod (int channel, int method);
PORT void SetRXAEMNRnpeMethod (int channel, int method);
PORT void SetRXAEMNRPosition (int channel, int position);
PORT void SetRXAANFRun(int channel, int run);
PORT double GetRXAMeter (int channel, int mt);
PORT void SetRXAPanelBinaural(int channel, int bin);
PORT void SetRXAPanelPan (int channel, double pan);
PORT void RXANBPSetFreqs (int channel, double low, double high);
PORT void SetRXASNBAOutputBandwidth (int channel, double low, double high);

PORT void SetRXAANRRun(int channel, int run);
PORT void SetRXAEMNRaeRun (int channel, int run);
PORT void SetRXASNBARun (int channel, int run);
PORT void SetRXAANFRun(int channel, int run);

PORT void SetRXAShiftRun (int channel, int run);
PORT void SetRXAShiftFreq (int channel, double fshift);

PORT void SetRXAAGCMode (int channel, int mode);
PORT void SetRXAAGCTop (int channel, double max_agc);
PORT void SetRXAAMDSBMode(int channel, int sbmode);
PORT void SetRXAANRVals (int channel, int taps, int delay, double gain, double leakage);

// TXA Prototypes
PORT void SetTXAMode (int channel, int mode);
PORT void SetTXABandpassRun (int channel, int run);
PORT void SetTXABandpassFreqs (int channel, double low, double high);
PORT void SetTXABandpassWindow (int channel, int wintype);
PORT void SetTXAPreGenRun (int channel, int run);
PORT void SetTXAPostGenRun (int channel, int run);
PORT void SetTXAEQRun (int channel, int run);
PORT void SetTXACTCSSRun (int channel, int run);
PORT void SetTXAAMSQRun (int channel, int run);
PORT void SetTXACompressorRun (int channel, int run);
PORT void SetTXAosctrlRun (int channel, int run);
PORT void SetTXACFIRRun (int channel, int run);

// resampler

PORT void *create_resample (int run, int size, double* in, double* out, int in_rate, int out_rate, double fc, int ncoef, double gain);

PORT void destroy_resample (void *a);

PORT void flush_resample (void *a);

PORT int xresample (void *a);


PORT void* create_resampleFV (int in_rate, int out_rate);
PORT void xresampleFV (float* input, float* output, int numsamps, int* outsamps, void* ptr);
PORT void destroy_resampleFV (void* ptr);

// wisdom
char *wisdom_get_status();
PORT void WDSPwisdom (char* directory);

