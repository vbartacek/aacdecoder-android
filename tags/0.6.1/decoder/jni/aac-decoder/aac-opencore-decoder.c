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

#define AACD_MODULE "Decoder[OpenCORE]"

#include "aac-common.h"

#include "pvmp4audiodecoder_api.h"
#include "e_tmp4audioobjecttype.h"

#include <string.h>

typedef struct AACDOpenCore {
    tPVMP4AudioDecoderExternal *pExt;
    void *pMem;
    unsigned long frameSamplesFactor;
} AACDOpenCore;



static const char* aacd_opencore_name()
{
    return "OpenCORE";
}


static void* aacd_opencore_init()
{
    AACDOpenCore *oc = (AACDOpenCore*) calloc( 1, sizeof(struct AACDOpenCore));

    oc->pExt = calloc( 1, sizeof( tPVMP4AudioDecoderExternal ));
    oc->pMem = malloc( PVMP4AudioDecoderGetMemRequirements());

    tPVMP4AudioDecoderExternal *pExt = oc->pExt;

    pExt->desiredChannels           = 2;
    pExt->outputFormat              = OUTPUTFORMAT_16PCM_INTERLEAVED;
    pExt->repositionFlag            = TRUE;
    pExt->aacPlusEnabled            = TRUE;

    Int err = PVMP4AudioDecoderInitLibrary(pExt, oc->pMem);

    if (err)
    {
        AACD_ERROR( "PVMP4AudioDecoderInitLibrary failed err=%d", err );

        free( pExt );
        free( oc->pMem );
        free( oc );

        oc = NULL;
    }

    return oc;
}


static void aacd_opencore_destroy( AACDInfo *info )
{
    AACDOpenCore *oc = (AACDOpenCore*) info->ext;

    if ( !oc ) return;

    if (oc->pMem != NULL) free( oc->pMem );
    if (oc->pExt != NULL) free( oc->pExt );

    free( oc );
}


static long aacd_opencore_start( AACDInfo *info, unsigned char *buffer, unsigned long buffer_size)
{
    AACD_TRACE( "start() buffer=%x size=%d", (*(unsigned long*)buffer), buffer_size );

    AACDOpenCore *oc = (AACDOpenCore*) info->ext;
    tPVMP4AudioDecoderExternal *pExt = oc->pExt;

    pExt->remainderBits             = 0;
    pExt->frameLength               = 0;

    // prepare the first samples buffer:
    pExt->pOutputBuffer             = malloc(4096 * sizeof(int16_t));
    pExt->pOutputBuffer_plus        = pExt->pOutputBuffer + 2048;

    int32_t status;
    int frameDecoded = 0;
    int attempts = 16;

    /* pre-init search adts sync */
    while (pExt->frameLength == 0 && attempts--) {
        pExt->pInputBuffer              = buffer;
        pExt->inputBufferMaxLength      = buffer_size;
        pExt->inputBufferCurrentLength  = buffer_size;
        pExt->inputBufferUsedLength     = 0;

        status = PVMP4AudioDecoderConfig(pExt, oc->pMem);
        AACD_DEBUG( "start() Status[0]: %d", status );

        if (status != MP4AUDEC_SUCCESS) {
            status = PVMP4AudioDecodeFrame(pExt, oc->pMem);
            AACD_DEBUG( "start() Status[1]: %d", status );

            buffer -= pExt->inputBufferUsedLength;
            buffer_size -= pExt->inputBufferUsedLength;

            if (MP4AUDEC_SUCCESS == status) {
                AACD_DEBUG( "start() frameLength: %d\n", pExt->frameLength);
                frameDecoded = 1;
                continue;
            }
        }

        if (buffer_size <= PVMP4AUDIODECODER_INBUFSIZE) break;
    }

    if (!frameDecoded)
    {
        AACD_INFO( "start() No stream info available - trying to decode a frame" );

        if (buffer_size >= PVMP4AUDIODECODER_INBUFSIZE) status = PVMP4AudioDecodeFrame(pExt, oc->pMem);
        else AACD_WARN( "start() Input buffer too small" );
    }

    free(pExt->pOutputBuffer);

    if (status != MP4AUDEC_SUCCESS)
    {
        AACD_ERROR( "start() init failed status=%d", status );
        return -1;
    }

    AACD_DEBUG( "start() bytesconsumed=%d", pExt->inputBufferUsedLength );

    int streamType  = -1;

    if ((pExt->extendedAudioObjectType == MP4AUDIO_AAC_LC) ||
            (pExt->extendedAudioObjectType == MP4AUDIO_LTP))
    {
        streamType = AAC;
    }
    else if (pExt->extendedAudioObjectType == MP4AUDIO_SBR)
    {
        streamType = AACPLUS;
    }
    else if (pExt->extendedAudioObjectType == MP4AUDIO_PS)
    {
        streamType = ENH_AACPLUS;
    }

    AACD_DEBUG( "start() streamType=%d", streamType );

    if ((AAC == streamType) && (2 == pExt->aacPlusUpsamplingFactor))
    {
        AACD_INFO( "start() DisableAacPlus" );
        PVMP4AudioDecoderDisableAacPlus(pExt, oc->pMem);
    }

    info->samplerate = pExt->samplingRate;
    info->channels = pExt->desiredChannels;

    oc->frameSamplesFactor = pExt->desiredChannels;
    if (2 == pExt->aacPlusUpsamplingFactor) oc->frameSamplesFactor *= 2;

    return pExt->inputBufferUsedLength;
}



static int aacd_opencore_decode( AACDInfo *info, unsigned char *buffer, unsigned long buffer_size, jshort *jsamples, jint outLen )
{
    AACDOpenCore *oc = (AACDOpenCore*) info->ext;
    tPVMP4AudioDecoderExternal *pExt = oc->pExt;

    pExt->pInputBuffer              = buffer;
    pExt->inputBufferMaxLength      = buffer_size;
    pExt->inputBufferCurrentLength  = buffer_size;
    pExt->inputBufferUsedLength     = 0;

    pExt->pOutputBuffer = jsamples;
    pExt->pOutputBuffer_plus = jsamples+2048;

    int32_t status = PVMP4AudioDecodeFrame( pExt, oc->pMem );

    if (status != MP4AUDEC_SUCCESS && status != SUCCESS)
    {
        AACD_ERROR( "decode() bytesleft=%d, status=%d", buffer_size, status );
        return -1;
    }

    info->frame_bytesconsumed = pExt->inputBufferUsedLength;
    info->frame_samples = pExt->frameLength * oc->frameSamplesFactor;

    return 0;
}


static int aacd_opencore_sync( AACDInfo *info, unsigned char *buffer, int buffer_size )
{
    return aacd_adts_sync( buffer, buffer_size );
}


AACDDecoder aacd_opencore_decoder = {
    aacd_opencore_name,
    aacd_opencore_init,
    aacd_opencore_start,
    aacd_opencore_decode,
    aacd_opencore_destroy,
    aacd_opencore_sync
};

