package org.openhpsdr.dsp;

import java.io.File;

/**
 * Java native interface for using WDSP library (version 1.18).
 *
 * For details see WDSP_Guide.pdf.
 *
 * Note: Not for all the methods in WDSP a native call is made... some work ahead...
 *
 */
public class Wdsp {

  private static Wdsp instance = null;

  public static Wdsp getInstance() {
    if (instance == null) {
      instance = new Wdsp();
    }
    return instance;
  }

  private Wdsp() {
    // Use the getInstance method; not allowed to instantiate; singleton.
  }

  static {

    System.out.println("JVM is " + System.getProperty("os.arch") + " bit");

    if(System.getProperty("os.name").startsWith("Windows")) {

      String libraryPath=System.getProperty("user.dir")+File.separator+"lib"+File.separator+"windows";

      if (System.getProperty("os.arch") != null && System.getProperty("os.arch").endsWith("64")) {
        libraryPath = libraryPath + File.separator + "fftw_x64";
      } else {
        libraryPath = libraryPath + File.separator + "fftw_x86";
      }
      System.load(libraryPath+File.separator+"libfftw3-3.dll");
      System.load(libraryPath+File.separator+"wdsp.dll");
    }

    if(System.getProperty("os.name").startsWith("Linux")) {

      String libraryPath=System.getProperty("user.dir")+File.separator+"lib"+File.separator+"linux";
      System.load(libraryPath+File.separator+"libfftw3.so");
      System.load(libraryPath+File.separator+"libwdsp.so");
      System.load(libraryPath+File.separator+"libwdspj.so");
      System.loadLibrary("wdspj");
    }

    if(System.getProperty("os.name").startsWith("Mac")) {

      String libraryPath=System.getProperty("user.dir")+File.separator+"lib"+File.separator+"mac";
      System.load(libraryPath+File.separator+"libfftw3.3.dylib");
      System.load(libraryPath+File.separator+"libwdsp.dylib");
      System.loadLibrary("wdsp");
    }

  }

  /**
   * WDSP version.
   *
   * @return version/
   */
  public native int GetWDSPVersion();

  /**
   * FFTW wisdom file
   */
  public native void WDSPwisdom(String dir);

  /**
   * Channel Settings / Information.
   */
  public native void OpenChannel(
    int channel,
    int in_size,
    int dsp_size,
    int input_samplerate,
    int dsp_rate,
    int output_samplerate,
    int type,
    int state,
    double tdelayup,
    double tslewup,
    double tdelaydown,
    double tslewdown,
    int bfo);

  public native void CloseChannel(int channel);

  public native void SetChannelState(int channel, int state, int dmode);

  public native void fexchange0(
    int channel,
    double[] in,
    double[] out,
    int[] error);

  public native void fexchange2(int channel,
                                float[] Iin,
                                float[] Qin,
                                float[] Iout,
                                float[] Qout,
                                int[] error);

  /**
   * RXA Receiver Unit.
   */

  public native void SetRXAAGCMaxInputLevel (int channel, double level);

  /**
   * Frequency Shifter
   */

  public native void SetRXAShiftRun (int channel, int run);

  public native void SetRXAShiftFreq (int channel, double fshift);

  /**
   * Signal Generator
   */

  public native void SetRXAPreGenRun (int channel, int run);

  public native void SetRXAPreGenMode (int channel, int mode);

  public native void SetRXAPreGenToneMag (int channel, double mag);

  public native void SetRXAPreGenToneFreq (int channel, double freq);

  public native void SetRXAPreGenNoiseMag (int channel, double mag);

  public native void SetRXAPreGenSweepMag (int channel, double mag);

  public native void SetRXAPreGenSweepFreq (int channel, double freq1, double freq2);

  public native void SetRXAPreGenSweepRate (int channel, double rate);

  /**
   * Input, S, and AGC Meters
   */
  public native double GetRXAMeter (int channel, int mt);

  /**
   * Bandpass Filter Settings
   */
  public native void RXANBPSetRun (int channel, int run);

  public native void RXANBPSetWindow (int channel, int wintype);

  /**
   * Notch Filter Settings
   */
  public native void RXANBPSetNotchesRun (int channel, int run);

  public native void RXANBPGetMinNotchWidth (int channel, double minwidth);

  public native void RXANBPSetAutoIncrease (int channel, int autoincr);

  public native void RXANBPSetTuneFrequency (int channel, double tunefreq);

  public native void RXANBPSetShiftFrequency (int channel, double shift);

  public native void RXANBPGetNumNotches (int channel, int nnotches);

  public native int RXANBPAddNotch (int channel,
                                    int notch,
                                    double fcenter,
                                    double fwidth,
                                    int active);

  public native int RXANBPGetNotch (int channel,
                                    int notch,
                                    double fcenter,
                                    double fwidth,
                                    int active);

  public native int RXANBPDeleteNotch (int channel, int notch);

  public native int RXANBPEditNotch (int channel,
                                     int notch,
                                     double fcenter,
                                     double fwidth,
                                     int active);

  /**
   * Post-filter Display Sender
   */

  public native void SetRXASpectrum (int channel,
                                     int flag,
                                     int disp,
                                     int ss,
                                     int LO);

  /**
   * AM Squelch
   */

  public native void SetRXAAMSQRun (int channel, int run);

  public native void RXAAMSQThreshold (int channel, double threshold);

  public native void SetRXAAMSQMaxTail (int channel, double tail);

  /**
   * AM/SAM Demodulator
   */

  public native void SetRXAAMDSBMode (int channel, int sbmode);

  public native void SetRXAAMDFadeLevel (int channel, int levelfade);

  /**
   * FM Demodulator
   */

  public native void SetRXAFMDeviation (int channel, double deviation);

  public native void SetRXACTCSSRun (int channel, int run);

  public native void SetRXACTCSSFreq (int channel, double freq);

  /**
   * FM Squelch
   */

  public native void SetRXAFMSQRun (int channel, int run);

  public native void SetRXAFMSQThreshold (int channel, double threshold);

  /**
   * Spectral Noise Blanker
   */

  public native void SetRXASNBARun (int channel, int run);

  /**
   * Equalizer
   */

  public native void SetRXAEQRun (int channel, int run);

  public native void SetRXAEQWinType (int channel, int wintype);

  public native void SetRXAEQCtfmode (int channel, int mode);

  public native void SetRXAEQProfile (int channel, int nfreqs, double F, double G);

  /**
   * AGC
   */

  public native void SetRXAAGCMode (int channel, int mode);

  public native void SetRXAAGCAttack (int channel, int attack);

  public native void SetRXAAGCDecay (int channel, int decay);

  public native void SetRXAAGCHang(int channel, int hang);

  public native void GetRXAAGCHangLevel (int channel, double[] hanglevel);

  public native void SetRXAAGCHangLevel (int channel, double hanglevel);

  public native void GetRXAAGCHangThreshold (int channel, int hangthreshold);

  public native void SetRXAAGCHangThreshold (int channel, int hangthreshold);

  public native void GetRXAAGCThresh (int channel, double[] thresh, double size, double rate);

  public native void SetRXAAGCThresh (int channel, double thresh, double size, double rate);

  public native void GetRXAAGCTop (int channel, double[] max_agc);

  public native void SetRXAAGCTop(int channel, double max_agc);

  public native void SetRXAAGCSlope (int channel, int slope);

  public native void SetRXAAGCFixed (int channel, double fixed_agc);

  /**
   * Automatic Notch Filter
   */

  public native void SetRXAANFRun (int channel, int run);

  public native void SetRXAANFTaps (int channel, int taps);

  public native void SetRXAANFDelay (int channel, int delay);

  public native void SetRXAANFGain (int channel, double gain);

  public native void SetRXAANFLeakage (int channel, double leakage);

  public native void SetRXAANFVals (int channel, int taps, int delay, double gain, double leakage);

  public native void SetRXAANFPosition (int channel, int position);


  /**
   * LMS Noise Reduction
   */

  public native void SetRXAANRRun (int channel, int run);

  public native void SetRXAANRTaps (int channel, int taps);

  public native void SetRXAANRDelay (int channel, int delay);

  public native void SetRXAANRGain (int channel, double gain);

  public native void SetRXAANRLeakage (int channel, double leakage);

  public native void SetRXAANRVals (int channel, int taps, int delay, double gain, double leakage);

  /**
   * Spectral Noise Reduction
   */

  public native void SetRXAEMNRRun (int channel, int run);

  public native void SetRXAEMNRgainMethod(int channel, int method);

  public native void SetRXAEMNRnpeMethod(int channel, int method);

  public native void SetRXAEMNRaeRun(int channel, int run);

  public native void SetRXAEMNRPosition(int channel, int position);

  /**
   * Bandpass Filter
   */

  public native void SetRXABandpassWindow (int channel, int wintype);

  /**
   * Scope/Phase Display Sender
   */

  public native void RXAGetaSipF (int channel, float[] out, int size);

  public native void RXAGetaSipF1 (int channel, float[] out, int size);

  /**
   * AM Carrier Block
   */

  public native void SetRXACBLRun (int channel, int run);

  /**
   * CW Peaking Filter
   */

  public native void SetRXASPCWRun (int channel, int run);

  public native void SetRXASPCWFreq (int channel, double freq);

  public native void SetRXASPCWBandwidth (int channel, double bw);

  public native void SetRXASPCWGain (int channel, double gain);

  /**
   * Dolly Filter
   */

  public native void SetRXAmpeakRun (int channel, int run);

  public native void SetRXAmpeakNpeaks (int channel, int npeaks);

  public native void SetRXAmpeakFilEnable (int channel, int fil, int enable);

  public native void SetRXAmpeakFilFreq (int channel, int fil, double freq);

  public native void SetRXAmpeakFilBw (int channel, int fil, double bw);

  public native void SetRXAmpeakFilGain (int channel, int fil, double gain);

  /**
   * Patch Panel - Audio Output Configuration
   */

  public native void SetRXAPanelRun (int channel, int run);

  public native void SetRXAPanelSelect (int channel, int select);

  public native void SetRXAPanelGain1 (int channel, double gain);

  public native void SetRXAPanelGain2 (int channel, double gainI, double gainQ);

  public native void SetRXAPanelPan (int channel, double pan);

  public native void SetRXAPanelCopy (int channel, int copy);

  public native void SetRXAPanelBinaural (int channel, int bin);


  /**
   * RXA Collectives & General Controls
   */

  public static final int LSB = 0;
  public static final int USB = 1;
  public static final int DSB = 2;
  public static final int CWL = 3;
  public static final int CWU = 4;
  public static final int FM = 5;
  public static final int AM = 6;
  public static final int DIGU = 7;
  public static final int SPEC = 8;
  public static final int DIGL = 9;
  public static final int SAM = 10;
  public static final int DRM = 11;

  public native void SetRXAMode(int channel, int mode);

  public native void RXASetPassband (int channel, double f_low, double f_high);

  public native void RXASetNC (int channel, int nc);

  public native void RXASetMP (int channel, int mp);

  /**
   * The TXA Transmitter Unit
   */

  public native void SetTXAPreGenRun (int channel, int run);

  public native void SetTXAPreGenMode (int channel, int mode);

  public native void SetTXAPreGenToneMag (int channel, double mag);

  public native void SetTXAPreGenToneFreq (int channel, double freq);

  public native void SetTXAPreGenNoiseMag (int channel, double mag);

  public native void SetTXAPreGenSweepMag (int channel, double mag);

  public native void SetTXAPreGenSweepFreq (int channel, double freq1, double freq2);

  public native void SetTXAPreGenSweepRate (int channel, double rate);

  public native void SetTXAPreGenSawtoothMag (int channel, double mag);

  public native void SetTXAPreGenSawtoothFreq (int channel, double freq);

  public native void SetTXAPreGenTriangleMag (int channel, double mag);

  public native void SetTXAPreGenTriangleFreq (int channel, double freq);

  public native void SetTXAPreGenPulseMag (int channel, double mag);

  public native void SetTXAPreGenPulseFreq (int channel, double freq);

  public native void SetTXAPreGenPulseDutyCycle (int channel, double dc);

  public native void SetTXAPreGenPulseToneFreq (int channel, double freq);

  public native void SetTXAPreGenPulseTransition (int channel, double transtime);

  public native void SetTXAPostGenRun (int channel, int run);

  public native void SetTXAPostGenMode (int channel, int mode);

  public native void SetTXAPostGenToneMag (int channel, double mag);

  public native void SetTXAPostGenToneFreq (int channel, double freq);

  public native void SetTXAPostGenTTMag (int channel, double mag1, double mag2);

  public native void SetTXAPostGenTTFreq (int channel, double freq1, double freq2);

  public native void SetTXAPostGenSweepMag (int channel, double mag);

  public native void SetTXAPostGenSweepFreq (int channel, double freq1, double freq2);

  public native void SetTXAPostGenSweepRate (int channel, double rate);

  /**
   * PatchPanel
   */


  public native void SetTXAPanelRun (int channel, int run);

  public native void SetTXAPanelSelect (int channel, int select);

  public native void SetTXAPanelGain1 (int channel, double gain);

  /**
   * Noise Gate
   */

  public native void SetTXAAMSQRun (int channel, int run);

  public native void SetTXAAMSQMutedGain (int channel, double dBlevel);

  public native void SetTXAAMSQThreshold (int channel, double threshold);

  /**
   * Equalizer
   */

  public native void SetTXAEQRun (int channel, int run);

  public native void SetTXAEQWintype (int channel, int wintype);

  public native void SetTXAEQCtfmode (int channel, int mode);

  public native void SetTXAEQProfile (int channel, int nfreqs, double F, double G);

  /**
   * FM Pre-emphasis
   */


  public native void SetTXAFMEmphPosition (int channel, int position);

  /**
   * Leveler
   */

  public native void SetTXALevelerSt (int channel, int state);

  public native void SetTXALevelerAttack (int channel, int attack);

  public native void SetTXALevelerDecay (int channel, int decay);

  public native void SetTXALevelerTop (int channel, double maxgain);

  /**
   *   Phase Rotator
   */

  public native void SetTXAPHROTRun (int channel, int run);

  public native void SetTXAPHROTCorner (int channel, double frequency);

  public native void SetTXAPHROTNstages (int channel, int nstages);


  /**
   * Continuous Frequency Compressor (CFC)
   * */

  public native void SetTXACFCOMPRun (int channel, int run);

  public native void SetTXACFCOMPprofile (int channel, int nfreqs, double F, double G, double E);

  public native void SetTXACFCOMPPrecomp (int channel, double precomp);

  public native void SetTXACFCOMPPeqRun (int channel, int run);

  public native void SetTXACFCOMPPrePeq (int channel, double prepeq);


  /**
   * Bandpass Filters
   */

  public native void SetTXABandpassFreqs (int channel, double f_low, double f_high);

  public native  void SetTXABandpassWindow (int channel, int wintype);


  /**
   * Speech Processor
   */

  public native void SetTXACompressorRun (int channel, int run);

  public native void SetTXACompressorGain (int channel, double gain);

  /**
   * CESSB Overshoot Control
   */

  public native void SetTXAosctrlRun (int channel, int run);

  /**
   * ALC
   */

  public native void SetTXAALCSt (int channel, int state);

  public native void SetTXAALCAttack (int channel, int attack);

  public native void SetTXAALCDecay (int channel, int decay);

  public native void SetTXAALCMaxGain (int channel, double maxgain);

  /**
   * AM Modulator
   */

  public native void SetTXAAMCarrierLevel (int channel, double c_level);

  /**
   * FM Modulator
   */

  public native void SetTXAFMDeviation (int channel, double deviation);

  public native void SetTXACTCSSRun (int channel, int run);

  public native void SetTXACTCSSFreq (int channel, double freq);

  /**
   * Siphon
   */

  public native void TXASetSipMode (int channel, int mode);

  public native void TXASetSipDisplay (int channel, int disp);

  public native void TXAGetaSipF (int channel, float[] out, int size);

  public native void TXAGetaSipF1 (int channel, float[] out, int size);

  public native void TXAGetaSpecF1 (int channel, float[] out);

  public native void TXASetSipSpecmode (int channel, int mode);

  /**
   * PureSignal I/Q Predistortion
   */

  //TODO

  //CFIR Filter

  public native  void SetTXACFIRRun (int channel, int run);

  /*
  TXA Collectives & General Controls
   */
  public native void SetTXAMode (int channel, int mode);

  public native void TXASetNC (int channel, int nc);

  public native void TXASetMP (int channel, int mp);

  /**
   * Panadapte & Other Frequency-Domain Displays
   */


  /**
   *  Creating and Destroying a Display
   */

  public native void XCreateAnalyzer(int disp,
                                     int[] success,
                                     int m_size,
                                     int m_LO,
                                     int m_stitch,
                                     String app_data_path
  );

  public native void DestroyAnalyzer(int disp);


  /**
   * Setting Display Parameters
   */

  public native void SetAnalyzer (
    int disp,
    int n_pixout,
    int n_fft,
    int typ,
    int[] flp,
    int sz,
    int bf_sz,
    int win_type,
    double pi,
    int ovrlp,
    int clp,
    int fscLin,
    int fscHin,
    int n_pix,
    int n_stch,
    int calset,
    double fmin,
    double fmax,
    int max_w);


  public native void SetCalibration (int disp, int set_num, int n_points, double cal[]);


  public native void SetDisplayDetectorMode (int disp, int pixout, int mode);

  public native void SetDisplayAverageMode (int disp, int pixout, int mode);

  public native void SetDisplayNumAverage (int disp, int pixout, int num);

  public native void SetDisplayAvBackmult (int disp, int pixout, double mult);

  public native void SetDisplaySampleRate (int disp, int rate);

  public native void SetDisplayNormOneHz (int disp, int pixout, int norm);

  /**
   * Supplying Input Data
   */

  public native void Spectrum2 (int run, int disp, int ss, int LO, double[] pbuff);

  public native void Spectrum0 (int run, int disp, int ss, int LO, double[] pbuff);

  public native void Spectrum (int disp, int ss, int LO, double[] pI, double[] pQ);

  /**
   * Retrieving Pixel Values
   */

  public native void GetPixels (int disp, int pixout, float[] pix, int[] flag);

  /**
   * Preemptive Wideband Noise Blanker
   */

  public native void create_anb (
    int run,
    int buffsize,
    double[] in,
    double[] out,
    double samplerate,
    double tau,
    double hangtime,
    double advtime,
    double backtau,
    double threshold);

  //TODO additonal methods.

  /**
   * Interpolating Wideband Noise Blanker
   */

  public native void create_nob (
    int run,
    int buffsize,
    double[] in,
    double[] out,
    double samplerate,
    int mode,
    double advslewtime,
    double advtime,
    double hangslewtime,
    double hangtime,
    double max_imp_seq_time,
    double backtau,
    double threshold);

  //TODO additonal methods.

  /**
   * Identifier-Based Calls
   */

  public native void create_nobEXT (
    int id,
    int run,
    int mode,
    int buffsize,
    double samplerate,
    double slewtime,
    double hangtime,
    double advtime,
    double backtau,
    double threshold);

  public native void destroy_nobEXT (int id);

  public native void flush_nobEXT (int id);

  public native void xnobEXT (int id, double[] in, double[] out);

  public native void SetEXTNOBRun (int id, int run);

  public native void SetEXTNOBMode (int id, int mode);

  public native void SetEXTNOBSamplerate (int id, int rate);

  public native void SetEXTNOBBuffsize (int id, int size);

  public native void SetEXTNOBTau (int id, double tau);

  public native void SetEXTNOBHangtime (int id, double time);

  public native void SetEXTNOBAdvtime (int id, double time);

  public native void SetEXTNOBBacktau (int id, double tau);

  public native void SetEXTANBNOBThreshold (int id, double thresh);

  /**
   * Resampler
   */



  //TODO there are more methods....


  /**
   * Constants.
   */

  public static final int INACTIVE = 0;
  public static final int ACTIVE = 1;

  public static final int OFF = 0;
  public static final int LONG = 1; // (hangtime = 2000ms, τ_decay = 2000ms)
  public static final int SLOW = 2; // (hangtime = 1000ms, τ_decay = 500ms)
  public static final int MED = 3; //  (No Hang, τ_decay = 250ms)
  public static final int FAST = 4; //  (No Hang, τ_decay = 50ms)
  public static final int CUSTOM = 5; // Settings

  public static final int S_PK = 0;
  public static final int S_AV = 1;
  public static final int ADC_PK = 2;
  public static final int ADC_AV = 3;
  public static final int AGC_GAIN = 4;
  public static final int AGC_PK = 5;
  public static final int AGC_AV = 6;

  public static final int REAL = 0;
  public static final int COMPLEX = 1;

  public static final int RECTANGULAR = 0;
  public static final int BLACKMAN_HARRIS = 1;
  public static final int HANN = 2;
  public static final int FLAT_TOP = 3;
  public static final int HAMMING = 4;
  public static final int KAISER = 5;

  public static final int PEAK_DETECT = -1;
  public static final int NO_AVERAGING = 0;
  public static final int TIME_WEIGHTED_LINEAR = 1;
  public static final int TIME_WEIGHTED_LOG = 2;
  public static final int WINDOW_LINEAR = 3;
  public static final int WINDOW_LOG = 4;
  public static final int WEIGHTED_LINEAR_LOW_NOISE = 5;
  public static final int WEIGHTED_LOG_LOW_NOISE = 6;
}

//End of source.
