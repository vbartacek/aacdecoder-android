/* 
    FlashAACInputStream - provides an InputStream for use with FlashAACPlayer within aacdecoder-android.
    Allows reading of FLV-wrapped raw AAC data into playable buffers of AAC frames with ADTS headers

    20-09-2011
    Author: Trevor Lovett (trevlovett (at) gmail.com)
    Based in part upon FLV_Extract (http://moitah.net/)
*/

package com.spoledge.aacdecoder;

import android.util.Log;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;

public class FlashAACInputStream extends InputStream {
    private DataInputStream dis = null;
    private int countInBackBuffer = 0;
    private int backBufferLen = 65536;
    private byte[] backBuffer = new byte[backBufferLen];
    private int readBufferLen = 65536;
    private byte[] readBuffer = new byte[readBufferLen];

    private int _aacProfile;
    private int _sampleRateIndex;
    private int _channelConfig;

    public FlashAACInputStream(InputStream istream) throws IOException {
        dis = new DataInputStream(istream);
        // Check that stream is a Flash Video stream
        if ((char)dis.readByte() != 'F' || (char)dis.readByte() != 'L' || (char)dis.readByte() != 'V')
            throw new IOException("The file is not a FLV file.");

        // Check if audio stream exists in the video stream
        byte version = dis.readByte();
        byte exists = dis.readByte();

        if ((exists != 5) && (exists != 4))
            throw new IOException("No Audio Stream");

        dis.readInt(); // data offset of header. ignoring
    }

    // don't use-- efficiency is not good
    @Override
    public int read() throws IOException {
        byte[] b = new byte[1];
        read(b, 0, 1);
        return ((int)b[0]) & 0xFF;
    }

    // Reads a frame at a time.  If the entire frame cannot be accomodated by b,
    // function saves the remainder in backBuffer for use in next call.
    // returns: number of bytes read into b

    @Override
    public int read(byte[] b, int off, int len) throws IOException {
        if (off < 0 || len < 0 || b.length - off < len)
            throw new IndexOutOfBoundsException();

        if (len > readBufferLen) 
            throw new IndexOutOfBoundsException("len exceeds readBufferLen");

        Log.d("FlashAACInputStream", "read: countInBackBuffer = " + countInBackBuffer);

        if (countInBackBuffer > 0) {
            if (countInBackBuffer >= len) {
                System.arraycopy(backBuffer, 0, b, off, len);

                // move the remainder in the backBuffer to the top
                if (countInBackBuffer > len) 
                    System.arraycopy(backBuffer, len, backBuffer, 0, countInBackBuffer - len);

                countInBackBuffer -= len;
                return len;
            }
            else {
                System.arraycopy(backBuffer, 0, b, off, countInBackBuffer);
            }
        }

        int remaining = len - countInBackBuffer;
        int readBytes = 0;
        int b_off = off + countInBackBuffer;
        
        countInBackBuffer = 0;

        while (true) {
            readBytes = readFrame(readBuffer);
            remaining -= readBytes;

            if (remaining <= 0) {
                System.arraycopy(readBuffer, 0, b, b_off, readBytes + remaining);
                if (remaining < 0)  {
                    System.arraycopy(readBuffer, readBytes + remaining, backBuffer, 0, Math.abs(remaining));
                    countInBackBuffer = Math.abs(remaining);
                }
                return len;
            }
            else if (remaining > 0) {
                System.arraycopy(readBuffer, 0, b, b_off, readBytes);
                b_off += readBytes;
            }
        }
    }

    // reads FLV Tag data
    private int readFrame(byte[] buf) throws IOException {
        int previousTagSize = dis.readInt(); // PreviousTagSize0 skipping

        byte tagType = dis.readByte();
        while (tagType != 8) {
            long skip = readNext3Bytes() + 11;
            dis.skipBytes((int)skip);

            tagType = dis.readByte();
        }

        long dataSize = readNext3Bytes() - 1;
        int timestamps = dis.readInt();
        long streamID = readNext3Bytes();
        byte audioHeader = dis.readByte();
        Log.d("FlashAACInputStream", "dataSize = " + dataSize + ", timestamps = " + timestamps + ", streamId = " + streamID + ", audioHeader = " + audioHeader);

        return fillBuffer(buf, (int)dataSize);
    }

    // returns true if header present, false if not
    private boolean readAACHeader() throws IOException {
        byte head = dis.readByte();
        if (head != 0) return false;

        int bits = ((dis.readByte() & 0xff)*256 + (dis.readByte() & 0xff)) << 16;

        _aacProfile = readBits(bits, 5) - 1;
        bits <<= 5;
        _sampleRateIndex = readBits(bits, 4);
        bits <<= 4;
        _channelConfig = readBits(bits, 4);
    
        Log.d("FlashAACInputStream", "aacProf = " + _aacProfile);
        Log.d("FlashAACInputStream", "_sampleRateIndex = " + _sampleRateIndex);
        Log.d("FlashAACInputStream", "_channelConfig = " + _channelConfig);

        if ((_aacProfile < 0) || (_aacProfile > 3))
            throw new IOException("Unsupported AAC profile.");
        if (_sampleRateIndex > 12)
            throw new IOException("Invalid AAC sample rate index.");
        if (_channelConfig > 6)
            throw new IOException("Invalid AAC channel configuration.");

        return true;
    }

    // puts a complete AAC frame with ADTS header in buf, ready for playing, returns size of frame in bytes
    private int fillBuffer(byte[] buf, int dataSize) throws IOException {
        if (readAACHeader()) return 0;

        dataSize -= 1;

        // see http://wiki.multimedia.cx/index.php?title=ADTS for format spec
        long bits = 0;
        bits = writeBits(bits, 12, 0xFFF);
        bits = writeBits(bits, 3, 0);
        bits = writeBits(bits, 1, 1);

        buf[0] = (byte)(bits >> 8);
        buf[1] = (byte)(bits);

        bits = 0;
        bits = writeBits(bits, 2, _aacProfile);
        bits = writeBits(bits, 4, _sampleRateIndex);
        bits = writeBits(bits, 1, 0);
        bits = writeBits(bits, 3, _channelConfig); 
        bits = writeBits(bits, 4, 0);
        bits = writeBits(bits, 2, (dataSize + 7) & 0x1800);

        buf[2] = (byte)(bits >> 8);
        buf[3] = (byte)(bits);
        
        bits = 0;
        bits = writeBits(bits, 11, (dataSize + 7) & 0x7FF);
        bits = writeBits(bits, 11, 0x7FF);
        bits = writeBits(bits, 2, 0);
        buf[4] = (byte)(bits >> 16);
        buf[5] = (byte)(bits >> 8);
        buf[6] = (byte)(bits);

        dis.readFully(buf, 7, dataSize);
        buf[dataSize+7] = 0;

        return dataSize + 8;
    }
 
    private int readBits(int x, int length) {
        int r = (int)(x >> (32 - length));
        return r;
    }

    public long writeBits(long x, int length, int value) {
        long mask = 0xffffffffL >> (32 - length);
        x = (x << length) | (value & mask);
        return x;
    }

    private long readNext3Bytes() throws IOException {
        return dis.readUnsignedByte() * 256 * 256 + dis.readUnsignedByte() * 256 + dis.readUnsignedByte();
    }

    protected static void dumpHeaders( URLConnection cn ) {
        for (java.util.Map.Entry<String, java.util.List<String>> me : cn.getHeaderFields().entrySet()) {
            for (String s : me.getValue()) {
                System.out.println("header: key=" + me.getKey() + ", val=" + s);
            }
        }
    }

    // simple unit test to see if it can read from a file or network stream
    public static void main(String args[]) {
        try {
            /*
            File f = new File(args[0]);
            FileInputStream fis = new FileInputStream(f);
            FlashAACInputStream aacStream = new FlashAACInputStream(fis);
           */
           
            // static file on server
            String url = "http://184.82.135.71/download.flv";

            // true stream URL
            //String url = "http://184.82.135.71:450";

            URLConnection cn = new URL( url ).openConnection();
            cn.connect();
            dumpHeaders( cn );
            InputStream istream = cn.getInputStream();
            FlashAACInputStream flvStream = new FlashAACInputStream(istream);

            File outFile = new File("output.aac");
            FileOutputStream fos = new FileOutputStream(outFile);
            DataOutputStream dos = new DataOutputStream(fos);

            byte [] myChunk = new byte[4096];
            int bytesRead;
            for (int i = 0; i < 100; i++) {
                bytesRead = flvStream.readFrame(myChunk);
                System.out.println("bytesRead = " + bytesRead);
                fos.write(myChunk, 0, bytesRead);
            }
            fos.close();
        } catch (Exception e) {
            System.out.println(e);
            e.printStackTrace();
        }
    }
}
