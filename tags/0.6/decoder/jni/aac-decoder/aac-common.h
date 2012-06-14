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

#ifndef AAC_COMMON_H
#define AAC_COMMON_H

#include <jni.h>
#include <android/log.h>

#ifndef AACD_MODULE
#error "Please specify AACD_MODULE at the top of your file."
#endif


#ifdef AACD_LOGLEVEL_TRACE
#define AACD_TRACE(...) \
    __android_log_print(ANDROID_LOG_VERBOSE, AACD_MODULE, __VA_ARGS__)
#else
#define AACD_TRACE(...) //
#endif

#ifdef AACD_LOGLEVEL_DEBUG
#define AACD_DEBUG(...) \
    __android_log_print(ANDROID_LOG_DEBUG, AACD_MODULE, __VA_ARGS__)
#else
#define AACD_DEBUG(...) //
#endif

#ifdef AACD_LOGLEVEL_INFO
#define AACD_INFO(...) \
    __android_log_print(ANDROID_LOG_INFO, AACD_MODULE, __VA_ARGS__)
#else
#define AACD_INFO(...) //
#endif

#ifdef AACD_LOGLEVEL_WARN
#define AACD_WARN(...) \
    __android_log_print(ANDROID_LOG_WARN, AACD_MODULE, __VA_ARGS__)
#else
#define AACD_WARN(...) //
#endif

#ifdef AACD_LOGLEVEL_ERROR
#define AACD_ERROR(...) \
    __android_log_print(ANDROID_LOG_ERROR, AACD_MODULE, __VA_ARGS__)
#else
#error "Ha AACD_LOGLEVEL_ERROR is not defined"
#define AACD_ERROR(...) //
#endif


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Common info struct used for storing info between calls.
 */
typedef struct AACDInfo {

    /**
     * The decoder.
     */
    struct AACDDecoder *decoder;

    /**
     * The input buffer reader object.
     */
    jobject *reader;

    /**
     * The last known JNIEnv.
     */
    JNIEnv *env;

    /**
     * The callback variable - Decoder.Info.
     */
    jobject *aacInfo;

    /**
     * Extended info - each decoder can use it for its own purposes:
     */
    void *ext;

    // internal input buffer - 2x
    unsigned char *buffer_block;
    unsigned long bbsize;
    unsigned char *buffer_block2;
    unsigned long bbsize2;

    // input buffer pointer:
    unsigned char *buffer;
    unsigned long bytesleft;

    // internal output buffer
    jshort *samples;
    unsigned long samplesLen;

    // start() function will fill these:
    unsigned long samplerate;
    unsigned char channels;

    // decode() function will fill these:
    unsigned long frame_bytesconsumed;
    unsigned long frame_samples;

    // max statistics allowing to predict when to finish decoding:
    unsigned long frame_max_bytesconsumed;
    unsigned long frame_max_bytesconsumed_exact;

    // filled after each decoding round
    unsigned long round_frames;
    unsigned long round_bytesconsumed;
    unsigned long round_samples;

} AACDInfo;


/**
 * Decoder definition.
 */
typedef struct AACDDecoder {
    /**
     * Returns the name of the decoder.
     */
    const char* (*name)();

    /**
     * Initializes the decoder.
     * @return optionally pointer to decoder's internal structure
     */
    void* (*init)();

    /**
     * Start decoding.
     * Must fill at least sampleRate and number of channels (AACDInfo).
     * @return either positive = number of bytes consumed; negative means an error code.
     */
    long (*start)( AACDInfo*, unsigned char*, unsigned long);

    /**
     * Decodes one frame.
     * @return 0=OK, otherwise error.
     */
    int (*decode)( AACDInfo*, unsigned char *, unsigned long, jshort*, jint);

    /**
     * Destroys the decoder - the decoder should free all resources.
     */
    void (*destroy)( AACDInfo* );

    /**
     * Searches for ADTS 0xfff header. Can be null - the default sync func is used.
     * Returns the offset of ADTS frame.
     * @return either positive = number of bytes consumed; negative means an error code.
     */
    int (*sync)( AACDInfo*, unsigned char *, int );

} AACDDecoder;


/**
 * Searches for ADTS 0xfff header.
 * Returns the offset of ADTS frame.
 */
int aacd_adts_sync(unsigned char *buffer, int len);


#ifdef __cplusplus
}
#endif
#endif
