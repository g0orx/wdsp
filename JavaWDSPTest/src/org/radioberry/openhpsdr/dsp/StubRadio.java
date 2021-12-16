package org.radioberry.openhpsdr.dsp;



import java.util.Date;

public class StubRadio  implements Runnable {


  private WDSP wdsp;

  private final static int SAMPLES = 1024;
  private final static int BANDWIDTH = 48000;
  private final static double TIMESTEP = (1.0 / BANDWIDTH);
  private double timebase = 0.0;
  double amplitude;
  private int vfo = 3629000;
  private int frequency = 3630000;
  private float[] outlsamples;
  private float[] outrsamples;

  private int[] error = new int[1];
  private volatile Thread thread;

  // Local audio output
  private byte[] audiooutput = new byte[1024 * 4]; // 2 channels of shorts
  private int audiooutputindex = 0;

  public StubRadio() {
    wdsp = WDSP.getInstance();
    outlsamples = new float[Configuration.buffersize];
    outrsamples = new float[Configuration.buffersize];
  }

  public void start() {
    if (thread == null) {
      thread = new Thread(this);
      thread.setPriority(Thread.MAX_PRIORITY);
      thread.start();
    }
    //spectrumStream.setTimer();
  }

  public void stop() {
    thread = null;
  }

  @Override
  public void run() {
    while (thread == Thread.currentThread()) {
      runStubRadio();
    }
  }

  private void runStubRadio() {
    float[] inlsamples = new float[SAMPLES];
    float[] inrsamples = new float[SAMPLES];

    int index = 0;
    int count = 0;
    int amplitudeDB = -73;
    amplitude = 1 / Math.pow(Math.sqrt(10), -(double) amplitudeDB / 10);
    System.out.println("Output generator -73dBm (S9)  = " + amplitude);

    long start = new Date().getTime();
    double actual = 0.0;
    double required = 0.0;

    short[] audioBuffer = new short[2000];
    int audioIndex = 0;

    while (thread == Thread.currentThread()) {
      long now = new Date().getTime();
      required = ((now - start) / 1000.0) * 48000;
      if (actual - required < 0.0) {

        generateTone(inlsamples, inrsamples);

        // DSP demodulation
        wdsp.fexchange2(Channel.RX, inlsamples, inrsamples, outlsamples, outrsamples, error);

        // 48000 samples => 8000 samples ; simple decimation (no filter)
        for (int j = 0; j < Configuration.buffersize; j++) {
          if (index % 6 == 0) {
            audioBuffer[audioIndex++] = (short) (outlsamples[j] * 32767.0F * 0.05);
            if (audioIndex == 2000) {
              audioBuffer = new short[2000];
              audioIndex = 0;
            }
          }
          index++;
        }
        index = index % 6;

       wdsp.Spectrum(Display.RX, 0, 0, inrsamples, inlsamples);

        actual = actual + 1024;
      }
    }
  }

  private void generateTone(float[] inlsamples, float[] inrsamples) {
    int f1 = (int) frequency - vfo;
    int idx = 0;

    int amplitudeDB = -100;
    float noiseAmplitude = (float) (1 / Math.pow(Math.sqrt(10), -(double) amplitudeDB / 10));

    while (idx < SAMPLES) {
      double angle1 = f1 * 2 * Math.PI * timebase;
      inlsamples[idx] = noiseAmplitude * (2 * (float) Math.random() - 1);
      inrsamples[idx] = noiseAmplitude * (2 * (float) Math.random() - 1);
      inlsamples[idx] += (float) (((float) Math.sin(angle1) * amplitude));
      inrsamples[idx] += (float) (((float) Math.cos(angle1) * amplitude));
      idx++;
      timebase += TIMESTEP;
    }
  }
}

// End of source.
