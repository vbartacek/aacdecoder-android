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

#define AACD_MODULE "Decoder"

#include "aac-decoder.h"
#include "aac-common.h"

#include <string.h>

/****************************************************************************************************
 * STRUCTS
 ****************************************************************************************************/

struct JavaDecoderInfo {
    jclass clazz;
    jfieldID sampleRate;
    jfieldID channels;
    jfieldID frameMaxBytesConsumed;
    jfieldID frameSamples;
    jfieldID roundFrames;
    jfieldID roundBytesConsumed;
    jfieldID roundSamples;
};

struct JavaArrayBufferReader {
    jclass bufferClazz;
    jfieldID bufferData;
    jfieldID bufferSize;
    jclass clazz;
    jmethodID next;
};

static struct JavaArrayBufferReader javaABR;
static struct JavaDecoderInfo javaDecoderInfo;

extern AACDDecoder aacd_opencore_decoder;
extern AACDDecoder aacd_opencoremp3_decoder;

#define AACD_DECODERS_COUNT 2
static struct AACDDecoder* aacd_decoders[AACD_DECODERS_COUNT] = { &aacd_opencore_decoder, &aacd_opencoremp3_decoder };


/****************************************************************************************************
 * FUNCTIONS
 ****************************************************************************************************/

/**
 * Searches for ADTS 0xfff header.
 * Returns the offset of ADTS frame.
 */
int aacd_adts_sync(unsigned char *buffer, int len)
{
    int pos = 0;
    len -= 3;

    AACD_TRACE( "probe() start len=%d", len );

    while (pos < len)
    {
        if (*buffer != 0xff)
        {
            buffer++;
            pos++;
        }
        else if ((*(++buffer) & 0xf6) == 0xf0)
        {
            AACD_TRACE( "probe() found ADTS start at offset %d", pos );
            return pos;
        }
        else pos++;
    }

    AACD_WARN( "probe() could not find ADTS start" );

    return -1;
}


/**
 * Copies relevant information to Java object.
 * This is called in the start method.
 */
static void aacd_start_info2java( AACDInfo *info )
{
    JNIEnv *env = info->env;
    jobject jinfo = info->aacInfo;

    if (javaDecoderInfo.clazz == NULL)
    {
        AACD_TRACE( "aacd_start_info2java() - caching Java reflection" );
        javaDecoderInfo.clazz = (jclass) (*env)->GetObjectClass( env, jinfo );
        javaDecoderInfo.sampleRate = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "sampleRate", "I");
        javaDecoderInfo.channels = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "channels", "I");
        javaDecoderInfo.frameMaxBytesConsumed = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "frameMaxBytesConsumed", "I");
        javaDecoderInfo.frameSamples = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "frameSamples", "I");
        javaDecoderInfo.roundFrames = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "roundFrames", "I");
        javaDecoderInfo.roundBytesConsumed = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "roundBytesConsumed", "I");
        javaDecoderInfo.roundSamples = (jfieldID) (*env)->GetFieldID( env, javaDecoderInfo.clazz, "roundSamples", "I");
    }

    AACD_TRACE( "aacd_start_info2java() - storing info sampleRate=%d, channels=%d",
            info->samplerate, info->channels );

    (*env)->SetIntField( env, jinfo, javaDecoderInfo.sampleRate, (jint) info->samplerate);
    (*env)->SetIntField( env, jinfo, javaDecoderInfo.channels, (jint) info->channels);

    AACD_TRACE( "aacd_start_info2java() - finished" );
}


/**
 * Copies relevant information to Java object.
 * This is called in the decode method.
 */
static void aacd_decode_info2java( AACDInfo *info )
{
    AACD_TRACE( "aacd_decode_info2java() - storing info frameMaxBytesConsumed=%d, frameSamples=%d, roundFrames=%d, roundBytesConsumed=%d, roundSamples=%d",
            info->frame_max_bytesconsumed, info->frame_samples,
            info->round_frames, info->round_bytesconsumed, info->round_samples );

    JNIEnv *env = info->env;
    jobject jinfo = info->aacInfo;

    (*env)->SetIntField( env, jinfo, javaDecoderInfo.frameMaxBytesConsumed, (jint) info->frame_max_bytesconsumed);
    (*env)->SetIntField( env, jinfo, javaDecoderInfo.frameSamples, (jint) info->frame_samples);
    (*env)->SetIntField( env, jinfo, javaDecoderInfo.roundFrames, (jint) info->round_frames);
    (*env)->SetIntField( env, jinfo, javaDecoderInfo.roundBytesConsumed, (jint) info->round_bytesconsumed);
    (*env)->SetIntField( env, jinfo, javaDecoderInfo.roundSamples, (jint) info->round_samples);

    AACD_TRACE( "aacd_decode_info2java() - finished" );
}


/****************************************************************************************************
 * FUNCTIONS - Buffers
 ****************************************************************************************************/

/**
 * Starts the service - initializes resource.
 */
static AACDInfo* aacd_start( JNIEnv *env, AACDDecoder *decoder, jobject jreader, jobject aacInfo)
{
    AACD_INFO( "start() starting native decoder - %s", decoder->name());

    AACDInfo *info = (AACDInfo*) calloc( 1, sizeof( struct AACDInfo ));

    info->decoder = decoder;

    info->ext = info->decoder->init();

    info->reader = (*env)->NewGlobalRef( env, jreader );
    info->aacInfo = (*env)->NewGlobalRef( env, aacInfo );

    return info;
}


/**
 * Stops the service and frees resources.
 */
static void aacd_stop( AACDInfo *info )
{
    AACD_INFO( "stop() stopping native decoder" );

    if (info == NULL) return;

    if (info->decoder) info->decoder->destroy( info );

    if (info->buffer_block != NULL)
    {
        free( info->buffer_block );
        info->buffer_block = NULL;
        info->bbsize = 0;
    }

    if (info->buffer_block2 != NULL)
    {
        free( info->buffer_block2 );
        info->buffer_block = NULL;
        info->bbsize2 = 0;
    }

    if (info->samples != NULL)
    {
        free( info->samples );
        info->samplesLen = 0;
    }

    JNIEnv *env = info->env;

    if (info->aacInfo) (*env)->DeleteGlobalRef( env, info->aacInfo );
    if (info->reader) (*env)->DeleteGlobalRef( env, info->reader );

    free( info );
}


/**
 * Prepares input buffer by joining the rest of the old one and the new one.
 */
static unsigned char* aacd_prepare_buffer( AACDInfo *info, jbyteArray inBuf, jint inOff, jint inLen )
{
    int newlen = info->bytesleft + inLen;

    if (info->bbsize2 < newlen) 
    {
        if (info->buffer_block2 != NULL) free( info->buffer_block2 );

        int realsize = newlen + 500; // avoid realocating by one or two bytes only

        info->buffer_block2 = (unsigned char*) malloc( realsize );
        info->bbsize2 = realsize;
    }

    if (info->bytesleft != 0) memcpy( info->buffer_block2, info->buffer, info->bytesleft );

    JNIEnv *env = info->env;
    (*env)->GetByteArrayRegion( env, inBuf, inOff, inLen, info->buffer_block2 + info->bytesleft );

    info->buffer = info->buffer_block;
    info->buffer_block = info->buffer_block2;
    info->buffer_block2 = info->buffer;
    info->buffer = info->buffer_block;

    int tmp;
    tmp = info->bbsize;
    info->bbsize = info->bbsize2;
    info->bbsize2 = tmp;

    info->bytesleft += inLen;

    return info->buffer;
}


/**
 * Reads next buffer.
 */
static unsigned char* aacd_read_buffer( AACDInfo *info )
{
    JNIEnv *env = info->env;

    if (javaABR.clazz == NULL)
    {
        javaABR.clazz = (*env)->GetObjectClass( env, info->reader );
        javaABR.next = (*env)->GetMethodID( env, javaABR.clazz, "next", "()Lcom/spoledge/aacdecoder/BufferReader$Buffer;");

        javaABR.bufferClazz = (*env)->FindClass( env, "com/spoledge/aacdecoder/BufferReader$Buffer");
        javaABR.bufferData = (jfieldID) (*env)->GetFieldID( env, javaABR.bufferClazz, "data", "[B");
        javaABR.bufferSize = (jfieldID) (*env)->GetFieldID( env, javaABR.bufferClazz, "size", "I");
    }

    jobject jbuffer = (*env)->CallObjectMethod( env, info->reader, javaABR.next );
    
    if (!jbuffer) return NULL;

    jbyteArray data = (jbyteArray) (*env)->GetObjectField( env, jbuffer, javaABR.bufferData );
    jint size = (*env)->GetIntField( env, jbuffer, javaABR.bufferSize );

    return aacd_prepare_buffer( info, data, 0, size );
}


/**
 * Prepares output buffer.
 */
static jshort* aacd_prepare_samples( AACDInfo *info, jint outLen )
{
    if (info->samplesLen < outLen)
    {
        if (info->samples) free( info->samples );
        info->samples = malloc( sizeof( jshort ) * outLen );
        info->samplesLen = outLen;
    }

    return info->samples;
}


/**
 * Decodes the stream - one round until the output buffer is (almost) filled.
 */
static void aacd_decode( AACDInfo *info, jshort *samples, jint outLen )
{
    AACD_DEBUG( "decode() start" );

    info->round_frames = 0;
    info->round_bytesconsumed = 0;
    info->round_samples = 0;

    do
    {
        // check if input buffer is filled:
        if (info->bytesleft <= info->frame_max_bytesconsumed)
        {
            AACD_TRACE( "decode() reading input buffer" );
            aacd_read_buffer( info );

            if (info->bytesleft <= info->frame_max_bytesconsumed)
            {
                AACD_INFO( "decode() detected end-of-file" );
                break;
            }
        }

        AACD_TRACE( "decode() frame - frames=%d, consumed=%d, samples=%d, bytesleft=%d, frame_maxconsumed=%d, frame_samples=%d, outLen=%d", info->round_frames, info->round_bytesconsumed, info->round_samples, info->bytesleft, info->frame_max_bytesconsumed, info->frame_samples, outLen);

        int attempts = 10;

        do
        {
            if (!info->decoder->decode( info, info->buffer, info->bytesleft, samples, outLen )) break;

            AACD_WARN( "decode() failed to decode a frame" );
            AACD_DEBUG( "decode() failed to decode a frame - frames=%d, consumed=%d, samples=%d, bytesleft=%d, frame_maxconsumed=%d, frame_samples=%d, outLen=%d", info->round_frames, info->round_bytesconsumed, info->round_samples, info->bytesleft, info->frame_max_bytesconsumed, info->frame_samples, outLen);

            if (info->bytesleft <= info->frame_max_bytesconsumed)
            {
                aacd_read_buffer( info );

                if (info->bytesleft <= info->frame_max_bytesconsumed)
                {
                    AACD_INFO( "decode() detected end-of-file after partial frame error" );
                    attempts = 0;
                    break;
                }
            }

            int pos = info->decoder->sync( info, info->buffer+1, info->bytesleft-1 );

            if (pos >= 0) {
                info->buffer += pos+1;
                info->bytesleft -= pos+1;
            }
        }
        while (--attempts > 0);

        if ( !attempts )
        {
            AACD_WARN( "decode() failed after several attempts");
            break;
        }

        info->round_frames++;
        info->round_bytesconsumed += info->frame_bytesconsumed;
        info->bytesleft -= info->frame_bytesconsumed;
        info->buffer += info->frame_bytesconsumed;

        if (info->frame_bytesconsumed > info->frame_max_bytesconsumed)
        {
            info->frame_max_bytesconsumed_exact = info->frame_bytesconsumed;
            info->frame_max_bytesconsumed = info->frame_bytesconsumed * 3 / 2;
        }

        samples += info->frame_samples;
        outLen -= info->frame_samples;
        info->round_samples += info->frame_samples;
    } 
    while (outLen >= info->frame_samples );

    AACD_DEBUG( "decode() round - frames=%d, consumed=%d, samples=%d, bytesleft=%d, frame_maxconsumed=%d, frame_samples=%d, outLen=%d", info->round_frames, info->round_bytesconsumed, info->round_samples, info->bytesleft, info->frame_max_bytesconsumed, info->frame_samples, outLen);
}


/****************************************************************************************************
 * FUNCTIONS - JNI
 ****************************************************************************************************/

/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeStart
 * Signature: (ILcom/spoledge/aacdecoder/BufferReader;Lcom/spoledge/aacdecoder/Decoder/Info;)I
 */
JNIEXPORT jint JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeStart
  (JNIEnv *env, jobject thiz, jint decoder, jobject jreader, jobject aacInfo)
{
    AACDDecoder *dec = decoder != 0 ? ((AACDDecoder*)decoder) : &aacd_opencore_decoder;
    AACDInfo *info = aacd_start( env, dec, jreader, aacInfo );

    info->env = env;

    unsigned char* buffer = aacd_read_buffer( info );
    unsigned long buffer_size = info->bytesleft;

    int pos = info->decoder->sync( info, buffer, buffer_size );

    if (pos < 0)
    {
        AACD_ERROR( "start() failed - ADTS sync word not found" );
        aacd_stop( info );

        return 0;
    }

    buffer += pos;
    buffer_size -= pos;

    long err = info->decoder->start( info, buffer, buffer_size );

    if (err < 0)
    {
        AACD_ERROR( "start() failed err=%d", err );
        aacd_stop( info );

        return 0;
    }

    // remember pointers for first decode round:
    info->buffer = buffer + err;
    info->bytesleft = buffer_size - err;

    AACD_DEBUG( "start() bytesleft=%d", info->bytesleft );

    aacd_start_info2java( info );

    info->env = NULL;

    return (jint) info;
}


/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeDecode
 * Signature: (I[SI)I
 */
JNIEXPORT jint JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeDecode
  (JNIEnv *env, jobject thiz, jint jinfo, jshortArray outBuf, jint outLen)
{
    AACDInfo *info = (AACDInfo*) jinfo;
    info->env = env;

    // prepare internal output buffer :
    jshort *jsamples = aacd_prepare_samples( info, outLen );

    aacd_decode( info, jsamples, outLen );

    // copy samples back to Java heap:
    (*env)->SetShortArrayRegion( env, outBuf, 0, info->round_samples, jsamples );

    aacd_decode_info2java( info );

    info->env = NULL;

    return (jint) info->round_samples;
}


/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeStop
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeStop
  (JNIEnv *env, jobject thiz, jint jinfo)
{
    AACDInfo *info = (AACDInfo*) jinfo;
    info->env = env;
    aacd_stop( info );
}


/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeDecoderGetByName
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeDecoderGetByName
  (JNIEnv *env, jclass clazzDecoder, jstring jname)
{
    int i;
    AACDDecoder *ret = NULL;
    jboolean isCopy;
    const char *name = (*env)->GetStringUTFChars( env, jname, &isCopy );

    for (i=0; i < AACD_DECODERS_COUNT; i++)
    {
        AACDDecoder *dec = aacd_decoders[i];

        if (!strcmp( name, dec->name()))
        {
            ret = dec;
            break;
        }
    }

    (*env)->ReleaseStringUTFChars( env, jname, name );

    return (jint) ret;
}


