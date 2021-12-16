package org.radioberry.openhpsdr.dsp;


import java.io.File;

public class Test {

    private WDSP wdsp;

    public static final int CHANNEL_RX=0;
    public final static double SAMPLERATE = 48000.0;
    public final static double DSPRATE = 48000.0;
    public final static int BUFFERSIZE = 1024;
    public final static int FFTSIZE = 4096;

    public static void main(String... arg){

        Test test = new Test();

        System.out.println("Start wisdom check/generate");
        test.handleWisdom();
        System.out.println("End wisdom check/generate");


        System.out.println("Start WDSP check");
        try {
            test.runWDSP();

            StubRadio stubRadio = new StubRadio();
            stubRadio.start();

            boolean run = true;
            float[] samples = new float[1280];
            while (run) {
                Thread.sleep(100);
                int[] result = new int[1];
                test.wdsp.GetPixels(Display.RX, samples, result);
                if (result[0] == 1)
                    try {
                        System.out.print(".");
                    } catch (Exception ex) {}

                int meter = (int) test.wdsp.GetRXAMeter(Channel.RX, WDSP.S_AV);
            }

            test.stop();
        } catch (Exception ex) {System.out.println("Fatal");}

        System.out.println("");
        System.out.println("WDSP check seems complete");

    }

    public Test() {
        wdsp = WDSP.getInstance();
    }


    private void runWDSP() {

        wdsp.OpenChannel(CHANNEL_RX,
                BUFFERSIZE,  FFTSIZE, (int) SAMPLERATE,
                (int) DSPRATE, 48000,
                0/* rx */, 1/* RUNNING */, 0.010, 0.025, 0.0, 0.010, 0);

        wdsp.SetRXAMode(Channel.RX, Settings.LSB);
        wdsp.SetRXABandpassFreqs(Channel.RX, Settings.filterLow[Settings.LSB],
                Settings.filterHigh[Settings.LSB]);
        wdsp.SetRXABandpassRun(Channel.RX, 1);
        setAGC(Channel.RX, Settings.AGC_SLOW);
        wdsp.SetRXAAGCTop(Channel.RX, 120);
        wdsp.SetRXAAMDSBMode(Channel.RX, 0);

        wdsp.SetRXAEMNRRun(Channel.RX, Configuration.NB2 ? 1 : 0);
        wdsp.SetRXAEMNRgainMethod(Channel.RX, Configuration.NB2_GAIN);
        wdsp.SetRXAEMNRnpeMethod(Channel.RX, Configuration.NB2_NPE);
        wdsp.SetRXAEMNRaeRun(Channel.RX, Configuration.NB2_AE ? 1 : 0);
        wdsp.SetRXAEMNRPosition(Channel.RX, Configuration.NB2_POSITION);
        wdsp.SetRXAANRRun(Channel.RX, Configuration.NR ? 1 : 0);
        wdsp.SetRXAANFRun(Channel.RX, Configuration.ANF ? 1 : 0);

       setSpectrumAnalyzer();
    }

    public void stop() {
        wdsp.DestroyAnalyzer(Display.RX);
        wdsp.SetChannelState(Channel.RX, 0, 0);
        wdsp.CloseChannel(Channel.RX);
    }

    private void setAGC(int channel, int agc) {
        wdsp.SetRXAAGCMode(channel, agc);
        switch (agc) {
            case Settings.AGC_LONG:
                wdsp.SetRXAAGCAttack(channel, 2);
                wdsp.SetRXAAGCHang(channel, 2000);
                wdsp.SetRXAAGCDecay(channel, 2000);
                break;
            case Settings.AGC_SLOW:
                wdsp.SetRXAAGCAttack(channel, 2);
                wdsp.SetRXAAGCHang(channel, 1000);
                wdsp.SetRXAAGCDecay(channel, 500);
                break;
            case Settings.AGC_MEDIUM:
                wdsp.SetRXAAGCAttack(channel, 2);
                wdsp.SetRXAAGCHang(channel, 0);
                wdsp.SetRXAAGCDecay(channel, 250);
                break;
            case Settings.AGC_FAST:
                wdsp.SetRXAAGCAttack(channel, 2);
                wdsp.SetRXAAGCHang(channel, 0);
                wdsp.SetRXAAGCDecay(channel, 50);
                break;
        }
    }

    private void setSpectrumAnalyzer() {
        int[] error = new int[1];
        int[] success = new int[1];

        Log.info("Radio","XCreateAnalyzer...");
        // rx spectrum
        wdsp.XCreateAnalyzer(Display.RX, success, 262144, 1, 1, "");
        if (success[0] != 0) {
            Log.info("Radio","XCreateAnalyzer Display.RX failed:" + success[0]);
        }
        int flp[] = { 0 };
        double KEEP_TIME = 0.1;
        int spur_elimination_ffts = 1;
        int data_type = 1;
        int fft_size = 8192;
        int window_type = 4;
        double kaiser_pi = 14.0;
        int overlap = 2048;
        int clip = 0;
        int span_clip_l = 0;
        int span_clip_h = 0;
        int pixels = 1280;
        int stitches = 1;
        int avm = 0;
        double tau = 0.001 * 120.0;
        int MAX_AV_FRAMES = 60;
        int display_average = Math.max(
                2,
                (int) Math.min((double) MAX_AV_FRAMES,
                        (double) Configuration.fps * tau));
        double avb = Math.exp(-1.0 / (Configuration.fps * tau));
        int calibration_data_set = 0;
        double span_min_freq = 0.0;
        double span_max_freq = 0.0;

        int max_w = fft_size
                + (int) Math.min(
                KEEP_TIME * (double) Configuration.fps,
                KEEP_TIME * (double) fft_size
                        * (double) Configuration.fps);

        wdsp.SetAnalyzer(Display.RX,spur_elimination_ffts, // number of LO
                // frequencies =
                // number of ffts
                // used in
                // elimination
                1,
                data_type, // 0 for real input data (I only); 1 for complex
                // input data (I & Q)
                flp, // vector with one elt for each LO frequency, 1 if
                // high-side LO, 0 otherwise
                fft_size, // size of the fft, i.e., number of input samples
                Configuration.buffersize, // number of samples
                // transferred for each
                // OpenBuffer()/CloseBuffer()
                window_type, // integer specifying which window function to use
                kaiser_pi, // PiAlpha parameter for Kaiser window
                overlap, // number of samples each fft (other than the first) is
                // to re-use from the previous
                clip, // number of fft output bins to be clipped from EACH side
                // of each sub-span
                span_clip_l, // number of bins to clip from low end of entire
                // span
                span_clip_h, // number of bins to clip from high end of entire
                // span
                pixels, // number of pixel values to return. may be either <= or
                // > number of bins
                stitches, // number of sub-spans to concatenate to form a
                // complete span
                calibration_data_set, // identifier of which set of calibration
                // data to use
                span_min_freq, // frequency at first pixel value8192
                span_max_freq, // frequency at last pixel value
                max_w // max samples to hold in input ring buffers
        );
    }

    private void handleWisdom() {
        if (System.getProperty("os.name").startsWith("Windows")) {
            String libraryPath=System.getProperty("user.dir");
            wdsp.WDSPwisdom(libraryPath+ File.separator);
        } else if(System.getProperty("os.name").startsWith("Linux")) {
            String libraryPath=System.getProperty("user.dir");
            wdsp.WDSPwisdom(libraryPath+File.separator);
        }
    }
}
