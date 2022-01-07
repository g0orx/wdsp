#include "org_openhpsdr_dsp_Wdsp.h"

#include "comm.h"
#include "meter.h"

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetWDSPVersion
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_openhpsdr_dsp_Wdsp_GetWDSPVersion
(JNIEnv* env, jobject obj) {

	return GetWDSPVersion();
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    WDSPwisdom
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_WDSPwisdom
  (JNIEnv * env, jobject obj, jstring dir) {
	const char* dir_ptr = (*env)->GetStringUTFChars(env, dir, NULL);
	
	WDSPwisdom(dir_ptr, env, obj);
	
	(*env)->ReleaseStringUTFChars(env, dir, dir_ptr);
}
  

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    OpenChannel
 * Signature: (IIIIIIIIDDDDI)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_OpenChannel
(JNIEnv * env, jobject obj, jint channel, jint in_size, jint dsp_size, jint input_samplerate, jint dsp_rate, jint output_samplerate, jint type, jint state, jdouble tdelayup, jdouble tslewup, jdouble tdelaydown, jdouble tslewdown, jint bfo) {
	
	OpenChannel(channel, in_size, dsp_size, input_samplerate, dsp_rate, output_samplerate, type, state, tdelayup, tslewup, tdelaydown, tslewdown, bfo);
}


/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    CloseChannel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_CloseChannel
(JNIEnv* env, jobject obj, jint channel) {
	
	CloseChannel(channel);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetChannelState
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetChannelState
  (JNIEnv* env, jobject obj, jint channel, jint state, jint dmode) {
	
	SetChannelState(channel, state, dmode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    fexchange0
 * Signature: (I[D[D[I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_fexchange0
  (JNIEnv* env, jobject obj, jint channel, jdoubleArray in, jdoubleArray out, jintArray error) {
	
	jdouble* indata = (*env)->GetDoubleArrayElements(env, in, 0);
	jdouble* outdata = (*env)->GetDoubleArrayElements(env, out, 0);
	jint* err = (*env)->GetIntArrayElements(env, error, 0);

	fexchange0(channel, indata, outdata, err);

	(*env)->ReleaseIntArrayElements(env, error, err, 0);
	(*env)->ReleaseDoubleArrayElements(env, out, outdata, 0);
	(*env)->ReleaseDoubleArrayElements(env, in, indata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    fexchange2
 * Signature: (I[F[F[F[F[I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_fexchange2
  (JNIEnv* env, jobject obj, jint channel, jfloatArray Iin, jfloatArray Qin, jfloatArray Iout, jfloatArray Qout, jintArray error) {
	jfloat* iin = (*env)->GetFloatArrayElements(env, Iin, 0);
	jfloat* qin = (*env)->GetFloatArrayElements(env, Qin, 0);
	jfloat* iout = (*env)->GetFloatArrayElements(env, Iout, 0);
	jfloat* qout = (*env)->GetFloatArrayElements(env, Qout, 0);
	jint* err = (*env)->GetIntArrayElements(env, error, 0);

	fexchange2(channel, iin, qin, iout, qout, err);

	(*env)->ReleaseIntArrayElements(env, error, err, 0);
	(*env)->ReleaseFloatArrayElements(env, Qout, qout, 0);
	(*env)->ReleaseFloatArrayElements(env, Iout, iout, 0);
	(*env)->ReleaseFloatArrayElements(env, Qin, qin, 0);
	(*env)->ReleaseFloatArrayElements(env, Iin, iin, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCMaxInputLevel
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCMaxInputLevel
  (JNIEnv* env, jobject obj, jint channel, jdouble level) {

	SetRXAAGCMaxInputLevel(channel, level);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAShiftRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAShiftRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {

	SetRXAShiftRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAShiftFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAShiftFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble frequency) {

	SetRXAShiftFreq(channel, frequency);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {
	
	SetRXAPreGenRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenMode
  (JNIEnv* env, jobject obj, jint channel, jint mode) {

	SetRXAPreGenMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenToneMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenToneMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag) {

	SetRXAPreGenToneMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenToneFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenToneFreq
(JNIEnv* env, jobject obj, jint channel, jdouble freq) {

	SetRXAPreGenToneFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenNoiseMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenNoiseMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag) {
	
	SetRXAPreGenNoiseMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenSweepMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenSweepMag
(JNIEnv* env, jobject obj, jint channel, jdouble mag) {

	SetRXAPreGenSweepMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenSweepFreq
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenSweepFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq1, jdouble freq2) {

	SetRXAPreGenSweepFreq(channel, freq1, freq2);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPreGenSweepRate
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPreGenSweepRate
  (JNIEnv* env, jobject obj, jint channel, jdouble rate) {

	SetRXAPreGenSweepRate(channel, rate);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetRXAMeter
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL Java_org_openhpsdr_dsp_Wdsp_GetRXAMeter
 (JNIEnv* env, jobject obj, jint channel, jint meter) {

	return GetRXAMeter(channel, meter);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPSetRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPSetRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {

	RXANBPSetRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPSetWindow
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPSetWindow
  (JNIEnv* env, jobject obj, jint channel, jint wintype) {

	RXANBPSetWindow(channel, wintype);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPSetNotchesRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPSetNotchesRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {

	RXANBPSetNotchesRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPGetMinNotchWidth
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPGetMinNotchWidth
  (JNIEnv* env, jobject obj, jint channel, jdouble minwidth) {

	RXANBPGetMinNotchWidth(channel, minwidth);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPSetAutoIncrease
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPSetAutoIncrease
  (JNIEnv* env, jobject obj, jint channel, jint autoincr) {

	RXANBPSetAutoIncrease(channel, autoincr);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPSetTuneFrequency
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPSetTuneFrequency
(JNIEnv* env, jobject obj, jint channel, jdouble tunefreq) {

	RXANBPSetTuneFrequency(channel, tunefreq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPSetShiftFrequency
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPSetShiftFrequency
(JNIEnv* env, jobject obj, jint channel, jdouble shift) {

	RXANBPSetShiftFrequency(channel, shift);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPGetNumNotches
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPGetNumNotches
(JNIEnv* env, jobject obj, jint channel, jint nnotches) {

	RXANBPGetNumNotches(channel, nnotches);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPAddNotch
 * Signature: (IIDDI)I
 */
JNIEXPORT jint JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPAddNotch
  (JNIEnv* env, jobject obj, jint channel, jint notch, jdouble fcenter, jdouble fwidth, jint active){
	
	return RXANBPAddNotch(channel, notch, fcenter, fwidth, active);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPGetNotch
 * Signature: (IIDDI)I
 */
JNIEXPORT jint JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPGetNotch
  (JNIEnv* env, jobject obj, jint channel, jint notch, jdouble fcenter, jdouble fwidth, jint active){

	return RXANBPGetNotch(channel, notch, fcenter, fwidth, active);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPDeleteNotch
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPDeleteNotch
  (JNIEnv* env, jobject obj, jint channel, jint notch){

	return RXANBPDeleteNotch(channel, notch);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXANBPEditNotch
 * Signature: (IIDDI)I
 */
JNIEXPORT jint JNICALL Java_org_openhpsdr_dsp_Wdsp_RXANBPEditNotch
  (JNIEnv* env, jobject obj, jint channel, jint notch, jdouble fcenter, jdouble fwidth, jint active) {
	
	return RXANBPEditNotch(channel, notch, fcenter, fwidth, active);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXASpectrum
 * Signature: (IIIII)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXASpectrum
  (JNIEnv* env, jobject obj, jint channel, jint flag, jint disp, jint ss, jint LO) {
	
	SetRXASpectrum(channel, flag, disp, ss, LO);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAMSQRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXAAMSQRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXAAMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXAAMSQThreshold
  (JNIEnv* env, jobject obj, jint channel, jdouble threshold) {

	SetRXAAMSQThreshold(channel, threshold);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAMSQMaxTail
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAMSQMaxTail
  (JNIEnv* env, jobject obj, jint channel, jdouble tail){

	SetRXAAMSQMaxTail(channel, tail);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAMDSBMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAMDSBMode
  (JNIEnv* env, jobject obj, jint channel, jint sbmode){

	SetRXAAMDSBMode(channel, sbmode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAMDFadeLevel
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAMDFadeLevel
  (JNIEnv* env, jobject obj, jint channel, jint fadelevel){

	SetRXAAMDFadeLevel(channel, fadelevel);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAFMDeviation
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAFMDeviation
  (JNIEnv* env, jobject obj, jint channel, jdouble deviation){

	SetRXAFMDeviation(channel, deviation);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXACTCSSRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXACTCSSRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXACTCSSRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXACTCSSFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXACTCSSFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetRXACTCSSFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAFMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAFMSQRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXAFMSQRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAFMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAFMSQThreshold
  (JNIEnv* env, jobject obj, jint channel, jdouble threshold){

	SetRXAFMSQThreshold(channel, threshold);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXASNBARun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXASNBARun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXASNBARun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEQRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXAEQRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEQWinType
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEQWinType
  (JNIEnv* env, jobject obj, jint channel, jint winType){

	SetRXAEQWintype(channel, winType);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEQCtfmode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEQCtfmode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetRXAEQCtfmode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEQProfile
 * Signature: (IIDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEQProfile
  (JNIEnv* env, jobject obj, jint channel, jint nfreqs, jdouble freq, jdouble gain){
	
	SetRXAEQProfile(channel, nfreqs, freq, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCMode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetRXAAGCMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCAttack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCAttack
  (JNIEnv* env, jobject obj, jint channel, jint attack){

	SetRXAAGCAttack(channel, attack);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCDecay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCDecay
  (JNIEnv* env, jobject obj, jint channel, jint decay){

	SetRXAAGCDecay(channel, decay);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCHang
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCHang
  (JNIEnv* env, jobject obj, jint channel, jint hang){

	SetRXAAGCHang(channel, hang);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetRXAAGCHangLevel
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_GetRXAAGCHangLevel
  (JNIEnv* env, jobject obj, jint channel, jdoubleArray level){

	jdouble* leveldata = (*env)->GetDoubleArrayElements(env, level, 0);

	GetRXAAGCHangLevel(channel, leveldata);

	(*env)->ReleaseDoubleArrayElements(env, level, leveldata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCHangLevel
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCHangLevel
  (JNIEnv* env, jobject obj, jint channel, jdouble level){

	SetRXAAGCHangLevel(channel, level);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetRXAAGCHangThreshold
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_GetRXAAGCHangThreshold
  (JNIEnv* env, jobject obj, jint channel, jint threshold){

	GetRXAAGCHangThreshold(channel, threshold);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCHangThreshold
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCHangThreshold
  (JNIEnv* env, jobject obj, jint channel, jint threshold){

	SetRXAAGCHangThreshold(channel, threshold);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetRXAAGCThresh
 * Signature: (IDDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_GetRXAAGCThresh
  (JNIEnv* env, jobject obj, jint channel, jdoubleArray thresh, jdouble size, jdouble rate){

		jdouble* threshdata = (*env)->GetDoubleArrayElements(env, thresh, 0);

		GetRXAAGCThresh(channel, threshdata, size, rate);

		(*env)->ReleaseDoubleArrayElements(env, thresh, threshdata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCThresh
 * Signature: (IDDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCThresh
  (JNIEnv* env, jobject obj, jint channel, jdouble thresh, jdouble size, jdouble rate){

	SetRXAAGCThresh(channel, thresh, size, rate);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetRXAAGCTop
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_GetRXAAGCTop
  (JNIEnv* env, jobject obj, jint channel, jdoubleArray max_agc){

	jdouble* max_agc_data = (*env)->GetDoubleArrayElements(env, max_agc, 0);

	GetRXAAGCTop(channel, max_agc_data);

	(*env)->ReleaseDoubleArrayElements(env, max_agc, max_agc_data, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCTop
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCTop
  (JNIEnv* env, jobject obj, jint channel, jdouble  max_agc){

	SetRXAAGCTop(channel, max_agc);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCSlope
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCSlope
  (JNIEnv* env, jobject obj, jint channel, jint slope){

	SetRXAAGCSlope(channel, slope);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAAGCFixed
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAAGCFixed
  (JNIEnv* env, jobject obj, jint channel, jdouble fixed){

	SetRXAAGCFixed(channel, fixed);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXAANFRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFTaps
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFTaps
  (JNIEnv* env, jobject obj, jint channel, jint taps){

	SetRXAANFTaps(channel, taps);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFDelay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFDelay
  (JNIEnv* env, jobject obj, jint channel, jint delay){

	SetRXAANFDelay(channel, delay);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFGain
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){
	
	SetRXAANFGain(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFLeakage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFLeakage
  (JNIEnv* env, jobject obj, jint channel, jdouble leakage){

	SetRXAANFLeakage(channel, leakage);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFVals
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFVals
  (JNIEnv* env, jobject obj, jint channel, jint taps, jint delay, jdouble gain, jdouble leakage) {
	
	SetRXAANFVals(channel, taps, delay, gain, leakage);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANFPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANFPosition
  (JNIEnv* env, jobject obj, jint channel, jint position) {
	
	SetRXAANFPosition(channel, position);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANRRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {
	
	SetRXAANRRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANRTaps
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANRTaps
  (JNIEnv* env, jobject obj, jint channel, jint taps) {
	
	SetRXAANRTaps(channel, taps);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANRDelay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANRDelay
  (JNIEnv* env, jobject obj, jint channel, jint delay) {
	
	SetRXAANRDelay(channel, delay);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANRGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANRGain
  (JNIEnv* env, jobject obj, jint channel, jdouble gain) {
	
	SetRXAANRGain(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANRLeakage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANRLeakage
  (JNIEnv* env, jobject obj, jint channel, jdouble leakage) {
	
	SetRXAANRLeakage(channel, leakage);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAANRVals
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAANRVals
  (JNIEnv* env, jobject obj, jint channel, jint taps, jint delay, jdouble gain, jdouble leakage) {
	
	SetRXAANRVals(channel, taps, delay, gain, leakage);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEMNRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEMNRRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {
	
	SetRXAEMNRRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEMNRgainMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEMNRgainMethod
 (JNIEnv* env, jobject obj, jint channel, jint method) {
	
	SetRXAEMNRgainMethod(channel, method);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEMNRnpeMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEMNRnpeMethod
  (JNIEnv* env, jobject obj, jint channel, jint method) {
	
	SetRXAEMNRnpeMethod(channel, method);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEMNRaeRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEMNRaeRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {
	
	SetRXAEMNRaeRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAEMNRPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAEMNRPosition
  (JNIEnv* env, jobject obj, jint channel, jint position) {
	
	SetRXAEMNRPosition(channel, position);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXABandpassWindow
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXABandpassWindow
  (JNIEnv* env, jobject obj, jint channel, jint windowtype){

	SetRXABandpassWindow(channel, windowtype);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXAGetaSipF
 * Signature: (IFI)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXAGetaSipF
  (JNIEnv* env, jobject obj, jint channel, jfloatArray out, jint size) {
	
	jfloat* fout = (*env)->GetFloatArrayElements(env, out, 0);
	
	RXAGetaSipF(channel, fout, size);
	 
	(*env)->ReleaseFloatArrayElements(env, out, fout, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXAGetaSipF1
 * Signature: (IFI)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXAGetaSipF1
  (JNIEnv* env, jobject obj, jint channel, jfloatArray out, jint size) {
	
	jfloat* fout = (*env)->GetFloatArrayElements(env, out, 0);
	
	RXAGetaSipF1(channel, fout, size);
	
	(*env)->ReleaseFloatArrayElements(env, out, fout, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXACBLRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXACBLRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {
	
	SetRXACBLRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXASPCWRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXASPCWRun
  (JNIEnv* env, jobject obj, jint channel, jint run) {

	SetRXASPCWRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXASPCWFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXASPCWFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetRXASPCWFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXASPCWBandwidth
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXASPCWBandwidth
  (JNIEnv* env, jobject obj, jint channel, jdouble bw){

	SetRXASPCWBandwidth(channel, bw);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXASPCWGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXASPCWGain
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){

	SetRXASPCWGain(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAmpeakRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAmpeakRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXAmpeakRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAmpeakNpeaks
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAmpeakNpeaks
  (JNIEnv* env, jobject obj, jint channel, jint npeaks){

	SetRXAmpeakNpeaks(channel, npeaks);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAmpeakFilEnable
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAmpeakFilEnable
  (JNIEnv* env, jobject obj, jint channel, jint filId, jint enable){

	SetRXAmpeakFilEnable(channel, filId, enable);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAmpeakFilFreq
 * Signature: (IID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAmpeakFilFreq
  (JNIEnv* env, jobject obj, jint channel, jint filId, jdouble freq){

	SetRXAmpeakFilFreq(channel, filId, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAmpeakFilBw
 * Signature: (IID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAmpeakFilBw
  (JNIEnv* env, jobject obj, jint channel, jint filid, jdouble bw){

	SetRXAmpeakFilBw(channel, filid, bw);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAmpeakFilGain
 * Signature: (IID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAmpeakFilGain
  (JNIEnv* env, jobject obj, jint channel, jint filId, jdouble gain){

	SetRXAmpeakFilGain(channel, filId, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetRXAPanelRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelSelect
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelSelect
  (JNIEnv* env, jobject obj, jint channel, jint select){

	SetRXAPanelSelect(channel, select);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelGain1
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelGain1
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){

	SetRXAPanelGain1(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelGain2
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelGain2
  (JNIEnv* env, jobject obj, jint channel, jdouble gainI, jdouble gainQ){

	SetRXAPanelGain2(channel, gainI, gainQ);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelPan
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelPan
(JNIEnv* env, jobject obj, jint channel, jdouble pan) {
	
	SetRXAPanelPan(channel, pan);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelCopy
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelCopy
  (JNIEnv* env, jobject obj, jint channel, jint copy){

	SetRXAPanelCopy(channel, copy);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAPanelBinaural
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAPanelBinaural
  (JNIEnv* env, jobject obj, jint channel, jint bin) {
	
	SetRXAPanelBinaural(channel, bin);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetRXAMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetRXAMode
  (JNIEnv* env, jobject obj, jint channel, jint mode) {
	
	SetRXAMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXASetPassband
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXASetPassband
  (JNIEnv* env, jobject obj, jint channel, jdouble f_low, jdouble f_high){

	RXASetPassband(channel, f_low, f_high);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXASetNC
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXASetNC
  (JNIEnv* env, jobject obj, jint channel, jint nc){

	RXASetNC(channel, nc);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    RXASetMP
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_RXASetMP
  (JNIEnv* env, jobject obj, jint channel, jint mp){

	RXASetMP(channel, mp);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAPreGenRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenMode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetTXAPreGenMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenToneMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenToneMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPreGenToneMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenToneFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenToneFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXAPreGenToneFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenNoiseMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenNoiseMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPreGenNoiseMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenSweepMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenSweepMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPreGenSweepMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenSweepFreq
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenSweepFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq1, jdouble freq2){

	SetTXAPreGenSweepFreq(channel, freq1, freq2);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenSweepRate
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenSweepRate
  (JNIEnv* env, jobject obj, jint channel, jdouble rate){

	SetTXAPreGenSweepRate(channel, rate);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenSawtoothMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenSawtoothMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPreGenSawtoothMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenSawtoothFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenSawtoothFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXAPreGenSawtoothFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenTriangleMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenTriangleMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPreGenTriangleMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenTriangleFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenTriangleFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXAPreGenTriangleFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenPulseMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenPulseMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPreGenPulseMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenPulseFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenPulseFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXAPreGenPulseFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenPulseDutyCycle
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenPulseDutyCycle
  (JNIEnv* env, jobject obj, jint channel, jdouble cycle){

	SetTXAPreGenPulseDutyCycle(channel, cycle);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenPulseToneFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenPulseToneFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXAPreGenPulseToneFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPreGenPulseTransition
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPreGenPulseTransition
  (JNIEnv* env, jobject obj, jint channel, jdouble trans){

	SetTXAPreGenPulseTransition(channel, trans);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAPostGenRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenMode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetTXAPostGenMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenToneMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenToneMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPostGenToneMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenToneFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenToneFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXAPostGenToneFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenTTMag
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenTTMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag1, jdouble mag2){

	SetTXAPostGenTTMag(channel, mag1, mag2);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenTTFreq
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenTTFreq
(JNIEnv* env, jobject obj, jint channel, jdouble freq1, jdouble freq2) {

	SetTXAPostGenTTFreq(channel, freq1, freq2);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenSweepMag
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenSweepMag
  (JNIEnv* env, jobject obj, jint channel, jdouble mag){

	SetTXAPostGenSweepMag(channel, mag);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenSweepFreq
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenSweepFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq1, jdouble freq2){

	SetTXAPostGenSweepFreq(channel, freq1, freq2);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPostGenSweepRate
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPostGenSweepRate
  (JNIEnv* env, jobject obj, jint channel, jdouble rate){

	SetTXAPostGenSweepRate(channel, rate);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPanelRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPanelRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAPanelRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPanelSelect
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPanelSelect
  (JNIEnv* env, jobject obj, jint channel, jint select){

	SetTXAPanelSelect(channel, select);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPanelGain1
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPanelGain1
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){

	SetTXAPanelGain1(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAAMSQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAAMSQRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAAMSQRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAAMSQMutedGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAAMSQMutedGain
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){

	SetTXAAMSQMutedGain(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAAMSQThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAAMSQThreshold
  (JNIEnv* env, jobject obj, jint channel, jdouble threshold){

	SetTXAAMSQThreshold(channel, threshold);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAEQRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAEQRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAEQRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAEQWintype
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAEQWintype
  (JNIEnv* env, jobject obj, jint channel, jint wintype){

	SetTXAEQWintype(channel, wintype);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAEQCtfmode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAEQCtfmode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetTXAEQCtfmode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAEQProfile
 * Signature: (IIDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAEQProfile
  (JNIEnv* env, jobject obj, jint channel, jint nfreqs, jdouble freq, jdouble gain){

	SetTXAEQProfile(channel, nfreqs, freq, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAFMEmphPosition
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAFMEmphPosition
  (JNIEnv* env, jobject obj, jint channel, jint position){

	SetTXAFMEmphPosition(channel, position);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXALevelerSt
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXALevelerSt
  (JNIEnv* env, jobject obj, jint channel, jint state){

	SetTXALevelerSt(channel, state);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXALevelerAttack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXALevelerAttack
  (JNIEnv* env, jobject obj, jint channel, jint attack){

	SetTXALevelerAttack(channel, attack);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXALevelerDecay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXALevelerDecay
  (JNIEnv* env, jobject obj, jint channel, jint decay){

	SetTXALevelerDecay(channel, decay);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXALevelerTop
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXALevelerTop
  (JNIEnv* env, jobject obj, jint channel, jdouble top){

	SetTXALevelerTop(channel, top);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPHROTRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPHROTRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAPHROTRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPHROTCorner
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPHROTCorner
  (JNIEnv* env, jobject obj, jint channel, jdouble corner){

	SetTXAPHROTCorner(channel, corner);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAPHROTNstages
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAPHROTNstages
  (JNIEnv* env, jobject obj, jint channel, jint stages){

	SetTXAPHROTNstages(channel, stages);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACFCOMPRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACFCOMPRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXACFCOMPRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACFCOMPprofile
 * Signature: (IIDDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACFCOMPprofile
  (JNIEnv* env, jobject obj, jint channel, jint nfreqs, jdouble freq, jdouble compression, jdouble equalizergain){

	SetTXACFCOMPprofile(channel, nfreqs, freq, compression, equalizergain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACFCOMPPrecomp
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACFCOMPPrecomp
  (JNIEnv* env, jobject obj, jint channel, jdouble comp){

	SetTXACFCOMPPrecomp(channel, comp);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACFCOMPPeqRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACFCOMPPeqRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXACFCOMPPeqRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACFCOMPPrePeq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACFCOMPPrePeq
  (JNIEnv* env, jobject obj, jint channel, jdouble prepeq){

	SetTXACFCOMPPrePeq(channel, prepeq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXABandpassFreqs
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXABandpassFreqs
  (JNIEnv* env, jobject obj, jint channel, jdouble f_low, jdouble f_high){

	SetTXABandpassFreqs(channel, f_low, f_high);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXABandpassWindow
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXABandpassWindow
  (JNIEnv* env, jobject obj, jint channel, jint window){

	SetTXABandpassWindow(channel, window);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACompressorRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACompressorRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXACompressorRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACompressorGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACompressorGain
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){

	SetTXACompressorGain(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAosctrlRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAosctrlRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXAosctrlRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAALCSt
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAALCSt
  (JNIEnv* env, jobject obj, jint channel, jint state){

	SetTXAALCSt(channel, state);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAALCAttack
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAALCAttack
  (JNIEnv* env, jobject obj, jint channel, jint attack){

	SetTXAALCAttack(channel, attack);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAALCDecay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAALCDecay
  (JNIEnv* env, jobject obj, jint channel, jint decay){

	SetTXAALCDecay(channel, decay);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAALCMaxGain
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAALCMaxGain
  (JNIEnv* env, jobject obj, jint channel, jdouble gain){

	SetTXAALCMaxGain(channel, gain);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAAMCarrierLevel
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAAMCarrierLevel
  (JNIEnv* env, jobject obj, jint channel, jdouble level){

	SetTXAAMCarrierLevel(channel, level);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAFMDeviation
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAFMDeviation
  (JNIEnv* env, jobject obj, jint channel, jdouble deviation){

	SetTXAFMDeviation(channel, deviation);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACTCSSRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACTCSSRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXACTCSSRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACTCSSFreq
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACTCSSFreq
  (JNIEnv* env, jobject obj, jint channel, jdouble freq){

	SetTXACTCSSFreq(channel, freq);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXASetSipMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXASetSipMode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	TXASetSipMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXASetSipDisplay
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXASetSipDisplay
  (JNIEnv* env, jobject obj, jint channel, jint display){

	TXASetSipDisplay(channel, display);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXAGetaSipF
 * Signature: (IFI)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXAGetaSipF
  (JNIEnv* env, jobject obj, jint channel, jfloatArray out , jint size){

	jfloat* outdata = (*env)->GetFloatArrayElements(env, out, 0);
	
	TXAGetaSipF(channel, outdata, size);

	(*env)->ReleaseFloatArrayElements(env, out, outdata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXAGetaSipF1
 * Signature: (IFI)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXAGetaSipF1
(JNIEnv* env, jobject obj, jint channel, jfloatArray out, jint size) {

	jfloat* outdata = (*env)->GetFloatArrayElements(env, out, 0);

	TXAGetaSipF1(channel, outdata, size);

	(*env)->ReleaseFloatArrayElements(env, out, outdata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXAGetaSpecF1
 * Signature: (IF)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXAGetaSpecF1
  (JNIEnv* env, jobject obj, jint channel, jfloatArray out){

	jfloat* outdata = (*env)->GetFloatArrayElements(env, out, 0);

	TXAGetSpecF1(channel, outdata);

	(*env)->ReleaseFloatArrayElements(env, out, outdata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXASetSipSpecmode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXASetSipSpecmode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	TXASetSipSpecmode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXACFIRRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXACFIRRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetTXACFIRRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetTXAMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetTXAMode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetTXAMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXASetNC
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXASetNC
  (JNIEnv* env, jobject obj, jint channel, jint nc){

	TXASetNC(channel, nc);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    TXASetMP
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_TXASetMP
  (JNIEnv* env, jobject obj, jint channel, jint mp){

	TXASetMP(channel, mp);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    XCreateAnalyzer
 * Signature: (I[IIIILjava/lang/String{})V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_XCreateAnalyzer
(JNIEnv* env, jobject obj, jint disp, jintArray success, jint m_size, jint m_LO, jint m_stitch, jstring app_data_path) {
	
	jint* successptr = (*env)->GetIntArrayElements(env, success, 0);
	const char* app_data_path_ptr = (*env)->GetStringUTFChars(env, app_data_path, NULL);
	
	XCreateAnalyzer(disp, successptr, m_size, m_LO, m_stitch, app_data_path_ptr);
	
	(*env)->ReleaseStringUTFChars(env, app_data_path, app_data_path_ptr);
	(*env)->ReleaseIntArrayElements(env, success, successptr, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    DestroyAnalyzer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_DestroyAnalyzer
(JNIEnv* env, jobject obj, jint disp) {
	
	DestroyAnalyzer(disp);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetAnalyzer
 * Signature: (IIII[IIIIDIIIIIIIDDI)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetAnalyzer
(JNIEnv* env, jobject obj, jint disp, jint n_pixout, jint n_fft, jint typ, jintArray flp, jint sz, jint bf_sz, jint win_type, jdouble pi, jint ovrlp, jint clp, jint fscLin, jint fscHin, jint n_pix, jint n_stch, jint cal_set, jdouble fmin, jdouble fmax, jint max_w) {

	jint* flpptr = (*env)->GetIntArrayElements(env, flp, 0);

	SetAnalyzer(disp, n_pixout, n_fft, typ, flpptr, sz, bf_sz, win_type, pi, ovrlp, clp, fscLin, fscHin, n_pix, n_stch, cal_set, fmin, fmax, max_w);
	
	(*env)->ReleaseIntArrayElements(env, flp, flpptr, 0);
}
/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetCalibration
 * Signature: (III[D)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetCalibration
  (JNIEnv* env, jobject obj, jint disp, jint num, jint points , jdoubleArray cal){

	jdouble* caldata = (*env)->GetDoubleArrayElements(env, cal, 0);

	SetCalibration(disp, num, points, cal);

	(*env)->ReleaseDoubleArrayElements(env, cal, caldata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetDisplayDetectorMode
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetDisplayDetectorMode
  (JNIEnv* env, jobject obj, jint disp, jint pixout, jint mode){

	SetDisplayDetectorMode(disp, pixout, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetDisplayAverageMode
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetDisplayAverageMode
  (JNIEnv* env, jobject obj, jint disp, jint pixout, jint mode){
	
	SetDisplayAverageMode(disp, pixout, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetDisplayNumAverage
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetDisplayNumAverage
  (JNIEnv* env, jobject obj, jint disp, jint pixout, jint num){

	SetDisplayNumAverage(disp, pixout, num);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetDisplayAvBackmult
 * Signature: (IID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetDisplayAvBackmult
  (JNIEnv* env, jobject obj, jint disp, jint pixout, jdouble mult){
	
	SetDisplayAvBackmult(disp, pixout, mult);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetDisplaySampleRate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetDisplaySampleRate
  (JNIEnv* env, jobject obj, jint disp, jint rate){

	SetDisplaySampleRate(disp, rate);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetDisplayNormOneHz
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetDisplayNormOneHz
  (JNIEnv* env, jobject obj, jint disp, jint pixout, jint norm){

	SetDisplayNormOneHz(disp, pixout, norm);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    Spectrum2
 * Signature: (IIIID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_Spectrum2
  (JNIEnv * env, jobject obj, jint run, jint disp, jint ss, jint LO , jdoubleArray buffer) {
	
	jdouble* fbuffer = (*env)->GetDoubleArrayElements(env, buffer, 0);
	
	Spectrum2(run, disp, ss, LO, fbuffer);

	(*env)->ReleaseDoubleArrayElements(env, buffer, fbuffer, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    Spectrum0
 * Signature: (IIIID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_Spectrum0
  (JNIEnv* env, jobject obj, jint run, jint disp, jint ss, jint LO, jdoubleArray buff){

	jdouble* buffdata = (*env)->GetDoubleArrayElements(env, buff, 0);

	Spectrum0(run, disp, ss, LO, buffdata);

	(*env)->ReleaseDoubleArrayElements(env, buff, buffdata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    Spectrum
 * Signature: (IIIDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_Spectrum
(JNIEnv* env, jobject obj, jint channel, jint ss, jint LO, jdoubleArray i, jdoubleArray q) {
	
	jfloat* fi = (*env)->GetDoubleArrayElements(env, i, 0);
	jfloat* fq = (*env)->GetDoubleArrayElements(env, q, 0);
	
	Spectrum(channel, ss, LO, fi, fq);
	
	(*env)->ReleaseDoubleArrayElements(env, q, fq, 0);
	(*env)->ReleaseDoubleArrayElements(env, i, fi, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    GetPixels
 * Signature: (II[F[I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_GetPixels
(JNIEnv* env, jobject obj, jint disp, jint pixout, jfloatArray pix, jintArray flag) {

	jfloat* pixptr = (*env)->GetFloatArrayElements(env, pix, 0);
	jint* flagptr = (*env)->GetIntArrayElements(env, flag, 0);

	GetPixels(disp, pixout, pixptr, flagptr);

	(*env)->ReleaseIntArrayElements(env, flag, flagptr, 0);
	(*env)->ReleaseFloatArrayElements(env, pix, pixptr, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    create_anb
 * Signature: (IIDDDDDDDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_create_anb
  (JNIEnv* env, jobject obj, jint run, jint buffsize, jdoubleArray in, jdoubleArray out, jdouble samplerate, jdouble tau, jdouble hangtime, jdouble advtime, jdouble backtau, jdouble threshold){
	
	jdouble* indata = (*env)->GetDoubleArrayElements(env, in, 0);
	jdouble* outdata = (*env)->GetDoubleArrayElements(env, out, 0);

	create_anb(run, buffsize, indata, outdata, samplerate, tau, hangtime, advtime, backtau, threshold);

	(*env)->ReleaseDoubleArrayElements(env, out, outdata, 0);
	(*env)->ReleaseDoubleArrayElements(env, in, indata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    create_nob
 * Signature: (IIDDDIDDDDDDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_create_nob
  (JNIEnv* env, jobject obj, jint run, jint buffsize, jdoubleArray in, jdoubleArray out, jdouble samplerate, jint mode, jdouble advslewtime, jdouble advtime, jdouble hangslewtime, jdouble hangtime, jdouble max_imp_seq_time, jdouble backtau, jdouble threshold){

	jdouble* indata = (*env)->GetDoubleArrayElements(env, in, 0);
	jdouble* outdata = (*env)->GetDoubleArrayElements(env, out, 0);

	create_nob(run, buffsize, indata, outdata, samplerate, mode, advslewtime, advtime, hangslewtime, hangtime, max_imp_seq_time, backtau, threshold);

	(*env)->ReleaseDoubleArrayElements(env, out, outdata, 0);
	(*env)->ReleaseDoubleArrayElements(env, in, indata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    create_nobEXT
 * Signature: (IIIIDDDDDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_create_nobEXT
  (JNIEnv* env, jobject obj, jint id, jint run, jint mode, jint buffsize, jdouble samplerate, jdouble slewtime, jdouble hangtime, jdouble advtime, jdouble backtau, jdouble threshold){

	create_nobEXT(id, run, mode, buffsize, samplerate, slewtime, hangtime, advtime, backtau, threshold);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    destroy_nobEXT
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_destroy_nobEXT
  (JNIEnv* env, jobject obj, jint id){

	destroy_nobEXT(id);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    flush_nobEXT
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_flush_nobEXT
  (JNIEnv* env, jobject obj, jint id){

	flush_nobEXT(id);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    xnobEXT
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_xnobEXT
  (JNIEnv* env, jobject obj, jint channel, jdoubleArray in, jdoubleArray out){

	jdouble* indata = (*env)->GetDoubleArrayElements(env, in, 0);
	jdouble* outdata = (*env)->GetDoubleArrayElements(env, out, 0);

	xnobEXT(channel, in, out);

	(*env)->ReleaseDoubleArrayElements(env, out, outdata, 0);
	(*env)->ReleaseDoubleArrayElements(env, in, indata, 0);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBRun
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBRun
  (JNIEnv* env, jobject obj, jint channel, jint run){

	SetEXTNOBRun(channel, run);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBMode
  (JNIEnv* env, jobject obj, jint channel, jint mode){

	SetEXTNOBMode(channel, mode);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBSamplerate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBSamplerate
  (JNIEnv* env, jobject obj, jint channel, jint rate){

	SetEXTNOBSamplerate(channel, rate);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBBuffsize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBBuffsize
  (JNIEnv* env, jobject obj, jint channel, jint size){

	SetEXTNOBBuffsize(channel, size);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBTau
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBTau
  (JNIEnv* env, jobject obj, jint channel, jdouble tau){

	SetEXTNOBTau(channel, tau);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBHangtime
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBHangtime
  (JNIEnv* env, jobject obj, jint channel, jdouble time){

	SetEXTNOBHangtime(channel, time);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBAdvtime
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBAdvtime
  (JNIEnv* env, jobject obj, jint channel, jdouble time){

	SetEXTNOBAdvtime(channel, time);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTNOBBacktau
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTNOBBacktau
  (JNIEnv* env, jobject obj, jint channel, jdouble tau){

	SetEXTNOBBacktau(channel, tau);
}

/*
 * Class:     org_openhpsdr_dsp_Wdsp
 * Method:    SetEXTANBNOBThreshold
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_org_openhpsdr_dsp_Wdsp_SetEXTANBNOBThreshold
  (JNIEnv* env, jobject obj, jint channel, jdouble threshold){

	SetEXTNOBThreshold(channel, threshold);
}

#ifdef __cplusplus
}
#endif
