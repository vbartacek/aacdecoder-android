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

/**
 * The decoder which calls native implementation(s).
 */
public class Decoder {

    /**
     * Info about the stream.
     */
    public static final class Info {
        private int sampleRate;
        private int channels;

        private int frameMaxBytesConsumed;
        private int frameSamples;

        private int roundFrames;
        private int roundBytesConsumed;
        private int roundSamples;

        private short[] firstSamples;


        ////////////////////////////////////////////////////////////////////////////
        // Public
        ////////////////////////////////////////////////////////////////////////////

        /**
         * Returns the sampling rate in Hz.
         * @return the sampling rate - always set
         */
        public int getSampleRate() {
            return sampleRate;
        }


        /**
         * Returns the number of channels (0=unknown yet, 1=mono, 2=stereo).
         * @return the channels - always set
         */
        public int getChannels() {
            return channels;
        }


        /**
         * Returns the maximum bytes consumed per ADTS frame.
         * @return the value - after each decode() round
         */
        public int getFrameMaxBytesConsumed() {
            return frameMaxBytesConsumed;
        }


        /**
         * Returns the samples produced per ADTS frame.
         * @return the value - after each decode() round (but should be always the same)
         */
        public int getFrameSamples() {
            return frameSamples;
        }


        /**
         * Returns the number of ADTS frames decoded.
         * @return the value - after each decode() round
         */
        public int getRoundFrames() {
            return roundFrames;
        }


        /**
         * Returns the number of bytes consumed.
         * @return the value - after each decode() round
         */
        public int getRoundBytesConsumed() {
            return roundBytesConsumed;
        }


        /**
         * Returns the number of samples decoded.
         * @return the value - after each decode() round
         */
        public int getRoundSamples() {
            return roundSamples;
        }


        /**
         * Returns the samples read by the start() method.
         * @return the sample or null if the decoder does not support this
         */
        public short[] getFirstSamples() {
            return firstSamples;
        }


        /**
         * Sets the first samples data.
         * This method can be used only for clearing memory.
         */
        public void setFirstSamples( short[] firstSamples ) {
            this.firstSamples = firstSamples;
        }
    }


    protected static int STATE_IDLE = 0;
    protected static int STATE_RUNNING = 1;

    private static boolean libLoaded = false;


    ////////////////////////////////////////////////////////////////////////////
    // Attributes
    ////////////////////////////////////////////////////////////////////////////

    /**
     * The decoder pointer.
     * This is by default 0 - which means that the OpenCORE aacdec decoder is used.
     * Otherwise it must be set to a valid C pointer to a AACDDecoder struct.
     */
    protected long decoder;


    /**
     * The decoding context pointer.
     * This is used between calls to C functions to kkep pointer to a C struct.
     */
    protected long aacdw;


    /**
     * The state of decoder: idle/running
     */
    protected int state = STATE_IDLE;


    /**
     * The information passed between JNI and Java.
     */
    protected Info info;


    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////

    protected Decoder(long decoder ) {
        this.decoder = decoder;
    }


    ////////////////////////////////////////////////////////////////////////////
    // Public
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Loads the native library.
     * This method is automatically called when first needed.
     */
    public static synchronized void loadLibrary() {
        if (!libLoaded) {
            System.loadLibrary( "aacdecoder" );

            libLoaded = true;
        }
    }


    /**
     * Creates a new default AAC decoder.
     */
    public static Decoder create() {
        return create( 0 );
    }


    /**
     * Creates a new decoder by its name.
     * @return the decoder or null if no such decoder is found
     */
    public static Decoder createByName( String name ) {
        loadLibrary();

        long aacdw = nativeDecoderGetByName( name );

        return aacdw != 0 ? create( aacdw ) : null;
    }


    /**
     * Creates a new decoder.
     * @param decoder the poiter to a C struct AACDDecoder. 0 means that the default OpenCORE aacdec
     *      decoder will be used.
     */
    public static synchronized Decoder create( long decoder ) {
        loadLibrary();

        return new Decoder( decoder );
    }


    /**
     * Starts decoding stream.
     */
    public Info start( BufferReader reader ) {
        if (state != STATE_IDLE) throw new IllegalStateException();

        info = new Info();

        aacdw = nativeStart( decoder, reader, info );

        if (aacdw == 0) throw new RuntimeException("Cannot start native decoder");

        state = STATE_RUNNING;

        return info;
    }


    /**
     * Decodes stream.
     * @return the number of samples produced (totally all channels = the length of the filled array)
     */
    public Info decode( short[] samples, int outLen ) {
        if (state != STATE_RUNNING) throw new IllegalStateException();

        nativeDecode( aacdw, samples, outLen );

        return info;
    }


    /**
     * Stops the decoder and releases all resources.
     */
    public void stop() {
        if (aacdw != 0) {
            nativeStop( aacdw );
            aacdw = 0;
        }

        state = STATE_IDLE;
    }


    ////////////////////////////////////////////////////////////////////////////
    // Protected
    ////////////////////////////////////////////////////////////////////////////

    @Override
    protected void finalize() {
        try {
            stop();
        }
        catch (Throwable t) {
            t.printStackTrace();
        }
    }


    ////////////////////////////////////////////////////////////////////////////
    // Private
    ////////////////////////////////////////////////////////////////////////////


    /**
     * Actually starts decoding the stream.
     * Detects the stream type.
     * @param decoder the pointer to the C struct AACDDecoder or NULL
     * @return the pointer to the C struct
     */
    protected native long nativeStart(long decoder, BufferReader reader, Info info );


    /**
     * Actually decodes a chunk of data.
     * Calls back Java method BufferReader.next() when additional input is needed.
     * @param aacdw the pointer to the C struct
     */
    protected native long nativeDecode( long aacdw, short[] samples, int outLen );


    /**
     * Actually stops decoding - releases all resources.
     * @param aacdw the pointer to the C struct
     */
    protected native void nativeStop( long aacdw );


    /**
     * Returns the decoder pointer struct or NULL.
     * @param name the name of the decoder
     */
    protected static native long nativeDecoderGetByName( String name );


}

