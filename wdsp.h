

#ifdef __cplusplus
extern "C" {
#endif

#define INREAL    float
#define OUTREAL   float
#define dINREAL   float
#define dOUTREAL  float

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

extern void XCreateAnalyzer(int disp, int *success, int m_size, int m_num_fft,             // analyzer.c
                            int m_stitch, char *app_data_path);
extern void SetAnalyzer(int disp, int n_pixout, int n_fft, int typ, int *flp, int sz,      // analyzer.c
                        int bf_sz, int win_type, double pi, int ovrlp, int clp,
                        double fscLin,      // until WDSP 1.18: "int"
                        double fscHin,      // until WDSP 1.18: "int"
                        int n_pix, int n_stch, int calset,
                        double fmin, double fmax, int max_w); 
extern void Spectrum0(int run, int disp, int ss, int LO, double* pbuff);                   // analyzer.c
extern void Spectrum(int disp, int ss, int LO, dINREAL* pI, dINREAL* pQ);                  // analyzer.c
extern void GetPixels(int disp, int pixout, dOUTREAL *pix, int *flag);                     // analyzer.c
extern void SetDisplayDetectorMode(int disp, int pixout, int mode);                        // analyzer.c
extern void SetDisplayAverageMode(int disp, int pixout, int mode);                         // analyzer.c
extern void SetDisplayNumAverage(int disp, int pixout, int num);                           // analyzer.c
extern void SetDisplayAvBackmult (int disp, int pixout, double mult);                      // analyzer.c
extern void DestroyAnalyzer(int disp);                                                     // analyzer.c

// RXA
enum rxaMeterType {                                                                        // rxa.h
        RXA_S_PK,
        RXA_S_AV,
        RXA_ADC_PK,
        RXA_ADC_AV,
        RXA_AGC_GAIN,
        RXA_AGC_PK,
        RXA_AGC_AV,
        RXA_METERTYPE_LAST
};

extern void SetRXAMode (int channel, int mode);                                            // RXA.c
extern void SetRXABandpassRun (int channel, int run);                                      // bandpass.c
extern void SetRXABandpassFreqs (int channel, double low, double high);                    // bandpass.c
extern void SetRXABandpassWindow (int channel, int wintype);                               // bandpass.c
extern void RXASetPassband (int channel, double f_low, double f_high);                     // rxa.c
extern void SetRXAFMSQRun (int channel, int run);                                          // fmsq.c
extern void SetRXAFMSQThreshold (int channel, double threshold);                           // fmsq.c
extern void SetRXAAMSQRun (int channel, int run);                                          // amsq.c
extern void SetRXAAMSQThreshold (int channel, double threshold);                           // amsq.c
extern void SetRXAEMNRRun (int channel, int run);                                          // emnr.c
extern void SetRXAEMNRgainMethod (int channel, int method);                                // emnr.c
extern void SetRXAEMNRnpeMethod (int channel, int method);                                 // emnr.c
extern void SetRXAEMNRPosition (int channel, int position);                                // emnr.c
extern void SetRXAANFRun(int channel, int run);                                            // anf.c
extern double GetRXAMeter (int channel, int mt);                                           // meter.c
extern void RXANBPSetFreqs (int channel, double low, double high);                         // nbp.c
extern void SetRXASNBAOutputBandwidth (int channel, double low, double high);              // snb.c

extern void SetRXAANRRun(int channel, int run);                                            // anr.c
extern void SetRXAEMNRaeRun (int channel, int run);                                        // emnr.c
extern void SetRXASNBARun (int channel, int run);                                          // snb.c
extern void SetRXAANFRun(int channel, int run);                                            // anf.c

extern void SetRXAShiftRun (int channel, int run);                                         // shift.c
extern void SetRXAShiftFreq (int channel, double fshift);                                  // shift.c

extern void SetRXAAMDSBMode(int channel, int sbmode);                                      // amd.c
extern void SetRXAANRVals (int channel, int taps, int delay, double gain, double leakage); // anr.c

extern void SetRXAAGCMode (int channel, int mode);                                         // wcpAGC.c
extern void SetRXAAGCFixed (int channel, double fixed_agc);                                // wcpAGC.c
extern void SetRXAAGCAttack (int channel, int attack);                                     // wcpAGC.c
extern void SetRXAAGCDecay (int channel, int decay);                                       // wcpAGC.c
extern void SetRXAAGCHang (int channel, int hang);                                         // wcpAGC.c
extern void GetRXAAGCHangLevel(int channel, double *hangLevel);                            // wcpAGC.c
extern void SetRXAAGCHangLevel(int channel, double hangLevel);                             // wcpAGC.c
extern void GetRXAAGCHangThreshold(int channel, int *hangthreshold);                       // wcpAGC.c
extern void SetRXAAGCHangThreshold (int channel, int hangthreshold);                       // wcpAGC.c
extern void GetRXAAGCTop(int channel, double *max_agc);                                    // wpcAGC.c
extern void SetRXAAGCTop (int channel, double max_agc);                                    // wpcAGC.c
extern void SetRXAAGCSlope (int channel, int slope);                                       // wpcAGC.c
extern void SetRXAAGCThresh(int channel, double thresh, double size, double rate);         // wpcAGC.c
extern void GetRXAAGCThresh(int channel, double *thresh, double size, double rate);        // wpcAGC.c
extern void SetRXAFMDeviation (int channel, double deviation);                             // fmd.c
extern void RXASetNC(int channel, int nc);                                                 // RXA.c
extern void RXASetMP(int channel, int mp);                                                 // RXA.c
extern void SetRXAEQRun (int channel, int run);                                            // eq.c
extern void SetRXAGrphEQ (int channel, int *rxeq);                                         // eq.c
extern void RXANBPSetShiftFrequency (int channel, double shift);                           // nbp.c

// Diversity prototypes
extern void create_divEXT (int id, int run, int nr, int size);                             // div.c
extern void SetEXTDIVRun (int id, int run);                                                // div.c
extern void SetEXTDIVBuffsize (int id, int size);                                          // div.c
extern void SetEXTDIVNr (int id, int nr);                                                  // div.c
extern void SetEXTDIVOutput (int id, int output);                                          // div.c
extern void SetEXTDIVRotate (int id, int nr, double *Irotate, double *Qrotate);            // div.c
extern void xdivEXT (int id, int nsamples, double **in, double *out);                      // div.c

// Noise Blanker prototypes
extern void create_anbEXT( int id, int run, int buffsize, double samplerate, double tau,   // nob.c
                           double hangtime, double advtime, double backtau,
                           double threshold);
extern void destroy_anbEXT (int id);                                                       // nob.c
extern void flush_anbEXT (int id);                                                         // nob.c
extern void xanbEXT (int id, double* in, double* out);                                     // nob.c
extern void SetEXTANBRun (int id, int run);                                                // nob.c
extern void SetEXTANBSamplerate (int id, int rate);                                        // nob.c
extern void SetEXTANBTau (int id, double tau);                                             // nob.c
extern void SetEXTANBHangtime (int id, double time);                                       // nob.c
extern void SetEXTANBAdvtime (int id, double time);                                        // nob.c
extern void SetEXTANBBacktau (int id, double tau);                                         // nob.c
extern void SetEXTANBThreshold (int id, double thresh);                                    // nob.c
extern void xanbEXTF (int id, float *I, float *Q);                                         // nob.c (legacy interface)

extern void create_nobEXT( int id, int run, int mode, int buffsize, double samplerate,     // nobII.c
                           double slewtime, double hangtime, double advtime,
                           double backtau, double threshold);
extern void destroy_nobEXT (int id);                                                       // nobII.c
extern void flush_nobEXT (int id);                                                         // nobII.c
extern void xnobEXT (int id, double* in, double* out);                                     // nobII.c
extern void SetEXTNOBRun (int id, int run);                                                // nobII.c
extern void SetEXTNOBMode (int id, int mode);                                              // nobII.c
extern void SetEXTNOBBuffsize (int id, int size);                                          // nobII.c
extern void SetEXTNOBSamplerate (int id, int rate);                                        // nobII.c
extern void SetEXTNOBTau (int id, double tau);                                             // nobII.c
extern void SetEXTNOBHangtime (int id, double time);                                       // nobII.c
extern void SetEXTNOBAdvtime (int id, double time);                                        // nobII.c
extern void SetEXTNOBBacktau (int id, double tau);                                         // nobII.c
extern void SetEXTNOBThreshold (int id, double thresh);                                    // nobII.c
extern void xnobEXTF (int id, float *I, float *Q);                                         // nobII.c (legacy interface)



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

extern void SetTXAMode (int channel, int mode);                                            // TXA.c 
extern void SetTXABandpassRun (int channel, int run);                                      // bandpass.c
extern void SetTXABandpassFreqs (int channel, double low, double high);                    // TXA.c
extern void SetTXABandpassWindow (int channel, int wintype);                               // bandbass.c
extern void SetTXAEQRun (int channel, int run);                                            // eq.c
extern void SetTXACTCSSRun (int channel, int run);                                         // fmmod.c
extern void SetTXAAMSQRun (int channel, int run);                                          // amsq.c
extern void SetTXACompressorGain (int channel, double gain);                               // compress.c
extern void SetTXACompressorRun (int channel, int run);                                    // compress.c
extern void SetTXAosctrlRun (int channel, int run);                                        // osctrl.c
extern void SetTXACFIRRun (int channel, int run);                                          // cfir.c
extern double GetTXAMeter (int channel, int mt);                                           // meter.c

extern void SetTXAALCSt (int channel, int state);                                          // wcpAGC.c
extern void SetTXAALCAttack (int channel, int attack);                                     // wcpAGC.c
extern void SetTXAALCDecay (int channel, int decay);                                       // wcpAGC.c
extern void SetTXAALCHang (int channel, int hang);                                         // wcpAGC.c

extern void SetTXALevelerSt (int channel, int state);                                      // wcpAGC.c
extern void SetTXALevelerAttack (int channel, int attack);                                 // wcpAGC.c
extern void SetTXALevelerDecay (int channel, int decay);                                   // wcpAGC.c
extern void SetTXALevelerHang (int channel, int hang);                                     // wcpAGC.c
extern void SetTXALevelerTop (int channel, double maxgain);                                // wcpAGC.c

extern void SetTXAPreGenRun (int channel, int run);                                        // gen.c
extern void SetTXAPreGenMode (int channel, int mode);                                      // gen.c
extern void SetTXAPreGenToneMag (int channel, double mag);                                 // gen.c
extern void SetTXAPreGenToneFreq (int channel, double freq);                               // gen.c
extern void SetTXAPreGenNoiseMag (int channel, double mag);                                // gen.c
extern void SetTXAPreGenSweepMag (int channel, double mag);                                // gen.c
extern void SetTXAPreGenSweepFreq (int channel, double freq1, double freq2);               // gen.c
extern void SetTXAPreGenSweepRate (int channel, double rate);                              // gen.c
extern void SetTXAPreGenSawtoothMag (int channel, double mag);                             // gen.c
extern void SetTXAPreGenSawtoothFreq (int channel, double freq);                           // gen.c
extern void SetTXAPreGenTriangleMag (int channel, double mag);                             // gen.c
extern void SetTXAPreGenTriangleFreq (int channel, double freq);                           // gen.c
extern void SetTXAPreGenPulseMag (int channel, double mag);                                // gen.c
extern void SetTXAPreGenPulseFreq (int channel, double freq);                              // gen.c
extern void SetTXAPreGenPulseDutyCycle (int channel, double dc);                           // gen.c
extern void SetTXAPreGenPulseToneFreq (int channel, double freq);                          // gen.c
extern void SetTXAPreGenPulseTransition (int channel, double transtime);                   // gen.c
extern void SetTXAPostGenRun (int channel, int run);                                       // gen.c
extern void SetTXAPostGenMode (int channel, int mode);                                     // gen.c
extern void SetTXAPostGenToneMag (int channel, double mag);                                // gen.c
extern void SetTXAPostGenToneFreq (int channel, double freq);                              // gen.c
extern void SetTXAPostGenTTMag (int channel, double mag1, double mag2);                    // gen.c
extern void SetTXAPostGenTTFreq (int channel, double freq1, double freq2);                 // gen.c
extern void SetTXAPostGenSweepMag (int channel, double mag);                               // gen.c
extern void SetTXAPostGenSweepFreq (int channel, double freq1, double freq2);              // gen.c
extern void SetTXAPostGenSweepRate (int channel, double rate);                             // gen.c

extern void SetTXAGrphEQ (int channel, int *txeq);                                         // eq.c

extern void SetTXAFMDeviation (int channel, double deviation);                             // fmmod.c
extern void SetTXAFMEmphPosition (int channel, int position);                              // emph.c

extern void TXASetNC(int channel, int nc);                                                 // TXA.c
extern void TXASetMP(int channel, int mp);                                                 // TXA.c

extern void SetTXAAMCarrierLevel (int channel, double c_level);                            // ammod.c

// PureSignal
extern void SetPSRunCal (int channel, int run);                                            // calcc.c
extern void SetPSMox (int channel, int mox);                                               // calcc.c
extern void SetPSReset (int channel, int reset);                                           // calcc.c
extern void SetPSMancal (int channel, int mancal);                                         // calcc.c
extern void SetPSAutomode (int channel, int automode);                                     // calcc.c
extern void SetPSTurnon (int channel, int turnon);                                         // calcc.c
extern void SetPSControl (int channel, int reset, int mancal, int automode, int turnon);   // calcc.c
extern void SetPSLoopDelay (int channel, double delay);                                    // calcc.c
extern void SetPSMoxDelay (int channel, double delay);                                     // calcc.c
extern double SetPSTXDelay (int channel, double delay);                                    // calcc.c
extern void SetPSHWPeak (int channel, double peak);                                        // calcc.c
extern void SetPSPtol (int channel, double ptol);                                          // calcc.c
extern void SetPSFeedbackRate (int channel, int rate);                                     // calcc.c
extern void SetPSIntsAndSpi (int channel, int ints, int spi);                              // calcc.c
extern void SetPSStabilize (int channel, int stbl);                                        // calcc.c
extern void SetPSMapMode (int channel, int map);                                           // calcc.c
extern void SetPSPinMode (int channel, int pin);                                           // calcc.c

extern void GetPSInfo (int channel, int *info);                                            // calcc.c
extern void GetPSHWPeak (int channel, double* peak);                                       // calcc.c
extern void GetPSMaxTX (int channel, double* maxtx);                                       // calcc.c


extern void pscc (int channel, int size, double* tx, double* rx);                          // calcc.c

// EER
extern void create_eerEXT (int id, int run, int size, int rate, double mgain,              // eer.c
                           double pgain, int rundelays, double mdelay, double pdelay,
                           int amiq);
extern void xeerEXTF (int id, float* inI, float* inQ, float* outI, float* outQ,            // eer.c (legacy interface)
                      float* outMI, float* outMQ, int mox, int size);
extern void SetEERRun (int id, int run);                                                   // eer.c
extern void SetEERAMIQ (int id, int amiq);                                                 // eer.c
extern void SetEERRunDelays (int id, int run);                                             // eer.c
extern void SetEERPgain (int id, double gain);                                             // eer.c
extern void SetEERPdelay (int id, double delay);                                           // eer.c
extern void SetEERMgain (int id, double gain);                                             // eer.c
extern void SetEERMdelay (int id, double delay);                                           // eer.c

// resampler (declare with void* instead of RESAMPLE)

extern void *create_resample (int run, int size, double* in, double* out,                  // resample.c
                              int in_rate, int out_rate, double fc, int ncoef,
                              double gain);
extern void destroy_resample (void *a);                                                    // resample.c
extern void flush_resample (void *a);                                                      // resample.c
extern int xresample (void *a);                                                            // resample.c

extern void* create_resampleFV (int in_rate, int out_rate);                                // resample.c
extern void xresampleFV (float* input, float* output, int numsamps,                        // resample.c
                         int* outsamps, void* ptr);
extern void destroy_resampleFV (void* ptr);                                                // resample.c


// patchpanel

extern void SetRXAPanelRun (int channel, int run);                                         // patchpanel.c
extern void SetRXAPanelSelect (int channel, int select);                                   // patchpanel.c
extern void SetRXAPanelGain1 (int channel, double gain);                                   // patchpanel.c
extern void SetRXAPanelGain2 (int channel, double gainI, double gainQ);                    // patchpanel.c
extern void SetRXAPanelPan (int channel, double pan);                                      // patchpanel.c
extern void SetRXAPanelCopy (int channel, int copy);                                       // patchpanel.c
extern void SetRXAPanelBinaural (int channel, int bin);                                    // patchpanel.c

extern void SetTXAPanelRun (int channel, int run);                                         // patchpanel.c
extern void SetTXAPanelSelect (int channel, int select);                                   // patchpanel.c
extern void SetTXAPanelGain1 (int channel, double gain);                                   // patchpanel.c

// variable smapler

extern void* create_varsampV (int in_rate, int out_rate, int R);                           // varsamp.c
extern void xvarsampV (double* input, double* output, int numsamps, double var,            // varsamp.c
                       int* outsamps, void* ptr);
extern void destroy_varsampV (void* ptr);                                                  // varsamp.c

// CTSCC
extern void SetTXACTCSSFreq (int channel, double freq);                                    // fmmod.c

// wisdom
char *wisdom_get_status();                                                                 // wisdom.c
extern void WDSPwisdom (char* directory);                                                  // wisdom.c

#ifdef __cplusplus
}
#endif
