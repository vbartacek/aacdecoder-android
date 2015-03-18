# System Requirements #

  * Android SDK - at least platform 3 (Android 1.5)
  * Android NDK - at least rev 6 (tested with 9c)
  * (Apache Ant - http://ant.apache.org/)
  * (Maven)


# Getting Android OpenCORE Sources #

You have to download Android OpenCORE sources either by:
  * downloading OpenCORE sources from the _Downloads_ tab (file android-opencore-20120628-patch-stereo.zip)
  * checking-out Android OpenCORE sources from the Androids repository: http://android.git.kernel.org
    * unfortunately this was working in summer 2011, but there is not an easy way how to download pure OpenCORE module now (spring 2012)
    * If anybody can provide me the full sources (OpenCORE only) I would appreciate it

  * checking-out OpenCORE aacdec sources from the original project:
http://code.google.com/p/opencore-aacdec/

If you download a zip file, then please unzip it somewhere.


# Compiling #

  1. copy sample.ant.properties to .ant.properties and edit .ant.properties:
    * path to Android SDK
    * path to Android NDK
    * path to Android OpenCORE sources (which you have downloaded from the _Downloads_ tab and unzipped)
  1. run ant
  1. use the libraries and/or the APK:
    * install the APK on the emulator or a device: adb install player/bin/AACMusicPlayer-debug.apk
    * the Java and shared libraries you find in decoder/libs

# Using Maven #

Starting with the version 0.7 the project can be built using Maven.

**NOTE:** You have to configure the .ant.properties to point to the OpenCORE
sources (see above). But do not mix using of Ant and Maven ! Be sure that the
working directory is clean before switching the tools. So if you used Ant in past,
then do the following:

```
    $ ant mrproper
```

You must install Android 1.5\_r4 into your Maven repository.
Please see https://code.google.com/p/maven-android-plugin/ how to use
Maven for Android projects.

When you have you maven for Android ready, then just do:

```
    $ mvn install
```

Then start an emulator or attach a device, go to the "decoder" dir
and run:

```
    $ mvn android:deploy
```

Using the apklib by other projects is as easy as the demo "player"
is using it (see the player/pom.xml):

```
    <dependencies>
        <dependency>
            <groupId>com.spoledge.aacdecoder</groupId>
            <artifactId>aacdecoder-lib</artifactId>
            <version>0.7</version>
            <type>apklib</type>
        </dependency>
    </dependencies>
```