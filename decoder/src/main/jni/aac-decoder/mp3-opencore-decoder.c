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

#define AACD_MODULE "Decoder[OpenCORE-MP3]"

#include "aac-common.h"

#include "pvmp3_audio_type_defs.h"
#include "pvmp3_dec_defs.h"
#include "pvmp3decoder_api.h"

#include <string.h>

typedef struct AACDOpenCoreMP3 {
    tPVMP3DecoderExternal *pExt;
    void *pMem;
} AACDOpenCoreMP3;



static const char* aacd_opencoremp3_name()
{
    return "OpenCORE-MP3";
}


static void* aacd_opencoremp3_init()
{
    AACDOpenCoreMP3 *oc = (AACDOpenCoreMP3*) calloc( 1, sizeof(struct AACDOpenCoreMP3));

    oc->pExt = calloc( 1, sizeof( tPVMP3DecoderExternal ));
    oc->pMem = malloc( pvmp3_decoderMemRequirements());

    tPVMP3DecoderExternal *pExt = oc->pExt;

    return oc;
}


static void aacd_opencoremp3_destroy( AACDInfo *info )
{
    AACDOpenCoreMP3 *oc = (AACDOpenCoreMP3*) info->ext;

    if ( !oc ) return;

    if (oc->pMem != NULL) free( oc->pMem );
    if (oc->pExt != NULL) free( oc->pExt );

    free( oc );
}


static long aacd_opencoremp3_start( AACDInfo *info, unsigned char *buffer, unsigned long buffer_size)
{
    AACD_TRACE( "start() buffer=%x size=%d", (*(unsigned long*)buffer), buffer_size );

    AACDOpenCoreMP3 *oc = (AACDOpenCoreMP3*) info->ext;
    tPVMP3DecoderExternal *pExt = oc->pExt;

    // prepare the first samples buffer:
    //pExt->pOutputBuffer             = malloc(4096 * sizeof(int16_t));
    pExt->pOutputBuffer             = aacd_prepare_samples( info, 4096 );
    pExt->outputFrameSize           = 4096;

    pExt->pInputBuffer              = buffer;
    pExt->inputBufferMaxLength      = buffer_size;
    pExt->inputBufferCurrentLength  = buffer_size;
    pExt->inputBufferUsedLength     = 0;

    pExt->crcEnabled                = 0;
    pExt->equalizerType             = flat;
    pvmp3_InitDecoder( oc->pExt, oc->pMem );

    int32_t status;
    int frameDecoded = 0;
    int attempts = 16;
    int totalConsumed = 0;
    pExt->outputFrameSize           = 0;

    /* pre-init search adts sync */
    while (!frameDecoded && attempts--) {
        pExt->pInputBuffer              = buffer;
        pExt->inputBufferMaxLength      = buffer_size;
        pExt->inputBufferCurrentLength  = buffer_size;
        pExt->inputBufferUsedLength     = 0;
        pExt->outputFrameSize           = 4096;

        status = pvmp3_framedecoder(pExt, oc->pMem);
        AACD_DEBUG( "start() Status[0]: %d - consumed %d bytes", status, pExt->inputBufferUsedLength );

        totalConsumed += pExt->inputBufferUsedLength;

        if (status != NO_DECODING_ERROR) {
            AACD_ERROR( "start() frame decode error=%d", status );

            if (!pExt->inputBufferUsedLength) {
                AACD_ERROR( "start() first frame cannot be decoded - trying to sync again" );

                int move = buffer_size < 2048 ? (buffer_size >> 1) : 1024;
                buffer += move;
                buffer_size -= move;
                totalConsumed += move;

                pExt->pInputBuffer              = buffer;
                pExt->inputBufferMaxLength      = buffer_size;
                pExt->inputBufferCurrentLength  = buffer_size;

                ERROR_CODE err = pvmp3_frame_synch( oc->pExt, oc->pMem );

                if (err == SYNCH_LOST_ERROR) {
                    AACD_ERROR( "start() cannot re-sync the stream after next %d bytes, status=%d", move, err );
                }
                else if (err != NO_DECODING_ERROR) {
                    AACD_ERROR( "start() cannot sync the stream status=%d", err );
                    break;
                }
                else {
                    totalConsumed += pExt->inputBufferUsedLength;
                    AACD_INFO( "start() sync was successful - used bytes=%d", totalConsumed );
                }
            }
            buffer -= pExt->inputBufferUsedLength;
            buffer_size -= pExt->inputBufferUsedLength;
        }
        else frameDecoded = 1;

        if (buffer_size <= 64) break;
    }

    //free(pExt->pOutputBuffer);
    pExt->pOutputBuffer = NULL;

    if (status != NO_DECODING_ERROR)
    {
        AACD_ERROR( "start() init failed status=%d", status );
        return -1;
    }

    AACD_DEBUG( "start() bytesconsumed=%d", totalConsumed );

    info->samplerate = pExt->samplingRate;
    info->channels = pExt->num_channels;

    info->frame_bytesconsumed = pExt->inputBufferUsedLength;
    info->frame_samples = pExt->outputFrameSize;

    return totalConsumed;
}


static int aacd_opencoremp3_decode( AACDInfo *info, unsigned char *buffer, unsigned long buffer_size, jshort *jsamples, jint outLen )
{
    AACDOpenCoreMP3 *oc = (AACDOpenCoreMP3*) info->ext;
    tPVMP3DecoderExternal *pExt = oc->pExt;

    pExt->pInputBuffer              = buffer;
    pExt->inputBufferMaxLength      = buffer_size;
    pExt->inputBufferCurrentLength  = buffer_size;
    pExt->inputBufferUsedLength     = 0;

    pExt->pOutputBuffer = jsamples;
    pExt->outputFrameSize = outLen;

    int32_t status = pvmp3_framedecoder( pExt, oc->pMem );

    if (status != NO_DECODING_ERROR)
    {
        AACD_ERROR( "decode() bytesleft=%lu, status=%d", buffer_size, status );
        return -1;
    }

    info->frame_bytesconsumed = pExt->inputBufferUsedLength;
    info->frame_samples = pExt->outputFrameSize;

    return 0;
}


static int aacd_opencoremp3_sync( AACDInfo *info, unsigned char *buffer, int buffer_size )
{
    AACDOpenCoreMP3 *oc = (AACDOpenCoreMP3*) info->ext;

    if (oc->pExt->pOutputBuffer)
    {
        ERROR_CODE err = pvmp3_frame_synch( oc->pExt, oc->pMem );

        return err != NO_DECODING_ERROR ? -1 : oc->pExt->inputBufferUsedLength;
    }

    return 0;
}


AACDDecoder aacd_opencoremp3_decoder = {
    aacd_opencoremp3_name,
    aacd_opencoremp3_init,
    aacd_opencoremp3_start,
    aacd_opencoremp3_decode,
    aacd_opencoremp3_destroy,
    aacd_opencoremp3_sync
};

