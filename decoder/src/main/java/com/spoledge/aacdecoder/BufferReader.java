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

import java.io.InputStream;
import java.io.IOException;


/**
 * This is a separate thread for reading data from a stream.
 * The buffer creates 3 buffer instances - one is being filled by the execution thread,
 * one is prepared with data, one can be processed by a consumer.
 * <pre>
 *  InputStream is = ...;
 *
 *  // create a new reader with capacity of 4096 bytes per buffer:
 *  BufferReader reader = new BufferReader( 4096, is );
 *
 *  // start the execution thread which reads the stream and fills the buffers:
 *  new Thread(reader).start();
 *
 *  // get the data
 *  while (...) {
 *      BufferReader.Buffer buf = reader.next();
 *
 *      if (!buf.getSize() == 0) break;
 *
 *      // process data
 *      ...
 *  }
 * </pre>
 */
public class BufferReader implements Runnable {

    public static class Buffer {
        private byte[] data;
        private int size;

        Buffer( int capacity ) {
            data = new byte[ capacity ];
        }

        public final byte[] getData() {
            return data;
        }

        public final int getSize() {
            return size;
        }
    }

    private static String LOG = "BufferReader";

    int capacity;

    private Buffer[] buffers;

    /**
     * The buffer to be write into.
     */
    private int indexMine;

    /**
     * The index of the buffer last returned in the next() method.
     */
    private int indexBlocked;

    private boolean stopped;

    private InputStream is;


    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Creates a new buffer.
     *
     * @param capacity the capacity of one buffer in bytes
     *          = total allocated memory
     *
     * @param is the input stream
     */
    public BufferReader( int capacity, InputStream is ) {
        this.capacity = capacity;
        this.is = is;

        Log.d( LOG, "init(): capacity=" + capacity );

        buffers = new Buffer[3];

        for (int i=0; i < buffers.length; i++) {
            buffers[i] = new Buffer( capacity );
        }

        indexMine = 0;
        indexBlocked = buffers.length-1;
    }


    ////////////////////////////////////////////////////////////////////////////
    // Public
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Changes the capacity of the buffer.
     */
    public synchronized void setCapacity( int capacity ) {
        Log.d( LOG, "setCapacity(): " + capacity );
        this.capacity = capacity;
    }


    /**
     * The main loop.
     */
    public void run() {
        Log.d( LOG, "run() started...." );

        int cap = capacity;
        int total = 0;

        while (!stopped) {
            Buffer buffer = buffers[ indexMine ];
            total = 0;

            if (cap != buffer.data.length) {
                Log.d( LOG, "run() capacity changed: " + buffer.data.length + " -> " + cap);
                buffers[ indexMine ] = buffer = null;
                buffers[ indexMine ] = buffer = new Buffer( cap );
            }

            while (!stopped && total < cap) {
                try {
                    int n = is.read( buffer.data, total, cap - total );

                    if (n == -1) stopped = true;
                    else total += n;
                }
                catch (IOException e) {
                    Log.e( LOG, "Exception when reading: " + e );
                    stopped = true;
                }
            }

            buffer.size = total;

            synchronized (this) {
                notify();
                int indexNew = (indexMine + 1) % buffers.length;

                while (!stopped && indexNew == indexBlocked) {
                    //Log.d( LOG, "run() waiting...." );
                    try { wait(); } catch (InterruptedException e) {}
                    //Log.d( LOG, "run() awaken" );
                }

                indexMine = indexNew;
                cap = capacity;
            }
        }

        Log.d( LOG, "run() stopped." );
    }


    /**
     * Stops the thread - the object cannot be longer used.
     */
    public synchronized void stop() {
        stopped = true;
        notify();
    }


    /**
     * Returns true if this thread was stopped.
     */
    public boolean isStopped() {
        return stopped;
    }


    /**
     * Returns next available buffer instance.
     * The returned instance can be freely used by another thread.
     * Blocks the caller until a buffer is ready.
     */
    public synchronized Buffer next() {
        int indexNew = (indexBlocked + 1) % buffers.length;

        while (!stopped && indexNew == indexMine) {
            Log.d( LOG, "next() waiting...." );
            try { wait(); } catch (InterruptedException e) {}
            Log.d( LOG, "next() awaken" );
        }

        if (indexNew == indexMine) return null;

        indexBlocked = indexNew;

        notify();

        return buffers[ indexBlocked ]; 
    }

}

