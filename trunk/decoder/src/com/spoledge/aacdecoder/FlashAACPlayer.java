package com.spoledge.aacdecoder;

import com.spoledge.aacdecoder.FlashAACInputStream;

import android.util.Log;

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.IOException;

import java.net.URL;
import java.net.URLConnection;

public class FlashAACPlayer extends AACPlayer {
    private InputStream istream = null;

    public FlashAACPlayer() {
        this( null );
    }

    /**
     * Creates a new player.
     * @param playerCallback the callback, can be null
     */
    public FlashAACPlayer( PlayerCallback playerCallback ) {
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
    public FlashAACPlayer( PlayerCallback playerCallback, int audioBufferCapacityMs, int decodeBufferCapacityMs ) {
        setPlayerCallback( playerCallback );
        setAudioBufferCapacityMs( audioBufferCapacityMs );
        setDecodeBufferCapacityMs( decodeBufferCapacityMs );

        decoder = createDecoder();
    }

    /** 
     * Plays a stream synchronously. 
     * @param url the URL of the stream or file 
     * @param expectedKBitSecRate the expected average bitrate in kbit/sec; -1 means unknown 
     */ 
    public void play( String url, int expectedKBitSecRate ) throws Exception { 
        if (url.indexOf( ':' ) > 0) { 
            URLConnection cn = new URL( url ).openConnection(); 
            cn.connect(); 
 
            dumpHeaders( cn ); 
            istream = cn.getInputStream();
            FlashAACInputStream flvStream = new FlashAACInputStream(istream);

            // TODO: try to get the expectedKBitSecRate from headers 
            play(flvStream, expectedKBitSecRate); 
        } 
        else play( new FileInputStream( url ), expectedKBitSecRate ); 
    }
}
