/*
** AACDecoder - Freeware Advanced Audio (AAC) Decoder for Android
** Copyright (C) 2011 Spolecne s.r.o., http://www.spoledge.com
**  
** This file is a part of AACDecoder.
**
** AACDecoder is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation; either version 3 of the License,
** or (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
package com.spoledge.aacdecoder;

import android.util.Log;

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.IOException;

import java.net.URL;
import java.net.URLConnection;


/**
 * This is the AAC Stream player class.
 * It uses Decoder to decode AAC stream into PCM samples.
 * This class is not thread safe.
 * <pre>
 *  AACPlayer player = new AACPlayer();
 *
 *  String url = ...;
 *  player.playAsync( url );
 * </pre>
 */
public class AACPlayer {

    /**
     * The default expected bitrate.
     * Used only if not specified in play() methods.
     */
    public static final int DEFAULT_EXPECTED_KBITSEC_RATE = 64;


    /**
     * The default capacity of the audio buffer (AudioTrack) in ms.
     * @see setAudioBufferCapacityMs(int)
     */
    public static final int DEFAULT_AUDIO_BUFFER_CAPACITY_MS = 1500;


    /**
     * The default capacity of the output buffer used for decoding in ms.
     * @see setDecodeBufferCapacityMs(int)
     */
    public static final int DEFAULT_DECODE_BUFFER_CAPACITY_MS = 700;


    private static final String LOG = "AACPlayer";


    ////////////////////////////////////////////////////////////////////////////
    // Attributes
    ////////////////////////////////////////////////////////////////////////////

    protected boolean stopped;
    protected boolean metadataEnabled = true;

    protected int audioBufferCapacityMs;
    protected int decodeBufferCapacityMs;
    protected PlayerCallback playerCallback;

    protected Decoder decoder;

    // variables used for computing average bitrate
    private int sumKBitSecRate = 0;
    private int countKBitSecRate = 0;
    private int avgKBitSecRate = 0;


    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Creates a new player.
     */
    public AACPlayer() {
        this( null );
    }


    /**
     * Creates a new player.
     * @param playerCallback the callback, can be null
     */
    public AACPlayer( PlayerCallback playerCallback ) {
        this( playerCallback, DEFAULT_AUDIO_BUFFER_CAPACITY_MS, DEFAULT_DECODE_BUFFER_CAPACITY_MS );
    }


    /**
     * Creates a new player.
     * @param playerCallback the callback, can be null
     * @param audioBufferCapacityMs the capacity of the audio buffer (AudioTrack) in ms
     * @param decodeBufferCapacityMs the capacity of the buffer used for decoding in ms
     * @see setAudioBufferCapacityMs(int)
     * @see setDecodeBufferCapacityMs(int)
     */
    public AACPlayer( PlayerCallback playerCallback, int audioBufferCapacityMs, int decodeBufferCapacityMs ) {
        setPlayerCallback( playerCallback );
        setAudioBufferCapacityMs( audioBufferCapacityMs );
        setDecodeBufferCapacityMs( decodeBufferCapacityMs );

        decoder = createDecoder();
    }


    ////////////////////////////////////////////////////////////////////////////
    // Public
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Returns the underlying decoder.
     */
    public Decoder getDecoder() {
        return decoder;
    }


    /**
     * Sets the custom decoder.
     */
    public void setDecoder( Decoder decoder ) {
        this.decoder = decoder;
    }


    /**
     * Sets the audio buffer (AudioTrack) capacity.
     * The capacity can be expressed in time of audio playing of such buffer.
     * For example 1 second buffer capacity is 88100 samples for 44kHz stereo.
     * By setting this the audio will start playing after the audio buffer is first filled.
     *
     * NOTE: this should be set BEFORE any of the play methods are called.
     *
     * @param audioBufferCapacityMs the capacity of the buffer in milliseconds
     */
    public void setAudioBufferCapacityMs( int audioBufferCapacityMs ) {
        this.audioBufferCapacityMs = audioBufferCapacityMs;
    }


    /**
     * Gets the audio buffer capacity as the audio playing time.
     * @return the capacity of the audio buffer in milliseconds
     */
    public int getAudioBufferCapacityMs() {
        return audioBufferCapacityMs;
    }


    /**
     * Sets the capacity of the output buffer used for decoding.
     * The capacity can be expressed in time of audio playing of such buffer.
     * For example 1 second buffer capacity is 88100 samples for 44kHz stereo.
     * Decoder tries to fill out the whole buffer in each round.
     *
     * NOTE: this should be set BEFORE any of the play methods are called.
     *
     * @param decodeBufferCapacityMs the capacity of the buffer in milliseconds
     */
    public void setDecodeBufferCapacityMs( int decodeBufferCapacityMs ) {
        this.decodeBufferCapacityMs = decodeBufferCapacityMs;
    }


    /**
     * Gets the capacity of the output buffer used for decoding as the audio playing time.
     * @return the capacity of the decoding buffer in milliseconds
     */
    public int getDecodeBufferCapacityMs() {
        return decodeBufferCapacityMs;
    }


    /**
     * Sets the PlayerCallback.
     * NOTE: this should be set BEFORE any of the play methods are called.
     */
    public void setPlayerCallback( PlayerCallback playerCallback ) {
        this.playerCallback = playerCallback;
    }


    /**
     * Returns the PlayerCallback or null if no PlayerCallback was set.
     */
    public PlayerCallback getPlayerCallback() {
        return playerCallback;
    }


    /**
     * Returns the flag if metadata information is enabeld / sent to PlayerCallback.
     */
    public boolean getMetadataEnabled() {
        return metadataEnabled;
    }


    /**
     * Sets the flag if metadata information is enabeld / sent to PlayerCallback.
     * This is enabled by default.
     */
    public void setMetadataEnabled( boolean metadataEnabled ) {
        this.metadataEnabled = metadataEnabled;
    }


    /**
     * Plays a stream asynchronously.
     * This method starts a new thread.
     * @param url the URL of the stream or file
     */
    public void playAsync( final String url ) {
        playAsync( url, -1 );
    }


    /**
     * Plays a stream asynchronously.
     * This method starts a new thread.
     * @param url the URL of the stream or file
     * @param expectedKBitSecRate the expected average bitrate in kbit/sec; -1 means unknown
     */
    public void playAsync( final String url, final int expectedKBitSecRate ) {
        new Thread(new Runnable() {
            public void run() {
                try {
                    play( url, expectedKBitSecRate );
                }
                catch (Exception e) {
                    Log.e( LOG, "playAsync():", e);

                    if (playerCallback != null) playerCallback.playerException( e );
                }
            }
        }).start();
    }


    /**
     * Plays a stream synchronously.
     * @param url the URL of the stream or file
     */
    public void play( String url ) throws Exception {
        play( url, -1 );
    }


    /**
     * Plays a stream synchronously.
     * @param url the URL of the stream or file
     * @param expectedKBitSecRate the expected average bitrate in kbit/sec; -1 means unknown
     */
    public void play( String url, int expectedKBitSecRate ) throws Exception {
        if (url.indexOf( ':' ) > 0) {
            URLConnection cn = new URL( url ).openConnection();

            prepareConnection( cn );
            cn.connect();
            processHeaders( cn );

            // TODO: try to get the expectedKBitSecRate from headers
            play( getInputStream( cn ), expectedKBitSecRate);
        }
        else play( new FileInputStream( url ), expectedKBitSecRate );
    }


    /**
     * Plays a stream synchronously.
     * @param is the input stream
     */
    public void play( InputStream is ) throws Exception {
        play( is, -1 );
    }


    /**
     * Plays a stream synchronously.
     * @param is the input stream
     * @param expectedKBitSecRate the expected average bitrate in kbit/sec; -1 means unknown
     */
    public final void play( InputStream is, int expectedKBitSecRate ) throws Exception {
        stopped = false;

        if (playerCallback != null) playerCallback.playerStarted();

        if (expectedKBitSecRate <= 0) expectedKBitSecRate = DEFAULT_EXPECTED_KBITSEC_RATE;

        sumKBitSecRate = 0;
        countKBitSecRate = 0;

        playImpl( is, expectedKBitSecRate );
    }


    /**
     * Stops the execution thread.
     */
    public void stop() {
        stopped = true;
    }


    ////////////////////////////////////////////////////////////////////////////
    // Protected
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Plays a stream synchronously.
     * This is the implementation method calle by every play() and playAsync() methods.
     * @param is the input stream
     * @param expectedKBitSecRate the expected average bitrate in kbit/sec
     */
    protected void playImpl( InputStream is, int expectedKBitSecRate ) throws Exception {
        BufferReader reader = new BufferReader(
                                        computeInputBufferSize( expectedKBitSecRate, decodeBufferCapacityMs ),
                                        is );
        new Thread( reader ).start();

        PCMFeed pcmfeed = null;
        Thread pcmfeedThread = null;

        // profiling info
        long profMs = 0;
        long profSamples = 0;
        long profSampleRate = 0;
        int profCount = 0;

        try {
            Decoder.Info info = decoder.start( reader );

            Log.d( LOG, "play(): samplerate=" + info.getSampleRate() + ", channels=" + info.getChannels());

            profSampleRate = info.getSampleRate() * info.getChannels();

            if (info.getChannels() > 2) {
                throw new RuntimeException("Too many channels detected: " + info.getChannels());
            }

            // 3 buffers for result samples:
            //   - one is used by decoder
            //   - one is used by the PCMFeeder
            //   - one is enqueued / passed to PCMFeeder - non-blocking op
            short[][] decodeBuffers = createDecodeBuffers( 3, info );
            short[] decodeBuffer = decodeBuffers[0]; 
            int decodeBufferIndex = 0;

            pcmfeed = createPCMFeed( info );
            pcmfeedThread = new Thread( pcmfeed );
            pcmfeedThread.start();

            do {
                long tsStart = System.currentTimeMillis();

                info = decoder.decode( decodeBuffer, decodeBuffer.length );
                int nsamp = info.getRoundSamples();

                profMs += System.currentTimeMillis() - tsStart;
                profSamples += nsamp;
                profCount++;

                Log.d( LOG, "play(): decoded " + nsamp + " samples" );

                if (nsamp == 0 || stopped) break;
                if (!pcmfeed.feed( decodeBuffer, nsamp ) || stopped) break;

                int kBitSecRate = computeAvgKBitSecRate( info );
                if (Math.abs(expectedKBitSecRate - kBitSecRate) > 1) {
                    Log.i( LOG, "play(): changing kBitSecRate: " + expectedKBitSecRate + " -> " + kBitSecRate );
                    reader.setCapacity( computeInputBufferSize( kBitSecRate, decodeBufferCapacityMs ));
                    expectedKBitSecRate = kBitSecRate;
                }

                decodeBuffer = decodeBuffers[ ++decodeBufferIndex % 3 ];
            } while (!stopped);
        }
        finally {
            stopped = true;

            if (pcmfeed != null) pcmfeed.stop();
            decoder.stop();
            reader.stop();

            int perf = 0;

            if (profCount > 0) Log.i( LOG, "play(): average decoding time: " + profMs / profCount + " ms");

            if (profMs > 0) {
                perf = (int)((1000*profSamples / profMs - profSampleRate) * 100 / profSampleRate);

                Log.i( LOG, "play(): average rate (samples/sec): audio=" + profSampleRate
                    + ", decoding=" + (1000*profSamples / profMs)
                    + ", audio/decoding= " + perf
                    + " %  (the higher, the better; negative means that decoding is slower than needed by audio)");
            }

            if (pcmfeedThread != null) pcmfeedThread.join();

            if (playerCallback != null) playerCallback.playerStopped( perf );
        }
    }


    protected Decoder createDecoder() {
        return Decoder.create();
    }


    protected short[][] createDecodeBuffers( int count, Decoder.Info info ) {
        int size = PCMFeed.msToSamples( decodeBufferCapacityMs, info.getSampleRate(), info.getChannels());

        short[][] ret = new short[ count ][];

        for (int i=0; i < ret.length; i++) {
            ret[i] = new short[ size ];
        }

        return ret;
    }


    protected PCMFeed createPCMFeed( Decoder.Info info ) {
        int size = PCMFeed.msToBytes( audioBufferCapacityMs, info.getSampleRate(), info.getChannels());

        return new PCMFeed( info.getSampleRate(), info.getChannels(), size, playerCallback );
    }


    /**
     * Prepares the connection.
     * This method is called before a connection is opened.
     * Actually sets "Icy-MetaData" header to "1" if metadata are enabled.
     */
    protected void prepareConnection( URLConnection conn ) {
        // request for dynamic metadata:
        if (metadataEnabled) conn.setRequestProperty("Icy-MetaData", "1");
    }


    /**
     * Gets the input stream from the connection.
     * Actually returns the underlying stream or IcyInputStream.
     */
    protected InputStream getInputStream( URLConnection conn ) throws Exception {
        String smetaint = conn.getHeaderField( "icy-metaint" );
        InputStream ret = conn.getInputStream();

        if (!metadataEnabled) {
            Log.i( LOG, "Metadata not enabled" );
        }
        else if (smetaint != null) {
            int period = -1;
            try {
                period = Integer.parseInt( smetaint );
            }
            catch (Exception e) {
                Log.e( LOG, "The icy-metaint '" + smetaint + "' cannot be parsed: '" + e );
            }

            if (period > 0) {
                Log.i( LOG, "The dynamic metainfo is sent every " + period + " bytes" );

                ret = new IcyInputStream( ret, period, playerCallback );
            }
        }
        else Log.i( LOG, "This stream does not provide dynamic metainfo" );

        return ret;
    }


    /**
     * This method is called after the connection is established.
     */
    protected void processHeaders( URLConnection cn ) {
        dumpHeaders( cn );

        if (playerCallback != null) {
            for (java.util.Map.Entry<String, java.util.List<String>> me : cn.getHeaderFields().entrySet()) {
                for (String s : me.getValue()) {
                    playerCallback.playerMetadata( me.getKey(), s );
                }
            }
        }
    }


    protected void dumpHeaders( URLConnection cn ) {
        for (java.util.Map.Entry<String, java.util.List<String>> me : cn.getHeaderFields().entrySet()) {
            for (String s : me.getValue()) {
                Log.d( LOG, "header: key=" + me.getKey() + ", val=" + s);
            }
        }
    }


    protected int computeAvgKBitSecRate( Decoder.Info info ) {
        // do not change the value after a while - avoid changing of the out buffer:
        if (countKBitSecRate < 64) {
            int kBitSecRate = computeKBitSecRate( info );
            int frames = info.getRoundFrames();

            sumKBitSecRate += kBitSecRate * frames;
            countKBitSecRate += frames;
            avgKBitSecRate = sumKBitSecRate / countKBitSecRate;
        }

        return avgKBitSecRate;
    }


    protected static int computeKBitSecRate( Decoder.Info info ) {
        if (info.getRoundSamples() <= 0) return -1;

        return computeKBitSecRate( info.getRoundBytesConsumed(), info.getRoundSamples(),
                                   info.getSampleRate(), info.getChannels());
    }


    protected static int computeKBitSecRate( int bytesconsumed, int samples, int sampleRate, int channels ) {
        long ret = 8L * bytesconsumed * channels * sampleRate / samples;

        return (((int)ret) + 500) / 1000;
    }


    protected static int computeInputBufferSize( int kbitSec, int durationMs ) {
        return kbitSec * durationMs / 8;
    }


    protected static int computeInputBufferSize( Decoder.Info info, int durationMs ) {

        return computeInputBufferSize( info.getRoundBytesConsumed(), info.getRoundSamples(),
                                        info.getSampleRate(), info.getChannels(), durationMs );
    }


    protected static int computeInputBufferSize( int bytesconsumed, int samples,
                                                 int sampleRate, int channels, int durationMs ) {

        return (int)(((long) bytesconsumed) * channels * sampleRate * durationMs  / (1000L * samples));
    }

}
