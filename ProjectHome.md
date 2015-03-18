# Freeware Advanced Audio (AAC) Decoder for Android #
http://www.spoledge.com

This is a follow-up project of [aacplayer-android](http://code.google.com/p/aacplayer-android/) which focuses on the decoding part using external library OpenCORE aacdec.

This project was written for those developers spending hours of googling the internet to answer a simple question:
> How to make Android to **play raw AAC files (streams)** ?

This is a port of the [OpenCORE aacdec](http://code.google.com/p/opencore-aacdec/) open source library to Android platform. OpenCORE aacdec is licensed under the [Apache License, Version 2.0](http://www.apache.org/licenses/) and its source can be downloaded [here](http://code.google.com/p/aacdecoder-android/downloads/list).
For more information about OpenCORE aacdec, please visit http://code.google.com/p/opencore-aacdec/

This library allows to play AAC, AAC+ and HE-AAC+ streams on Android devices.

**PLEASE NOTE**
that the use of this software may require the payment of
patent royalties. You need to consider this issue before you start
building derivative works. We are not warranting or indemnifying you in
any way for patent royalities! YOU ARE SOLELY RESPONSIBLE FOR YOUR OWN
ACTIONS!

For more information about the AAC patents, please visit
http://www.vialicensing.com/licensing/aac-fees.aspx


---

## Project Overview ##

The project contains two modules - **decoder** and **player**.

The "decoder" module contains the Java and C code used for wrapping
the underlying AAC decoding algorithm (which is currently the OpenCORE aacdec,
but it could be easily changed). Since the version 0.6 also MP3 streams are supported.

The "player" module is an example how to use the "decoder" library in your
project.


---

## Using the Library ##

You can use the library in your own Android projects. To do so, download the compiled AACDecoder library from the "Downloads" tab and copy the content to your Android project's "libs" directory. Then you can use the Java API of the AACDecoder.

The simplest way how to play AAC streams:
```
import com.spoledge.aacdecoder.AACPlayer;
...
AACPlayer aacPlayer = new AACPlayer();
aacPlayer.playAsync( "http://..." );
```

Also you can register a callback object to get information about the playing status:
```
import com.spoledge.aacdecoder.AACPlayer;
import com.spoledge.aacdecoder.PlayerCallback;
...
PlayerCallback clb = new PlayerCallback() {
    public void playerStarted() { ... }
    public void playerPCMFeedBuffer(boolean isPlaying, int bufSizeMs, int bufCapacityMs) {...}
    public void playerStopped( int perf ) { ... }
    public void playerException( Throwable t) { ... }
    public void playerMetadata( String key, String value ) { ... }
};

AACPlayer aacPlayer = new AACPlayer( clb );
aacPlayer.playAsync( "http://..." );
```

Or you can play both AAC and MP3 streams using MultiPlayer class:
```
import com.spoledge.aacdecoder.MultiPlayer;
import com.spoledge.aacdecoder.PlayerCallback;
...
PlayerCallback clb = new PlayerCallback() { ... };
MultiPlayer aacMp3Player = new MultiPlayer( clb );
aacMp3Player.playAsync( "http://..." ); // URL of MP3 or AAC stream
```

If you want to play Shoutcast streams (those returning "ICY" instead of "HTTP/1.x" response), then you must also register the "icy" protocol prefix in JVM once before you open a stream (see HandlingShoutcastStreams):
```
    try {
        java.net.URL.setURLStreamHandlerFactory( new java.net.URLStreamHandlerFactory(){
            public java.net.URLStreamHandler createURLStreamHandler( String protocol ) {
                Log.d( LOG, "Asking for stream handler for protocol: '" + protocol + "'" );
                if ("icy".equals( protocol )) return new com.spoledge.aacdecoder.IcyURLStreamHandler();
                return null;
            }
        });
    }
    catch (Throwable t) {
        Log.w( LOG, "Cannot set the ICY URLStreamHandler - maybe already set ? - " + t );
    }
```

For more complex example please look at a simple player - [AACPlayerActivity.java](http://code.google.com/p/aacdecoder-android/source/browse/trunk/player/src/com/spoledge/aacplay/AACPlayerActivity.java).


---

