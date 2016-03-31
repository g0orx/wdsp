#include "org_g0orx_openhpsdr_wdsp_WDSP.h"

#include "comm.h"
#include "meter.h"

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    OpenChannel
 * Signature: (IIIIIIIIDDDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_OpenChannel
  (JNIEnv *env, jobject obj, jint channel, jint in_size, jint dsp_size, jint input_samplerate, jint dsp_rate, jint output_samplerate, jint type, jint state, jdouble tdelayup, jdouble tslewup, jdouble tdelaydown, jdouble tslewdown, jint bfo) {
	OpenChannel(channel,in_size,dsp_size,input_samplerate,dsp_rate,output_samplerate,type,state,tdelayup,tslewup,tdelaydown,tslewdown,bfo);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    CloseChannel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_CloseChannel
  (JNIEnv *env, jobject obj, jint channel) {
	CloseChannel(channel);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    fexchange0
 * Signature: (I[D[D[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_fexchange0
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray in, jdoubleArray out, jintArray error) {
	jdouble *indata=(*env)->GetDoubleArrayElements(env,in,0);
	jdouble *outdata=(*env)->GetDoubleArrayElements(env,out,0);
        jint *err = (*env)->GetIntArrayElements(env, error, 0);
	fexchange0(channel,indata,outdata,err);
	(*env)->ReleaseIntArrayElements(env,error,err,0);
	(*env)->ReleaseDoubleArrayElements(env,out,outdata,0);
	(*env)->ReleaseDoubleArrayElements(env,in,indata,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    fexchange2
 * Signature: (I[F[F[F[F[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_fexchange2
  (JNIEnv *env, jobject obj, jint channel, jfloatArray Iin, jfloatArray Qin, jfloatArray Iout, jfloatArray Qout, jintArray error) {
	jfloat *iin=(*env)->GetFloatArrayElements(env,Iin,0);
	jfloat *qin=(*env)->GetFloatArrayElements(env,Qin,0);
	jfloat *iout=(*env)->GetFloatArrayElements(env,Iout,0);
	jfloat *qout=(*env)->GetFloatArrayElements(env,Qout,0);
        jint *err = (*env)->GetIntArrayElements(env, error, 0);
	fexchange2(channel,iin,qin,iout,qout,err);
	(*env)->ReleaseIntArrayElements(env,error,err,0);
	(*env)->ReleaseFloatArrayElements(env,Qout,qout,0);
	(*env)->ReleaseFloatArrayElements(env,Iout,iout,0);
	(*env)->ReleaseFloatArrayElements(env,Qin,qin,0);
	(*env)->ReleaseFloatArrayElements(env,Iin,iin,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetType
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetType
  (JNIEnv *env, jobject obj, jint channel, jint type) {
	SetType(channel,type);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetInputBuffsize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetInputBuffsize
  (JNIEnv *env, jobject obj, jint channel, jint size) {
	SetInputBuffsize(channel,size);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetDSPBuffsize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetDSPBuffsize
  (JNIEnv *env, jobject obj, jint channel, jint size) {
	SetDSPBuffsize(channel,size);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetInputSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetInputSamplerate
  (JNIEnv *env, jobject obj, jint channel, jint rate) {
	SetInputSamplerate(channel,rate);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetDSPSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetDSPSamplerate
  (JNIEnv *env, jobject obj, jint channel, jint rate) {
	SetDSPSamplerate(channel,rate);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetOutputSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetOutputSamplerate
  (JNIEnv *env, jobject obj, jint channel, jint rate) {
	SetOutputSamplerate(channel,rate);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetAllRates
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetAllRates
  (JNIEnv *env, jobject obj, jint channel, jint in_rate, jint dsp_rate, jint out_rate) {
	SetAllRates(channel,in_rate,dsp_rate,out_rate);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelState
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelState
  (JNIEnv *env, jobject obj, jint channel, jint state, jint dmode) {
	SetChannelState(channel,state,dmode);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTDelayUp
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTDelayUp
  (JNIEnv *env, jobject obj, jint channel, jdouble delay) {
	SetChannelTDelayUp(channel,delay);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTSlewUp
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTSlewUp
  (JNIEnv *env, jobject obj, jint channel, jdouble delay) {
	SetChannelTDelayUp(channel,delay);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTDelayDown
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTDelayDown
  (JNIEnv *env, jobject obj, jint channel, jdouble delay) {
	SetChannelTDelayDown(channel,delay);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetChannelTSlewDown
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetChannelTSlewDown
  (JNIEnv *env, jobject obj, jint channel, jdouble slew) {
	SetChannelTSlewDown(channel,slew);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAMode
  (JNIEnv *env, jobject obj, jint channel, jint mode) {
	SetRXAMode(channel,mode);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAShiftRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAShiftRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXAShiftRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAShiftFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAShiftFreq
  (JNIEnv *env, jobject obj, jint channel, jdouble frequency) {
	SetRXAShiftFreq(channel,frequency);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXABandpassRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXABandpassRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXABandpassRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXABandpassFreqs
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXABandpassFreqs
  (JNIEnv *env, jobject obj, jint channel, jdouble low, jdouble high) {
	SetRXABandpassFreqs(channel,low,high);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMSQRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXAAMSQRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMSQThreshold
  (JNIEnv *env, jobject obj, jint channel, jdouble threshold) {
	SetRXAAMSQThreshold(channel,threshold);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMDSBMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMDSBMode
  (JNIEnv *env, jobject obj, jint channel, jint mode) {
	SetRXAAMDSBMode(channel,mode);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAMDFadeLevel
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAMDFadeLevel
  (JNIEnv *env, jobject obj, jint channel, jint level) {
	SetRXAAMDFadeLevel(channel,level);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAFMDeviation
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAFMDeviation
  (JNIEnv *env, jobject obj, jint channel, jdouble deviation) {
	SetRXAFMDeviation(channel,deviation);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAFMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAFMSQRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXAFMSQRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAFMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAFMSQThreshold
  (JNIEnv *env, jobject obj, jint channel, jdouble threshold) {
	SetRXAFMSQThreshold(channel,threshold);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEQRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXAEQRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEQProfile
 * Signature: (II[D[D)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEQProfile
  (JNIEnv *env, jobject obj, jint channel, jint nfreqs, jdoubleArray F, jdoubleArray G) {
	jdouble *dF=(*env)->GetDoubleArrayElements(env,F,0);
	jdouble *dG=(*env)->GetDoubleArrayElements(env,G,0);
	SetRXAEQProfile(channel,nfreqs,dF,dG);
	(*env)->ReleaseDoubleArrayElements(env,G,dG,0);
	(*env)->ReleaseDoubleArrayElements(env,F,dF,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAGrphEQ
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAGrphEQ
  (JNIEnv *env, jobject obj, jint channel, jintArray rxeq) {
	jint *irxeq=(*env)->GetIntArrayElements(env,rxeq,0);
	SetRXAGrphEQ(channel,irxeq);
	(*env)->ReleaseIntArrayElements(env,rxeq,irxeq,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAGrphEQ10
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAGrphEQ10
  (JNIEnv *env, jobject obj, jint channel, jintArray rxeq) {
	jint *irxeq=(*env)->GetIntArrayElements(env,rxeq,0);
	SetRXAGrphEQ10(channel,irxeq);
	(*env)->ReleaseIntArrayElements(env,rxeq,irxeq,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXAANFRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFVals
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFVals
  (JNIEnv *env, jobject obj, jint channel, jint taps, jint delay, jdouble gain, jdouble leakage) {
	SetRXAANFVals(channel,taps,delay,gain,leakage);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFTaps
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFTaps
  (JNIEnv *env, jobject obj, jint channel, jint taps) {
	SetRXAANFTaps(channel,taps);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFDelay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFDelay
  (JNIEnv *env, jobject obj, jint channel, jint delay) {
	SetRXAANFDelay(channel,delay);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFGain
  (JNIEnv *env, jobject obj, jint channel, jdouble gain) {
	SetRXAANFGain(channel,gain);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFLeakage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFLeakage
  (JNIEnv *env, jobject obj, jint channel, jdouble leakage) {
	SetRXAANFLeakage(channel,leakage);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANFPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANFPosition
  (JNIEnv *env, jobject obj, jint channel, jint position) {
	SetRXAANFPosition(channel,position);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXAANRRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRVals
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRVals
  (JNIEnv *env, jobject obj, jint channel, jint taps, jint delay, jdouble gain, jdouble leakage) {
	SetRXAANRVals(channel,taps,delay,gain,leakage);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRTaps
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRTaps
  (JNIEnv *env, jobject obj, jint channel, jint taps) {
	SetRXAANRTaps(channel,taps);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRDelay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRDelay
  (JNIEnv *env, jobject obj, jint channel, jint delay) {
	SetRXAANRDelay(channel,delay);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRGain
  (JNIEnv *env, jobject obj, jint channel, jdouble gain) {
	SetRXAANRGain(channel,gain);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRLeakage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRLeakage
  (JNIEnv *env, jobject obj, jint channel, jdouble leakage) {
	SetRXAANRLeakage(channel,leakage);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAANRPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAANRPosition
  (JNIEnv *env, jobject obj, jint channel, jint position) {
	SetRXAANRPosition(channel,position);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCMode
  (JNIEnv *env, jobject obj, jint channel, jint mode) {
    SetRXAAGCMode(channel,mode);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCAttack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCAttack
  (JNIEnv *env, jobject obj, jint channel, jint attack) {
	SetRXAAGCAttack(channel,attack);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCDecay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCDecay
  (JNIEnv *env, jobject obj, jint channel, jint decay) {
	SetRXAAGCDecay(channel,decay);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCHang
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCHang
  (JNIEnv *env, jobject obj, jint channel, jint hang) {
	SetRXAAGCHang(channel,hang);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCHangLevel
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCHangLevel
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray level) {
	jdouble *dlevel=(*env)->GetDoubleArrayElements(env,level,0);
	GetRXAAGCHangLevel(channel,dlevel);
	(*env)->ReleaseDoubleArrayElements(env,level,dlevel,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCHangLevel
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCHangLevel
  (JNIEnv *env, jobject obj, jint channel, jdouble level) {
	SetRXAAGCHangLevel(channel,level);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCHangThreshold
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCHangThreshold
  (JNIEnv *env, jobject obj, jint channel, jintArray threshold) {
	jint *ithreshold=(*env)->GetIntArrayElements(env,threshold,0);
	GetRXAAGCHangThreshold(channel,ithreshold);
	(*env)->ReleaseIntArrayElements(env,threshold,ithreshold,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCHangThreshold
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCHangThreshold
  (JNIEnv *env, jobject obj, jint channel, jint threshold) {
	SetRXAAGCHangThreshold(channel,threshold);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCThresh
 * Signature: (I[DDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCThresh
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray thresh, jdouble size, jdouble rate) {
	jdouble *dthresh=(*env)->GetDoubleArrayElements(env,thresh,0);
	GetRXAAGCThresh(channel,dthresh,size,rate);
	(*env)->ReleaseDoubleArrayElements(env,thresh,dthresh,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCThresh
 * Signature: (IDDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCThresh
  (JNIEnv *env, jobject obj, jint channel, jdouble thresh, jdouble size, jdouble rate) {
	SetRXAAGCThresh(channel,thresh,size,rate);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAAGCTop
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAAGCTop
  (JNIEnv *env, jobject obj, jint channel, jdoubleArray top) {
	jdouble *dtop=(*env)->GetDoubleArrayElements(env,top,0);
	GetRXAAGCTop(channel,dtop);
	(*env)->ReleaseDoubleArrayElements(env,top,dtop,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCTop
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCTop
  (JNIEnv *env, jobject obj, jint channel, jdouble top) {
	SetRXAAGCTop(channel,top);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCSlope
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCSlope
  (JNIEnv *env, jobject obj, jint channel, jint slope) {
	SetRXAAGCSlope(channel,slope);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAAGCFixed
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAAGCFixed
  (JNIEnv *env, jobject obj, jint channel, jdouble fixed) {
	SetRXAAGCFixed(channel,fixed);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXACBLRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXACBLRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetRXACBLRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAPanelPan
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAPanelPan
  (JNIEnv *env, jobject obj, jint channel, jdouble pan) {
	SetRXAPanelPan(channel,pan);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAPanelBinaural
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAPanelBinaural
  (JNIEnv *env, jobject obj, jint channel, jint bin) {
	SetRXAPanelBinaural(channel,bin);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetRXAMeter
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetRXAMeter
  (JNIEnv *env, jobject obj, jint channel, jint meter) {
	return GetRXAMeter(channel,meter);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    RXAGetaSipF
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_RXAGetaSipF
  (JNIEnv *env, jobject obj, jint channel, jfloatArray out, jint size) {
	jfloat *fout=(*env)->GetFloatArrayElements(env,out,0);
	RXAGetaSipF(channel,fout,size);
	(*env)->ReleaseFloatArrayElements(env,out,fout,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    RXAGetaSipF1
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_RXAGetaSipF1
  (JNIEnv *env, jobject obj, jint channel, jfloatArray out, jint size) {
	jfloat *fout=(*env)->GetFloatArrayElements(env,out,0);
	RXAGetaSipF1(channel,fout,size);
	(*env)->ReleaseFloatArrayElements(env,out,fout,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    Spectrum
 * Signature: (III[F[F)V
 */

JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_Spectrum
  (JNIEnv *env, jobject obj, jint channel, jint ss, jint LO, jfloatArray i, jfloatArray q) {
	jfloat *fi=(*env)->GetFloatArrayElements(env,i,0);
	jfloat *fq=(*env)->GetFloatArrayElements(env,q,0);
	Spectrum(channel,ss,LO,fi,fq);
	(*env)->ReleaseFloatArrayElements(env,q,fq,0);
	(*env)->ReleaseFloatArrayElements(env,i,fi,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    Spectrum2
 * Signature: (III[F)V
 */

JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_Spectrum2
  (JNIEnv *env, jobject obj, jint channel, jint ss, jint LO, jfloatArray buffer) {
	jfloat *fbuffer=(*env)->GetFloatArrayElements(env,buffer,0);
	Spectrum2(channel,ss,LO,fbuffer);
	(*env)->ReleaseFloatArrayElements(env,buffer,fbuffer,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetTXAMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetTXAMode
  (JNIEnv *env, jobject obj, jint channel, jint mode) {
	SetTXAMode(channel,mode);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetTXABandpassRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetTXABandpassRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
	SetTXABandpassRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetTXABandpassFreqs
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetTXABandpassFreqs
  (JNIEnv *env, jobject obj, jint channel, jdouble low, jdouble high) {
	SetTXABandpassFreqs(channel,low,high);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    XCreateAnalyzer
 * Signature: (I[IIIIS)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_XCreateAnalyzer
  (JNIEnv *env, jobject obj, jint disp, jintArray success, jint m_size, jint m_LO, jint m_stitch, jstring app_data_path) {
	jint *successptr = (*env)->GetIntArrayElements(env, success, 0);
	const char *app_data_path_ptr = (*env)->GetStringUTFChars(env, app_data_path, NULL);
	XCreateAnalyzer(disp, successptr, m_size, m_LO, m_stitch, app_data_path_ptr);
	(*env)->ReleaseStringUTFChars(env, app_data_path, app_data_path_ptr); 
	(*env)->ReleaseIntArrayElements(env,success,successptr,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    DestroyAnalyzer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_DestroyAnalyzer
  (JNIEnv *env, jobject obj, jint disp) {
	DestroyAnalyzer(disp);
}
        

/*      
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP 
 * Method:    SetAnalyzer
 * Signature: (IIII[IIIIDIIIIIIIIDIDDI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetAnalyzer
  (JNIEnv *env, jobject obj, jint disp, jint n_fft, jint typ, jintArray flp, jint sz, jint bf_sz, jint win_type, jdouble pi, jint ovrlp, jint clp, jint fscLin, jint fscHin, jint n_pix, jint n_stch, jint av_m, jint n_av, jdouble av_b, jint calset, jdouble fmin, jdouble fmax, jint max_w) {
	jint *flpptr = (*env)->GetIntArrayElements(env, flp, 0);
	SetAnalyzer(disp, n_fft, typ, flpptr, sz, bf_sz, win_type, pi, ovrlp, clp, fscLin, fscHin, n_pix, n_stch, av_m, n_av, av_b, calset, fmin, fmax, max_w);
	(*env)->ReleaseIntArrayElements(env,flp,flpptr,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetPixels
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetPixels
  (JNIEnv *env, jobject obj, jint disp, jfloatArray pix, jintArray flag) {
	jfloat *pixptr = (*env)->GetFloatArrayElements(env, pix, 0);
	jint *flagptr = (*env)->GetIntArrayElements(env, flag, 0);
	GetPixels(disp,pixptr,flagptr);
	(*env)->ReleaseIntArrayElements(env,flag,flagptr,0);
	(*env)->ReleaseFloatArrayElements(env,pix,pixptr,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    GetNAPixels
 * Signature: (I[FI)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_GetNAPixels
  (JNIEnv *env, jobject obj, jint disp, jfloatArray pix, jintArray flag) {
	jfloat *pixptr = (*env)->GetFloatArrayElements(env, pix, 0);
	jint *flagptr = (*env)->GetIntArrayElements(env, flag, 0);
	GetNAPixels(disp,pixptr,flagptr);
	(*env)->ReleaseIntArrayElements(env,flag,flagptr,0);
	(*env)->ReleaseFloatArrayElements(env,pix,pixptr,0);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    WDSPwisdom
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_WDSPwisdom
  (JNIEnv *env, jobject obj, jstring dir) {
	const char *dir_ptr = (*env)->GetStringUTFChars(env, dir, NULL);
	WDSPwisdom(dir_ptr,env,obj);
	(*env)->ReleaseStringUTFChars(env, dir, dir_ptr); 
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
        SetRXAEMNRRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRgainMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRgainMethod
  (JNIEnv *env, jobject obj, jint channel, jint method) {
        SetRXAEMNRgainMethod(channel,method);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRnpeMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRnpeMethod
  (JNIEnv *env, jobject obj, jint channel, jint method) {
        SetRXAEMNRnpeMethod(channel,method);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRaeRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRaeRun
  (JNIEnv *env, jobject obj, jint channel, jint run) {
        SetRXAEMNRaeRun(channel,run);
}

/*
 * Class:     org_g0orx_openhpsdr_wdsp_WDSP
 * Method:    SetRXAEMNRPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_g0orx_openhpsdr_wdsp_WDSP_SetRXAEMNRPosition
  (JNIEnv *env, jobject obj, jint channel, jint position) {
        SetRXAEMNRPosition(channel,position);
}
