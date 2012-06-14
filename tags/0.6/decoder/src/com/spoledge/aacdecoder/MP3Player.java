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


/**
 * This is the MP3 Stream player class.
 * It uses Decoder to decode MP3 stream into PCM samples.
 * This class is not thread safe.
 * <pre>
 *  MP3Player player = new MP3Player();
 *
 *  String url = ...;
 *  player.playAsync( url );
 * </pre>
 */
public class MP3Player extends AACPlayer {

    private static final String LOG = "MP3Player";


    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Creates a new player.
     */
    public MP3Player() {
        this( null );
    }


    /**
     * Creates a new player.
     * @param playerCallback the callback, can be null
     */
    public MP3Player( PlayerCallback playerCallback ) {
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
    public MP3Player( PlayerCallback playerCallback, int audioBufferCapacityMs, int decodeBufferCapacityMs ) {
        super( playerCallback, audioBufferCapacityMs, decodeBufferCapacityMs );
    }


    ////////////////////////////////////////////////////////////////////////////
    // Protected
    ////////////////////////////////////////////////////////////////////////////

    @Override
    protected Decoder createDecoder() {
        String name = "OpenCORE-MP3";

        Decoder ret = Decoder.createByName( name );

        if (ret == null) {
            Log.e( LOG, "Cannot find decoder by name '" + name + "'");
            throw new RuntimeException("MP3 Decoder not found");
        }

        return ret;
    }

}

