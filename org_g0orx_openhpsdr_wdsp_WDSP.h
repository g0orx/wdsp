#ifndef _org_g0orx_openhpsdr_wdsp_WDSP_H
#define _org_g0orx_openhpsdr_wdsp_WDSP_H

#include <jni.h>

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    OpenChannel
 * Signature: (IIIIIIIIDDDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_OpenChannel
  (JNIEnv *env, jobject obj, jint channel, jint in_size, jint dsp_size, jint input_samplerate, jint dsp_rate, jint output_samplerate, jint type, jint state, jdouble tdelayup, jdouble tslewup, jdouble tdelaydown, jdouble tslewdown, jint bfo);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    CloseChannel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_CloseChannel
  (JNIEnv *env, jobject obj, jint channel);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    fexchange0
 * Signature: (I[D[D[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_fexchange0
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray in, jdoubleArray out, jintArray error);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    fexchange2
 * Signature: (I[F[F[F[F[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_fexchange2
  (JNIEnv *env, jobject obj, jint channel, jfloatArray Iin, jfloatArray Qin, jfloatArray Iout, jfloatArray Qout, jintArray error);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetType
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetType
  (JNIEnv *env, jobject obj, jint channel, jint type);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetInputBuffsize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetInputBuffsize
  (JNIEnv *env, jobject obj, jint channel, jint size);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetDSPBuffsize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetDSPBuffsize
  (JNIEnv *env, jobject obj, jint channel, jint size);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetInputSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetInputSamplerate
  (JNIEnv *env, jobject obj, jint channel, jint rate);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetDSPSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetDSPSamplerate
  (JNIEnv *env, jobject obj, jint channel, jint rate);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetOutputSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetOutputSamplerate
  (JNIEnv *env, jobject obj, jint channel, jint rate);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetAllRates
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetAllRates
  (JNIEnv *env, jobject obj, jint channel, jint in_rate, jint dsp_rate, jint out_rate);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelState
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelState
  (JNIEnv *env, jobject obj, jint channel, jint state, jint dmode);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTDelayUp
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTDelayUp
  (JNIEnv *env, jobject obj, jint channel, jdouble delay);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTSlewUp
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTSlewUp
  (JNIEnv *env, jobject obj, jint channel, jdouble delay);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTDelayDown
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTDelayDown
  (JNIEnv *env, jobject obj, jint channel, jdouble delay);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTSlewDown
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTSlewDown
  (JNIEnv *env, jobject obj, jint channel, jdouble slew);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAMode
  (JNIEnv *env, jobject obj, jint channel, jint mode);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAShiftRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAShiftRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAShiftFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAShiftFreq
  (JNIEnv *env, jobject obj, jint channel, jdouble frequency);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXABandpassRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXABandpassRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXABandpassFreqs
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXABandpassFreqs
  (JNIEnv *env, jobject obj, jint channel, jdouble low, jdouble high);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMSQRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMSQThreshold
  (JNIEnv *env, jobject obj, jint channel, jdouble threshold);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMDSBMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMDSBMode
  (JNIEnv *env, jobject obj, jint channel, jint mode);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMDFadeLevel
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMDFadeLevel
  (JNIEnv *env, jobject obj, jint channel, jint level);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAFMDeviation
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAFMDeviation
  (JNIEnv *env, jobject obj, jint channel, jdouble deviation);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAFMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAFMSQRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAFMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAFMSQThreshold
  (JNIEnv *env, jobject obj, jint channel, jdouble threshold);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEQRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEQProfile
 * Signature: (II[D[D)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEQProfile
  (JNIEnv *env, jobject obj, jint channel, jint nfreqs, jdoubleArray F, jdoubleArray G);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAGrphEQ
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAGrphEQ
  (JNIEnv *env, jobject obj, jint channel, jintArray rxeq);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAGrphEQ10
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAGrphEQ10
  (JNIEnv *env, jobject obj, jint channel, jintArray rxeq);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFVals
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFVals
  (JNIEnv *env, jobject obj, jint channel, jint taps, jint delay, jdouble gain, jdouble leakage);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFTaps
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFTaps
  (JNIEnv *env, jobject obj, jint channel, jint taps);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFDelay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFDelay
  (JNIEnv *env, jobject obj, jint channel, jint delay);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFGain
  (JNIEnv *env, jobject obj, jint channel, jdouble gain);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFLeakage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFLeakage
  (JNIEnv *env, jobject obj, jint channel, jdouble leakage);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFPosition
  (JNIEnv *env, jobject obj, jint channel, jint position);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRVals
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRVals
  (JNIEnv *env, jobject obj, jint channel, jint taps, jint delay, jdouble gain, jdouble leakage);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRTaps
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRTaps
  (JNIEnv *env, jobject obj, jint channel, jint taps);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRDelay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRDelay
  (JNIEnv *env, jobject obj, jint channel, jint delay);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRGain
  (JNIEnv *env, jobject obj, jint channel, jdouble gain);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRLeakage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRLeakage
  (JNIEnv *env, jobject obj, jint channel, jdouble leakage);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRPosition
  (JNIEnv *env, jobject obj, jint channel, jint position);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCMode
  (JNIEnv *env, jobject obj, jint channel, jint mode);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCAttack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCAttack
  (JNIEnv *env, jobject obj, jint channel, jint attack);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCDecay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCDecay
  (JNIEnv *env, jobject obj, jint channel, jint decay);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCHang
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCHang
  (JNIEnv *env, jobject obj, jint channel, jint hang);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCHangLevel
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCHangLevel
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray level);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCHangLevel
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCHangLevel
  (JNIEnv *env, jobject obj, jint channel, jdouble level);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCHangThreshold
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCHangThreshold
  (JNIEnv *env, jobject obj, jint channel, jintArray threshold);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCHangThreshold
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCHangThreshold
  (JNIEnv *env, jobject obj, jint channel, jint threshold);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCThresh
 * Signature: (I[DDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCThresh
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray thresh, jdouble size, jdouble rate);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCThresh
 * Signature: (IDDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCThresh
  (JNIEnv *env, jobject obj, jint channel, jdouble thresh, jdouble size, jdouble rate);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCTop
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCTop
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray top);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCTop
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCTop
  (JNIEnv *env, jobject obj, jint channel, jdouble top);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCSlope
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCSlope
  (JNIEnv *env, jobject obj, jint channel, jint slope);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCFixed
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCFixed
  (JNIEnv *env, jobject obj, jint channel, jdouble fixed);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXACBLRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXACBLRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAPanelPan
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAPanelPan
  (JNIEnv *env, jobject obj, jint channel, jdouble pan);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAPanelBinaural
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAPanelBinaural
  (JNIEnv *env, jobject obj, jint channel, jint bin);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAMeter
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAMeter
  (JNIEnv *env, jobject obj, jint channel, jint meter);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    RXAGetaSipF
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_RXAGetaSipF
  (JNIEnv *env, jobject obj, jint channel, jfloatArray out, jint size);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    RXAGetaSipF1
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_RXAGetaSipF1
  (JNIEnv *env, jobject obj, jint channel, jfloatArray out, jint size);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    Spectrum
 * Signature: (III[F[F)V
 */

JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_Spectrum
  (JNIEnv *env, jobject obj, jint channel, jint ss, jint LO, jfloatArray i, jfloatArray q);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    Spectrum2
 * Signature: (III[F)V
 */

JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_Spectrum2
  (JNIEnv *env, jobject obj, jint channel, jint ss, jint LO, jfloatArray buffer);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetTXAMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetTXAMode
  (JNIEnv *env, jobject obj, jint channel, jint mode);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetTXABandpassRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetTXABandpassRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetTXABandpassFreqs
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetTXABandpassFreqs
  (JNIEnv *env, jobject obj, jint channel, jdouble low, jdouble high);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    XCreateAnalyzer
 * Signature: (I[IIIIS)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_XCreateAnalyzer
  (JNIEnv *env, jobject obj, jint disp, jintArray success, jint m_size, jint m_LO, jint m_stitch, jstring app_data_path);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    DestroyAnalyzer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_DestroyAnalyzer
  (JNIEnv *env, jobject obj, jint disp);
        

/*      
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP 
 * Method:    SetAnalyzer
 * Signature: (IIII[IIIIDIIIIIIIIDIDDI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetAnalyzer
  (JNIEnv *env, jobject obj, jint disp, jint n_fft, jint typ, jintArray flp, jint sz, jint bf_sz, jint win_type, jdouble pi, jint ovrlp, jint clp, jint fscLin, jint fscHin, jint n_pix, jint n_stch, jint av_m, jint n_av, jdouble av_b, jint calset, jdouble fmin, jdouble fmax, jint max_w);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetPixels
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetPixels
  (JNIEnv *env, jobject obj, jint disp, jfloatArray pix, jintArray flag);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetNAPixels
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetNAPixels
  (JNIEnv *env, jobject obj, jint disp, jfloatArray pix, jintArray flag);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    WDSPwisdom
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_WDSPwisdom
  (JNIEnv *env, jobject obj, jstring dir);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRgainMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRgainMethod
  (JNIEnv *env, jobject obj, jint channel, jint method);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRnpeMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRnpeMethod
  (JNIEnv *env, jobject obj, jint channel, jint method);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRaeRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRaeRun
  (JNIEnv *env, jobject obj, jint channel, jint run);

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRPosition
  (JNIEnv *env, jobject obj, jint channel, jint position);

#endif
