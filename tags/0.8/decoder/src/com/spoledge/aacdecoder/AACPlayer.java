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

import java.net.HttpURLConnection;
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
    protected boolean responseCodeCheckEnabled = true;

    protected int audioBufferCapacityMs;
    protected int decodeBufferCapacityMs;
    protected PlayerCallback playerCallback;
    protected String metadataCharEnc;

    protected Decoder decoder;

    /**
     * The bit rate declared by the stream header - kb/s.
     */
    protected int declaredBitRate = -1;

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
     * Returns the flag if the HTTP / shoutcast response code should be checked or not.
     */
    public boolean getResponseCodeCheckEnabled() {
        return responseCodeCheckEnabled;
    }


    /**
     * Sets the flag if the HTTP / shoutcast response code should be checked or not.
     * This method was added for backward compatibility. By disabling the check
     * you also force pre-Kitkat devices to use original HttpURLConnection implementation
     * even for shoutcast streams.
     * This is enabled by default.
     * @since 0.8
     */
    public void setResponseCodeCheckEnabled( boolean responseCodeCheckEnabled ) {
        this.responseCodeCheckEnabled = responseCodeCheckEnabled;
    }


    /**
     * Sets the encoding for the metadata strings.
     * If not set, then UTF-8 is used.
     */
    public void setMetadataCharEnc( String metadataCharEnc ) {
        this.metadataCharEnc = metadataCharEnc;
    }


    /**
     * Returns the bit-rate as declared by the stream metadata.
     * @return the bitrate in kb/s or -1 if unknown
     * @since 0.8
     */
    public int getDeclaredBitRate() {
        return declaredBitRate;
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
     * @param expectedKBitSecRate the expected average bitrate in kbit/sec;
     *      -1 means unknown;
     *      when setting this parameter, then the declared bit-rate from the stream header is ignored
     */
    public void play( String url, int expectedKBitSecRate ) throws Exception {
        declaredBitRate = -1;

        if (url.indexOf( ':' ) > 0) {
            URLConnection cn = openConnection( url );
            InputStream is = null;

            try {
                if (responseCodeCheckEnabled) checkResponseCode( cn );
                processHeaders( cn );
                is = getInputStream( cn );

                // try to get the expectedKBitSecRate from headers
                // but if then expectedKBitSecRate is passed, then ignore the declared one:
                play( is, expectedKBitSecRate != -1 ? expectedKBitSecRate : declaredBitRate );
            }
            finally {
                try { is.close(); } catch (Throwable t) {}

                if (cn instanceof HttpURLConnection) {
                    try { ((HttpURLConnection)cn).disconnect(); } catch (Throwable t) {}
                }
            }
        }
        else {
            processFileType( url );
            InputStream is = new FileInputStream( url );

            try {
                play( is, expectedKBitSecRate );
            }
            finally {
                try { is.close(); } catch (Throwable t) {}
            }
        }
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

            if (info.getFirstSamples() != null) {
                short[] firstSamples = info.getFirstSamples();
                Log.d( LOG, "First samples length: " + firstSamples.length );

                pcmfeed.feed( firstSamples, firstSamples.length );
                info.setFirstSamples( null );
            }

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
            boolean stopImmediatelly = stopped;
            stopped = true;

            if (pcmfeed != null) pcmfeed.stop( !stopImmediatelly );
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
     * Opens connection.
     * Tries to recognize if the stream is a standard HTTP or SHOUTCAST.
     * Since Android 4.4 Kitkat the HttpURLConnection implementation is strict
     * and does not allow SHOUTCAST response "ICY 200 OK".
     * If we detect this, we try to use alternate protocol "icy" and 
     * our auxiliar implementation - IcyURLConnection.
     * NOTE: URL.setURLStreamHandlerFactory() must be called - this library does not call it
     * itself.
     */
    protected URLConnection openConnection( String url ) throws IOException {
        URLConnection conn = null;
        boolean close = true;

        while (true) {
            conn = new URL( url ).openConnection();

            prepareConnection( conn );
            conn.connect();

            try {
                if (conn instanceof HttpURLConnection) {
                    HttpURLConnection httpConn = (HttpURLConnection) conn;

                    try {
                        // pre-KitKat returns -1:
                        if (httpConn.getResponseCode() == -1) {
                            if (!responseCodeCheckEnabled) {
                                Log.w( LOG, "No response code, but ignoring - for url " + url );
                                close = false;
                                break;
                            }
                            else {
                                Log.w( LOG, "No response code for url " + url );
                            }
                        }
                        else {
                            // standard HTTP response / IcyURLConnection response
                            close = false;
                            break;
                        }
                    }
                    catch (Exception e) {
                        // KitKat throws exception:
                        // java.net.ProtocolException: Unexpected status line: ICY 200 OK
                        Log.w( LOG, "Invalid response code for url " + url + " - " + e );
                    }
                }
                else if (conn.getHeaderFields() == null) {
                    // sanity code
                    Log.w( LOG, "No header fields in response for url " + url );
                }
                else {
                    close = false;
                    break;
                }

                if (url.startsWith( "http:" )) {
                    url = "icy" + url.substring( 4 );
                    Log.i( LOG, "Trying to re-connect as ICY url " + url );
                }
                else throw new IOException( "Invalid response - no response code / headers detected" );
            }
            finally {
                if (close) {
                    if (conn instanceof HttpURLConnection) {
                        try { ((HttpURLConnection)conn).disconnect(); } catch (Throwable t) {}
                    }
                    conn = null;
                }
            }
        }

        return conn;
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
     * Checks the response code.
     * Actually for HttpURLConnection it throws an exception
     * when the response code is not between 200 and 299.
     */
    protected void checkResponseCode( URLConnection conn ) throws Exception {
        if (conn instanceof HttpURLConnection) {
            HttpURLConnection httpConn = (HttpURLConnection) conn;

            int responseCode = httpConn.getResponseCode();

            if (responseCode == -1) {
                Log.w( LOG, "Empty response code: " + responseCode + " " + httpConn.getResponseMessage());
            }
            else if (responseCode < 200 || responseCode > 299) {
                Log.e( LOG, "Error response code: " + responseCode + " " + httpConn.getResponseMessage());
                throw new IOException( "Error response: " + responseCode + " " + httpConn.getResponseMessage());
            }
            else {
                Log.d( LOG, "Response: " + responseCode + " " + httpConn.getResponseMessage());
            }
        }
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

                ret = new IcyInputStream( ret, period, playerCallback, metadataCharEnc );
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

        String br = cn.getHeaderField( "icy-br" );

        if (br != null) {
            try {
                declaredBitRate = Integer.parseInt( br );

                if (declaredBitRate > 7) {
                    Log.d( LOG, "Declared bitrate is " + declaredBitRate + " kb/s" );
                }
                else {
                    Log.w( LOG, "Declared bitrate is too low - ignoring: " + declaredBitRate + " kb/s" );
                    declaredBitRate = -1;
                }
            }
            catch (Exception e) {
                Log.w( LOG, "Cannot parse declared bit-rate '" + br + "'" );
            }
        }

        if (playerCallback != null) {
            for (java.util.Map.Entry<String, java.util.List<String>> me : cn.getHeaderFields().entrySet()) {
                for (String s : me.getValue()) {
                    playerCallback.playerMetadata( me.getKey(), s );
                }
            }
        }
    }


    protected void dumpHeaders( URLConnection cn ) {
        if (cn.getHeaderFields() == null) {
            Log.d( LOG, "No headers - not an HTTP response ?" );
            return;
        }

        for (java.util.Map.Entry<String, java.util.List<String>> me : cn.getHeaderFields().entrySet()) {
            for (String s : me.getValue()) {
                Log.d( LOG, "header: key=" + me.getKey() + ", val=" + s);
            }
        }
    }


    /**
     * This method is called before opening the file.
     * Actually this method does nothing, but subclasses may override it.
     */
    protected void processFileType( String file ) {
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
