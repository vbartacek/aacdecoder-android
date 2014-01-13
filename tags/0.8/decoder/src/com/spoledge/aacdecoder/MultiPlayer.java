/*
** AACDecoder - Freeware Advanced Audio (AAC) Decoder for Android
** Copyright (C) 2012 Spolecne s.r.o., http://www.spoledge.com
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

import java.net.URLConnection;


/**
 * This is the Multi (MP3/AAC) Stream player class.
 * It uses Decoder to decode Multi stream into PCM samples.
 * This class is not thread safe.
 * <pre>
 *  MultiPlayer player = new MultiPlayer();
 *
 *  String url = ...;
 *  player.playAsync( url );
 * </pre>
 */
public class MultiPlayer extends AACPlayer {

    private static final String LOG = "MultiPlayer";


    ////////////////////////////////////////////////////////////////////////////
    // Attributes
    ////////////////////////////////////////////////////////////////////////////

    private Decoder aacDecoder;
    private Decoder mp3Decoder;


    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Creates a new player.
     */
    public MultiPlayer() {
        this( null );
    }


    /**
     * Creates a new player.
     * @param playerCallback the callback, can be null
     */
    public MultiPlayer( PlayerCallback playerCallback ) {
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
    public MultiPlayer( PlayerCallback playerCallback, int audioBufferCapacityMs, int decodeBufferCapacityMs ) {
        super( playerCallback, audioBufferCapacityMs, decodeBufferCapacityMs );
    }


    ////////////////////////////////////////////////////////////////////////////
    // Protected
    ////////////////////////////////////////////////////////////////////////////

    @Override
    protected Decoder createDecoder() {
        aacDecoder = super.createDecoder();

        String name = "OpenCORE-MP3";

        mp3Decoder = Decoder.createByName( name );

        if (mp3Decoder == null) {
            Log.e( LOG, "Cannot find decoder by name '" + name + "'");
            throw new RuntimeException("MP3 Decoder not found");
        }

        return aacDecoder;
    }


    @Override
    protected void processHeaders( URLConnection cn ) {
        super.processHeaders( cn );

        for (java.util.Map.Entry<String, java.util.List<String>> me : cn.getHeaderFields().entrySet()) {
            if ("content-type".equalsIgnoreCase( me.getKey())) {
                for (String s : me.getValue()) {
                    String ct = s;

                    if (!s.startsWith( "audio/" )) {
                        Log.w( LOG, "Content type not audio: " + s ); 
                        continue;
                    }

                    s = s.substring( "audio/".length());
                    if (s.startsWith( "x-" )) s = s.substring( "x-".length());

                    // MP3: audio/mpeg, audio/x-mpeg, audio/mp3, audio/x-mp3,
                    //      audio/mpeg3, audio/x-mpeg3, audio/mpg, audio/x-mpg, audio/x-mpegaudio
                    boolean isMp3 = s.startsWith( "mp3" )
                        || s.startsWith( "mpeg" )
                        || s.startsWith( "mpg" );

                    Log.i( LOG, "Setting " + (isMp3 ? "MP3" : "AAC") + " decoder for content type " + ct );
                    setDecoder( isMp3 ? mp3Decoder : aacDecoder );

                    return;
                }
                Log.w( LOG, "Content type not recognized" );
            }
        }

        Log.e( LOG, "Could not recognize the type of the stream." );
        throw new RuntimeException( "Could not recognize the type of the stream." );
    }


    /**
     * This method is called before opening the file.
     * Detects the file type - according to the suffix.
     */
    @Override
    protected void processFileType( String file ) {
        boolean isMp3 = file.toLowerCase().endsWith( ".mp3" );

        Log.i( LOG, "Setting " + (isMp3 ? "MP3" : "AAC") + " decoder for file " + file );
        setDecoder( isMp3 ? mp3Decoder : aacDecoder );
    }

}

