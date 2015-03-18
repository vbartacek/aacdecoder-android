# Release Notes #


---


## 2014-01-12 Version 0.8 ##

  * improved start/stop of the AACPlayer
    * streams/files are fully played since now
    * "start" function uses "icy-br" header for bitrate estimation
    * "stop" function stops playing sounds immediatelly
    * see also [issue 41](https://code.google.com/p/aacdecoder-android/issues/detail?id=41) and [issue 32](https://code.google.com/p/aacdecoder-android/issues/detail?id=32) for more information

  * fixed [issue 32](https://code.google.com/p/aacdecoder-android/issues/detail?id=32) - small files cannot be played / are truncated

  * writing dummy PCM data to the `AudioTrack`, but stopping playback just before it

  * fixed [issue 37](https://code.google.com/p/aacdecoder-android/issues/detail?id=37) - http/shoutcast response code checking
    * unified conneciton workflow for pre-Kitkat and Kitkat devices
    * backward compatibility option added to AACPlayer (no reconnection needed for pre-Kitkat devices)

  * fixed [issue 41](https://code.google.com/p/aacdecoder-android/issues/detail?id=41) - some data is lost - media is shorter
    * the first decoded frame is also played (both AAC and MP3)
    * the end of the file is played - waiting  until "the last tone"

  * fixed [issue 44](https://code.google.com/p/aacdecoder-android/issues/detail?id=44) - shoutcast streams on Andorid 4.4 Kitkat
    * provided IcyURLStreamHandler and added it to the demo
    * reconnecting to the shoutcastserver using IcyURLConnection ("icy" protocol)
    * shoutcats streams can be directly played using "icy://" URLs


---


## 2013-12-29 Version 0.7 ##

  * Maven can be used for building the code

  * fixed [issue 8](https://code.google.com/p/aacdecoder-android/issues/detail?id=8) - disconnection after stop
    * closing resources

  * fixed [issue 14](https://code.google.com/p/aacdecoder-android/issues/detail?id=14) - `AudioTrack` can be accessed by caller
    * a new method in `PlayerCallback` - playerAudioTrackCreated

  * fixed [issue 22](https://code.google.com/p/aacdecoder-android/issues/detail?id=22) - supporting other available archs (x86, mips)

  * fixed [issue 23](https://code.google.com/p/aacdecoder-android/issues/detail?id=23) - MP3 stream not starting time to time
    * rewritten native C decode loop

  * fixed [issue 31](https://code.google.com/p/aacdecoder-android/issues/detail?id=31) - better exception handling
    * detecting invalid sample rate

  * fixed [issue 33](https://code.google.com/p/aacdecoder-android/issues/detail?id=33) - metadata encoding
    * added option for setting character encoding for metadata


---


## 2012-06-28 Version 0.6.1 ##

  * fixed [issue 13](https://code.google.com/p/aacdecoder-android/issues/detail?id=13) - HE-AAC+ streams crashing
    * fixed Parametric Stereo initialization in the OpenCORE lib (PS enabled again)


---


## 2012-06-14 Version 0.6 ##

  * using "new" OpenCORE library - both AAC and MP3 codecs included

  * fixed [issue 16](https://code.google.com/p/aacdecoder-android/issues/detail?id=16) - exception in onPeriodicNotification

  * FlashAACInputStream


---


## 2011-07-26 Version 0.5.1 ##

  * fixed [issue 1](https://code.google.com/p/aacdecoder-android/issues/detail?id=1) - aacd\_probe

  * fixed [issue 6](https://code.google.com/p/aacdecoder-android/issues/detail?id=6) - crash when starting
    * Parametric Stereo disabled


---


## 2011-05-26 Version 0.5 ##

  * initial import of the project based on aacplayer-android