/* ------------------------------------------------------------------
 * Copyright (C) 1998-2010 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/*

 Filename: pvmp4audiodecoderframe.cpp

------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:
    pExt = pointer to the external interface structure. See the file
           PVMP4AudioDecoder_API.h for a description of each field.
           Data type of pointer to a tPVMP4AudioDecoderExternal
           structure.

    pMem = void pointer to hide the internal implementation of the library
           It is cast back to a tDec_Int_File structure. This structure
           contains information that needs to persist between calls to
           this function, or is too big to be placed on the stack, even
           though the data is only needed during execution of this function
           Data type void pointer, internally pointer to a tDec_Int_File
           structure.

 Local Stores/Buffers/Pointers Needed: None
           (The memory set aside in pMem performs this task)

 Global Stores/Buffers/Pointers Needed: None

 Outputs:
     status = 0                       if no error occurred
              MP4AUDEC_NONRECOVERABLE if a non-recoverable error occurred
              MP4AUDEC_RECOVERABLE    if a recoverable error occurred.
              Presently a recoverable error does not exist, but this
              was a requirement.


 Pointers and Buffers Modified:
    pMem contents are modified.
    pExt: (more detail in the file PVMP4AudioDecoder_API.h)
    inputBufferUsedLength - number of array elements used up by the stream.
    remainderBits - remaining bits in the next UInt32 buffer
    samplingRate - sampling rate in samples per sec
    bitRate - bit rate in bits per second, varies frame to frame.
    encodedChannels - channels found on the file (informative)
    frameLength - length of the frame

 Local Stores Modified: None.

 Global Stores Modified: None.

------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 Decodes one frame of an MPEG-2/MPEG-4 encoded audio bitstream.

 This function calls the various components of the decoder in the proper order.


         Left Channel                                    Right Channel
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
 #1 ____________________                           #2 ____________________
    |                  |                              |                  |
    | Huffman Decoding |                              | Huffman Decoding |
    |__________________|                              |__________________|
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                                |
 #3 ____________________                                       |
    |                  |                                       |
    |     PNS LEFT     |                                       |
    |__________________|                                       |
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
 #4 ______________________________________________________________________
    |                                                                    |
    |                          Apply MS_Synt                             |
    |____________________________________________________________________|
             |                                                 |
             |                                                 |
            \|/                                                |
 #5 ____________________                                       |
    |                  |                                       W
    |       LTP        |                                       A
    |__________________|                                       I
             |                                                 T
             |                                                 |
             |                                                 F
            \|/                                                O
 #6 ____________________                                       R
    |                  |                                       |
    |   Time -> Freq   |                                       L
    |__________________|                                       E
             |                                                 F
             |                                                 T
             |                                                 |
            \|/                                                C
 #7 ____________________                                       H
    |                  |                                       A
    |    TNS Inverse   |                                       N
    |__________________|                                       N
             |                                                 E
             |                                                 L
             |                                                 |
            \|/                                                |
 #8 ____________________                                       |
    |                  |                                       |
    | Long Term Synth  |                                       |
    |__________________|                                       |
             |                                                 |
             |                                                \|/
             |                                     #9 ____________________
             |                                        |                  |
             |--DATA ON LEFT CHANNEL MAY BE USED----->| PNS/Intensity Rt |
             |                                        |__________________|
             |                                                 |
             |                                                 |
             |                                                \|/
             |                                    #10 ____________________
             W                                        |                  |
             A                                        |       LTP        |
             I                                        |__________________|
             T                                                 |
             |                                                 |
             F                                                 |
             O                                                \|/
             R                                    #11 ____________________
             |                                        |                  |
             R                                        |   Time -> Freq   |
             I                                        |__________________|
             G                                                 |
             H                                                 |
             T                                                 |
             |                                                \|/
             C                                    #12 ____________________
             H                                        |                  |
             A                                        |    TNS Inverse   |
             N                                        |__________________|
             N                                                 |
             E                                                 |
             L                                                 |
             |                                                \|/
             |                                    #13 ____________________
             |                                        |                  |
             |                                        | Long Term Synth  |
             |                                        |__________________|
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
#14 ____________________                          #18 ____________________
    |                  |                              |                  |
    |       TNS        |                              |       TNS        |
    |__________________|                              |__________________|
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
#15 ____________________                          #19 ____________________
    |                  |                              |                  |
    |   qFormatNorm    |                              |   qFormatNorm    |
    |__________________|                              |__________________|
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
#16 ____________________                          #20 ____________________
    |                  |                              |                  |
    |   Freq / Time    |                              |   Freq / Time    |
    |__________________|                              |__________________|
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
#17 ____________________                          #21 ____________________
    |                  |                              |                  |
    |   Limit Buffer   |                              |   Limit Buffer   |
    |__________________|                              |__________________|
             |                                                 |
             |                                                 |
             |                                                 |
            \|/                                               \|/
#22 ______________________________________________________________________
    |                                                                    |
    |                           Write Output                             |
    |____________________________________________________________________|


------------------------------------------------------------------------------
 REQUIREMENTS

 PacketVideo Document # CCC-AUD-AAC-ERS-0003

------------------------------------------------------------------------------
 REFERENCES

 (1) MPEG-2 NBC Audio Decoder
   "This software module was originally developed by AT&T, Dolby
   Laboratories, Fraunhofer Gesellschaft IIS in the course of development
   of the MPEG-2 NBC/MPEG-4 Audio standard ISO/IEC 13818-7, 14496-1,2 and
   3. This software module is an implementation of a part of one or more
   MPEG-2 NBC/MPEG-4 Audio tools as specified by the MPEG-2 NBC/MPEG-4
   Audio standard. ISO/IEC gives users of the MPEG-2 NBC/MPEG-4 Audio
   standards free license to this software module or modifications thereof
   for use in hardware or software products claiming conformance to the
   MPEG-2 NBC/MPEG-4 Audio  standards. Those intending to use this software
   module in hardware or software products are advised that this use may
   infringe existing patents. The original developer of this software
   module and his/her company, the subsequent editors and their companies,
   and ISO/IEC have no liability for use of this software module or
   modifications thereof in an implementation. Copyright is not released
   for non MPEG-2 NBC/MPEG-4 Audio conforming products.The original
   developer retains full right to use the code for his/her own purpose,
   assign or donate the code to a third party and to inhibit third party
   from using the code for non MPEG-2 NBC/MPEG-4 Audio conforming products.
   This copyright notice must be included in all copies or derivative
   works."
   Copyright(c)1996.

------------------------------------------------------------------------------
*/


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "pv_audio_type_defs.h"

#include "s_tdec_int_chan.h"
#include "s_tdec_int_file.h"
#include "aac_mem_funcs.h"
#include "sfb.h"                   /* Where samp_rate_info[] is declared */
#include "e_tmp4audioobjecttype.h"
#include "e_elementid.h"


#include "get_adif_header.h"
#include "get_adts_header.h"
#include "get_audio_specific_config.h"
#include "ibstream.h"           /* where getbits is declared */

#include "huffman.h"            /* where huffdecode is declared */
#include "get_prog_config.h"
#include "getfill.h"
#include "pns_left.h"

#include "apply_ms_synt.h"
#include "pns_intensity_right.h"
#include "q_normalize.h"
#include "long_term_prediction.h"
#include "long_term_synthesis.h"
#include "ltp_common_internal.h"
#include "apply_tns.h"

#include "window_block_fxp.h"

#include "pvmp4audiodecoder_api.h"   /* Where this function is declared */
#include "get_dse.h"

#include "sbr_applied.h"
#include "sbr_open.h"
#include "get_sbr_bitstream.h"
#include "e_sbr_element_id.h"

#include "get_cce.h"


/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here. Include conditional
; compile variables also.
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; LOCAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; LOCAL STORE/BUFFER/POINTER DEFINITIONS
; Variable declaration - defined here and used outside this module
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; EXTERNAL FUNCTION REFERENCES
; Declare functions defined elsewhere and referenced in this module
----------------------------------------------------------------------------*/




/*----------------------------------------------------------------------------
; EXTERNAL GLOBAL STORE/BUFFER/POINTER REFERENCES
; Declare variables used in this module but defined elsewhere
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/


OSCL_EXPORT_REF Int PVMP4AudioDecodeFrame(
    tPVMP4AudioDecoderExternal  *pExt,
    void                        *pMem)
{
    Int            frameLength;      /* Helper variable */
    Int            ch;
    Int            id_syn_ele;
    UInt           initialUsedBits;  /* Unsigned for C55x */
    Int            qFormatNorm;
    Int            qPredictedSamples;
    Bool           leaveGetLoop;
    MC_Info       *pMC_Info;        /* Helper pointer */
    FrameInfo     *pFrameInfo;      /* Helper pointer */
    tDec_Int_File *pVars;           /* Helper pointer */
    tDec_Int_Chan *pChVars[Chans];  /* Helper pointer */

    per_chan_share_w_fxpCoef *pChLeftShare;  /* Helper pointer */
    per_chan_share_w_fxpCoef *pChRightShare; /* Helper pointer */



    Int            status = MP4AUDEC_SUCCESS;


    Bool empty_frame;

#ifdef AAC_PLUS

    SBRDECODER_DATA *sbrDecoderData;
    SBR_DEC         *sbrDec;
    SBRBITSTREAM    *sbrBitStream;

#endif
    /*
     * Initialize "helper" pointers to existing memory.
     */
    pVars = (tDec_Int_File *)pMem;



    pMC_Info = &pVars->mc_info;

    pChVars[LEFT]  = &pVars->perChan[LEFT];
    pChVars[RIGHT] = &pVars->perChan[RIGHT];

    pChLeftShare = pChVars[LEFT]->pShareWfxpCoef;
    pChRightShare = pChVars[RIGHT]->pShareWfxpCoef;


#ifdef AAC_PLUS

    sbrDecoderData = (SBRDECODER_DATA *) & pVars->sbrDecoderData;
    sbrDec         = (SBR_DEC *) & pVars->sbrDec;
    sbrBitStream   =  pVars->sbrBitStr;

#ifdef PARAMETRICSTEREO
    sbrDecoderData->hParametricStereoDec = (HANDLE_PS_DEC) & pVars->sbrDecoderData.ParametricStereoDec;
#endif

#endif
    /*
     * Translate input buffer variables.
     */
    pVars->inputStream.pBuffer = pExt->pInputBuffer;

    pVars->inputStream.inputBufferCurrentLength = (UInt)pExt->inputBufferCurrentLength;

    pVars->inputStream.availableBits =
        (UInt)(pExt->inputBufferCurrentLength << INBUF_ARRAY_INDEX_SHIFT);

    initialUsedBits =
        (UInt)((pExt->inputBufferUsedLength << INBUF_ARRAY_INDEX_SHIFT) +
               pExt->remainderBits);

    pVars->inputStream.usedBits = initialUsedBits;

    /*
     *  Verified that vital parameters have not changed, after they were set
     */
    if (pVars->parameters_acquired)
    {
        Int32 temp = samp_rate_info[pVars->mc_info.sampling_rate_idx].samp_rate;

#ifdef AAC_PLUS
        temp <<= (pVars->mc_info.upsamplingFactor - 1);
#endif

        if (pExt->samplingRate != temp)
        {
            status = MP4AUDEC_INVALID_FRAME;
        }


        if ((pExt->audioObjectType != pVars->mc_info.audioObjectType) ||
                (pExt->encodedChannels != pVars->mc_info.nch))
        {
            status = MP4AUDEC_INVALID_FRAME;
        }

    }



    if (initialUsedBits > pVars->inputStream.availableBits)
    {
        status = MP4AUDEC_INVALID_FRAME;
    }
    else if (pVars->bno == 0)
    {
        /*
         * Attempt to read in ADIF format first because it is easily identified.
         * If its not an ADIF bitstream, get_adif_header rewinds the "pointer"
         * (actually usedBits).
         */
        status =
            get_adif_header(
                pVars,
                &(pVars->scratch.scratch_prog_config));

        byte_align(&pVars->inputStream);

        if (status == SUCCESS)
        {
            pVars->prog_config.file_is_adts = FALSE;
        }
        else  /* we've tried simple audio config, adif, then it should be adts */
        {
            pVars->prog_config.file_is_adts = TRUE;
        }
    }
    else if ((pVars->bno == 1) && (pVars->prog_config.file_is_adts == FALSE))
    {

        /*
         * There might be an ID_END element following immediately after the
         * AudioSpecificConfig header. This syntactic element should be read
         * and byte_aligned before proceeds to decode "real" AAC raw data.
         */
        id_syn_ele = (Int)getbits(LEN_SE_ID, &pVars->inputStream) ;

        if (id_syn_ele == ID_END)
        {

            byte_align(&pVars->inputStream);

            pExt->inputBufferUsedLength =
                pVars->inputStream.usedBits >> INBUF_ARRAY_INDEX_SHIFT;

            pExt->remainderBits = pVars->inputStream.usedBits & INBUF_BIT_MODULO_MASK;

            pVars->bno++;

            return(status);
        }
        else
        {
            /*
             * Rewind bitstream pointer so that the syntactic element can be
             * read when decoding raw bitstream
             */
            pVars->inputStream.usedBits -= LEN_SE_ID;
        }

    }

    if (pVars->prog_config.file_is_adts == TRUE)
    {
        /*
         *  If file is adts format, let the decoder handle only on data raw
         *  block at the time, once the last (or only) data block has been
         *  processed, then synch on the next header
         */
        if (pVars->prog_config.headerless_frames)
        {
            pVars->prog_config.headerless_frames--;  /* raw data block counter  */
        }
        else
        {
            status =  get_adts_header(pVars,
                                      &(pVars->syncword),
                                      &(pVars->invoke),
                                      3);     /*   CorrectlyReadFramesCount  */

            if (status != SUCCESS)
            {
                status = MP4AUDEC_LOST_FRAME_SYNC;    /*  we lost track of header */
            }
        }
    }
    else
    {
        byte_align(&pVars->inputStream);
    }

#ifdef AAC_PLUS
    sbrBitStream->NrElements = 0;
    sbrBitStream->NrElementsCore = 0;

#endif

    /*
     * The variable leaveGetLoop is used to signal that the following
     * loop can be left, which retrieves audio syntatic elements until
     * an ID_END is found, or an error occurs.
     */
    leaveGetLoop = FALSE;
    empty_frame  = TRUE;




    while ((leaveGetLoop == FALSE) && (status == SUCCESS))
    {
        /* get audio syntactic element */
        id_syn_ele = (Int)get9_n_lessbits(LEN_SE_ID, &pVars->inputStream);

        /*
         *  As fractional frames are a possible input, check that parsing does not
         *  go beyond the available bits before parsing the syntax.
         */
        if (pVars->inputStream.usedBits > pVars->inputStream.availableBits)
        {
            status = MP4AUDEC_INCOMPLETE_FRAME; /* possible EOF or fractional frame */
            id_syn_ele = ID_END;           /* quit while-loop */
        }

        switch (id_syn_ele)
        {
            case ID_END:        /* terminator field */
                leaveGetLoop = TRUE;
                break;

            case ID_SCE:        /* single channel */
            case ID_CPE:        /* channel pair */
                empty_frame = FALSE;
                status = huffdecode(id_syn_ele,
                                    &(pVars->inputStream),
                                    pVars,
                                    pChVars
                                   );

#ifdef AAC_PLUS
                sbrBitStream->sbrElement[sbrBitStream->NrElements].ElementID = id_syn_ele;
                sbrBitStream->NrElementsCore++;
#endif
                break;



            case ID_PCE:        /* program config element */
                /*
                 * PCE are not accepted in the middle of a
                 * raw_data_block. If found, a possible error may happen
                 * If a PCE is encountered during the first 2 frames,
                 * it will be read and accepted
                 * if its tag matches the first, with no error checking
                 * (inside of get_prog_config). Redundant PCE will be accepted too
                 */


                status = get_prog_config(pVars,
                                         &(pVars->scratch.scratch_prog_config));

                if (status != SUCCESS)
                {
                    status = MP4AUDEC_PCE_CHANGE_REQUEST;
                }

                break;

            case ID_FIL:        /* fill element */
#ifdef AAC_PLUS
                if (pExt->aacPlusEnabled == true)
                {
                    get_sbr_bitstream(sbrBitStream, &pVars->inputStream);
                }
                else
                {
                    getfill(&pVars->inputStream);
                }
#else
                getfill(&pVars->inputStream);
#endif

                break;

            case ID_DSE:       /* Data Streaming element */
                get_dse(pVars->share.data_stream_bytes,
                        &pVars->inputStream);
                break;



            default: /* Unsupported element, including ID_LFE */
                status = -1;  /* ERROR CODE needs to be updated */
                break;

        } /* end switch() */

    } /* end while() */

    byte_align(&pVars->inputStream);

    /*

    After parsing the first frame ( bno=0 (adif), bno=1 (raw))
    verify if implicit signalling is forcing to upsample AAC with
    no AAC+/eAAC+ content. Verify that the frame is not empty
    If so, disable upsampling
    */

#ifdef AAC_PLUS
    if ((pVars->bno <= 1) && (empty_frame == FALSE))
    {
        if (!sbrBitStream->NrElements)
        {
            PVMP4AudioDecoderDisableAacPlus(pExt, pMem);
        }
    }
#endif

    /*
     *   There might be an empty raw data block with only a
     *   ID_END element or non audio ID_DSE, ID_FIL
     *   This is an "illegal" condition but this trap
     *   avoids any further processing
     */

    if (empty_frame == TRUE)
    {
        pExt->inputBufferUsedLength =
            pVars->inputStream.usedBits >> INBUF_ARRAY_INDEX_SHIFT;

        pExt->remainderBits = pVars->inputStream.usedBits & INBUF_BIT_MODULO_MASK;

        pVars->bno++;

        return(status);

    }

#ifdef AAC_PLUS
    if (sbrBitStream->NrElements)
    {
        if (pExt->aacPlusEnabled == true)
        {
            /* for every core SCE or CPE there must be an SBR element, otherwise sths. wrong */
            if (sbrBitStream->NrElements != sbrBitStream->NrElementsCore)
            {
                if (pVars->bno <= 1)
                {
                    /*
                     *  Mismatch information indicate a problem on stream
                     *  then default back to AAC
                     */
                    pVars->mc_info.audioObjectType = MP4AUDIO_AAC_LC;
                    pVars->mc_info.ExtendedAudioObjectType = MP4AUDIO_AAC_LC;

                    PVMP4AudioDecoderDisableAacPlus(pExt, pMem);

                    sbrBitStream->NrElements = 0;   /* disable aac processing  */
                }
                else
                {
                    status = MP4AUDEC_INVALID_FRAME;
                }
            }  // else this is what is expected
        }

    }
    else
    {
        /*
         *  This is AAC, but if aac+/eaac+ was declared in the stream, and there is not sbr content
         *  something is wrong
         */
        if ((pMC_Info->sbrPresentFlag || pMC_Info->psPresentFlag) && (pExt->aacPlusEnabled == true))
        {
            status = MP4AUDEC_INVALID_FRAME;
        }
    }
#endif


    /*
     * Signal processing section.
     */
    frameLength = pVars->frameLength;

    if (status == SUCCESS)
    {
        /*
         *   PNS and INTENSITY STEREO and MS
         */

        pFrameInfo = pVars->winmap[pChVars[LEFT]->wnd];

        pns_left(pFrameInfo,
                 pChLeftShare->group,
                 pChLeftShare->cb_map,
                 pChLeftShare->factors,
                 pChLeftShare->lt_status.sfb_prediction_used,
                 pChLeftShare->lt_status.ltp_data_present,
                 pChVars[LEFT]->fxpCoef,
                 pChLeftShare->qFormat,
                 &(pVars->pns_cur_noise_state));

        /*
         *  For dual-mono clips, process second channel as well
         */

        if ((pMC_Info->ch_info[0].cpe == ID_SCE) && (pMC_Info->nch > 1))
        {
            pFrameInfo = pVars->winmap[pChVars[RIGHT]->wnd];

            pns_left(pFrameInfo,
                     pChRightShare->group,
                     pChRightShare->cb_map,
                     pChRightShare->factors,
                     pChRightShare->lt_status.sfb_prediction_used,
                     pChRightShare->lt_status.ltp_data_present,
                     pChVars[RIGHT]->fxpCoef,
                     pChRightShare->qFormat,
                     &(pVars->pns_cur_noise_state));
        }


        /*
         * apply_ms_synt can only be ran for common windows.
         * (where both the left and right channel share the
         * same grouping, window length, etc.
         *
         * pVars->hasmask will be > 0 only if
         * common windows are enabled for this frame.
         */

        if (pVars->hasmask > 0)
        {
            apply_ms_synt(pFrameInfo,
                          pChLeftShare->group,
                          pVars->mask,
                          pChLeftShare->cb_map,
                          pChVars[LEFT]->fxpCoef,
                          pChVars[RIGHT]->fxpCoef,
                          pChLeftShare->qFormat,
                          pChRightShare->qFormat);
        }

        for (ch = 0; (ch < pMC_Info->nch); ch++)
        {
            pFrameInfo = pVars->winmap[pChVars[ch]->wnd];

            /*
             *  Apply right channel properties only if channel is stereo
             *  avoid for dual-mono cases
             */

            if ((ch > 0) && (pMC_Info->ch_info[0].cpe == ID_CPE))
            {
                pns_intensity_right(
                    pVars->hasmask,
                    pFrameInfo,
                    pChRightShare->group,
                    pVars->mask,
                    pChRightShare->cb_map,
                    pChLeftShare->factors,
                    pChRightShare->factors,
                    pChRightShare->lt_status.sfb_prediction_used,
                    pChRightShare->lt_status.ltp_data_present,
                    pChVars[LEFT]->fxpCoef,
                    pChVars[RIGHT]->fxpCoef,
                    pChLeftShare->qFormat,
                    pChRightShare->qFormat,
                    &(pVars->pns_cur_noise_state));
            }

            if (pChVars[ch]->pShareWfxpCoef->lt_status.ltp_data_present != FALSE)
            {
                /*
                 * LTP - Long Term Prediction
                 */

                qPredictedSamples = long_term_prediction(
                                        pChVars[ch]->wnd,
                                        pChVars[ch]->pShareWfxpCoef->lt_status.
                                        weight_index,
                                        pChVars[ch]->pShareWfxpCoef->lt_status.
                                        delay,
                                        pChVars[ch]->ltp_buffer,
                                        pVars->ltp_buffer_state,
                                        pChVars[ch]->time_quant,
                                        pVars->share.predictedSamples,      /* Scratch */
                                        frameLength);

                trans4m_time_2_freq_fxp(
                    pVars->share.predictedSamples,
                    pChVars[ch]->wnd,
                    pChVars[ch]->wnd_shape_prev_bk,
                    pChVars[ch]->wnd_shape_this_bk,
                    &qPredictedSamples,
                    pVars->scratch.fft);   /* scratch memory for FFT */


                /*
                 * To solve a potential problem where a pointer tied to
                 * the qFormat was being incremented, a pointer to
                 * pChVars[ch]->qFormat is passed in here rather than
                 * the address of qPredictedSamples.
                 *
                 * Neither values are actually needed in the case of
                 * inverse filtering, but the pointer was being
                 * passed (and incremented) regardless.
                 *
                 * So, the solution is to pass a space of memory
                 * that a pointer can happily point to.
                 */

                /* This is the inverse filter */
                apply_tns(
                    pVars->share.predictedSamples,  /* scratch re-used for each ch */
                    pChVars[ch]->pShareWfxpCoef->qFormat,     /* Not used by the inv_filter */
                    pFrameInfo,
                    &(pChVars[ch]->pShareWfxpCoef->tns),
                    TRUE,                       /* TRUE is FIR */
                    pVars->scratch.tns_inv_filter);

                /*
                 * For the next function long_term_synthesis,
                 * the third param win_sfb_top[], and
                 * the tenth param coef_per_win,
                 * are used differently that in the rest of the project. This
                 * is because originally the ISO code was going to have
                 * these parameters change as the "short window" changed.
                 * These are all now the same value for each of the eight
                 * windows.  This is why there is a [0] at the
                 * end of each of theses parameters.
                 * Note in particular that win_sfb_top was originally an
                 * array of pointers to arrays, but inside long_term_synthesis
                 * it is now a simple array.
                 * When the rest of the project functions are changed, the
                 * structure FrameInfo changes, and the [0]'s are removed,
                 * this comment could go away.
                 */
                long_term_synthesis(
                    pChVars[ch]->wnd,
                    pChVars[ch]->pShareWfxpCoef->max_sfb,
                    pFrameInfo->win_sfb_top[0], /* Look above */
                    pChVars[ch]->pShareWfxpCoef->lt_status.win_prediction_used,
                    pChVars[ch]->pShareWfxpCoef->lt_status.sfb_prediction_used,
                    pChVars[ch]->fxpCoef,   /* input and output */
                    pChVars[ch]->pShareWfxpCoef->qFormat,   /* input and output */
                    pVars->share.predictedSamples,
                    qPredictedSamples,       /* q format for previous aray */
                    pFrameInfo->coef_per_win[0], /* Look above */
                    NUM_SHORT_WINDOWS,
                    NUM_RECONSTRUCTED_SFB);

            } /* end if (pChVars[ch]->lt_status.ltp_data_present != FALSE) */

        } /* for(ch) */

        for (ch = 0; (ch < pMC_Info->nch); ch++)
        {

            pFrameInfo = pVars->winmap[pChVars[ch]->wnd];

            /*
             * TNS - Temporal Noise Shaping
             */

            /* This is the forward filter
             *
             * A special note:  Scratch memory is not used by
             * the forward filter, but is passed in to maintain
             * common interface for inverse and forward filter
             */
            apply_tns(pChVars[ch]->fxpCoef,
                      pChVars[ch]->pShareWfxpCoef->qFormat,
                      pFrameInfo,
                      &(pChVars[ch]->pShareWfxpCoef->tns),
                      FALSE,                   /* FALSE is IIR */
                      pVars->scratch.tns_inv_filter);

            /*
             * Normalize the q format across all scale factor bands
             * to one value.
             */
            qFormatNorm = q_normalize(pChVars[ch]->pShareWfxpCoef->qFormat,
                                      pFrameInfo,
                                      pChVars[ch]->abs_max_per_window,
                                      pChVars[ch]->fxpCoef);

            /*
             *  filterbank - converts frequency coeficients to time domain.
             */

#ifdef AAC_PLUS
            if (sbrBitStream->NrElements == 0 && pMC_Info->upsamplingFactor == 1)
            {
                trans4m_freq_2_time_fxp_2(
                    pChVars[ch]->fxpCoef,
                    pChVars[ch]->time_quant,
                    pChVars[ch]->wnd,   /* window sequence */
                    pChVars[ch]->wnd_shape_prev_bk,
                    pChVars[ch]->wnd_shape_this_bk,
                    qFormatNorm,
                    pChVars[ch]->abs_max_per_window,
                    pVars->scratch.fft,
                    &pExt->pOutputBuffer[ch]);
                /*
                 *  Update LTP buffers if needed
                 */

                if (pVars->mc_info.audioObjectType == MP4AUDIO_LTP)
                {
                    Int16 * pt = &pExt->pOutputBuffer[ch];
                    Int16 * ptr = &(pChVars[ch]->ltp_buffer[pVars->ltp_buffer_state]);
                    Int16  x, y;
                    for (Int32 i = HALF_LONG_WINDOW; i != 0; i--)
                    {
                        x = *pt;
                        pt += 2;
                        y = *pt;
                        pt += 2;
                        *(ptr++) =  x;
                        *(ptr++) =  y;
                    }
                }
            }
            else
            {
                trans4m_freq_2_time_fxp_1(
                    pChVars[ch]->fxpCoef,
                    pChVars[ch]->time_quant,
                    &(pChVars[ch]->ltp_buffer[pVars->ltp_buffer_state + 288]),
                    pChVars[ch]->wnd,   /* window sequence */
                    pChVars[ch]->wnd_shape_prev_bk,
                    pChVars[ch]->wnd_shape_this_bk,
                    qFormatNorm,
                    pChVars[ch]->abs_max_per_window,
                    pVars->scratch.fft);

            }
#else

            trans4m_freq_2_time_fxp_2(
                pChVars[ch]->fxpCoef,
                pChVars[ch]->time_quant,
                pChVars[ch]->wnd,   /* window sequence */
                pChVars[ch]->wnd_shape_prev_bk,
                pChVars[ch]->wnd_shape_this_bk,
                qFormatNorm,
                pChVars[ch]->abs_max_per_window,
                pVars->scratch.fft,
                &pExt->pOutputBuffer[ch]);
            /*
             *  Update LTP buffers only if needed
             */

            if (pVars->mc_info.audioObjectType == MP4AUDIO_LTP)
            {
                Int16 * pt = &pExt->pOutputBuffer[ch];
                Int16 * ptr = &(pChVars[ch]->ltp_buffer[pVars->ltp_buffer_state]);
                Int16  x, y;
                for (Int32 i = HALF_LONG_WINDOW; i != 0; i--)
                {
                    x = *pt;
                    pt += 2;
                    y = *pt;
                    pt += 2;
                    *(ptr++) =  x;
                    *(ptr++) =  y;
                }

            }

#endif
            /* Update the window shape */
            pChVars[ch]->wnd_shape_prev_bk = pChVars[ch]->wnd_shape_this_bk;

        } /* end for() */

        /*
         * Copy to the final output buffer, taking into account the desired
         * channels from the calling environment, the actual channels, and
         * whether the data should be interleaved or not.
         *
         * If the stream had only one channel, write_output will not use
         * the right channel data.
         *
         */


        /* CONSIDER USE OF DMA OPTIMIZATIONS WITHIN THE write_output FUNCTION.
         *
         * It is presumed that the ltp_buffer will reside in internal (fast)
         * memory, while the pExt->pOutputBuffer will reside in external
         * (slow) memory.
         *
         */

#ifdef AAC_PLUS

        if (sbrBitStream->NrElements || pMC_Info->upsamplingFactor == 2)
        {

            if (pVars->bno <= 1)   /* allows console to operate with ADIF and audio config */
            {
                if (sbrDec->outSampleRate == 0) /* do it only once (disregarding of signaling type) */
                {
                    sbr_open(samp_rate_info[pVars->mc_info.sampling_rate_idx].samp_rate,
                             sbrDec,
                             sbrDecoderData,
                             pVars->mc_info.bDownSampledSbr);
                }
            }
            pMC_Info->upsamplingFactor =
                sbrDecoderData->SbrChannel[0].frameData.sbr_header.sampleRateMode;

            /* reuse right aac spectrum channel  */
            {
                Int16 *pt_left  =  &(pChVars[LEFT ]->ltp_buffer[pVars->ltp_buffer_state]);
                Int16 *pt_right =  &(pChVars[RIGHT]->ltp_buffer[pVars->ltp_buffer_state]);

                if (sbr_applied(sbrDecoderData,
                                sbrBitStream,
                                pt_left,
                                pt_right,
                                pExt->pOutputBuffer,
                                sbrDec,
                                pVars,
                                pMC_Info->nch) != SBRDEC_OK)
                {
                    status = MP4AUDEC_INVALID_FRAME;
                }
            }


        }  /*  if( pExt->aacPlusEnabled == FALSE) */
#endif

        /*
         * Copied mono data in both channels or just leave it as mono,
         * according with desiredChannels (default is 2)
         */

        if (pExt->desiredChannels == 2)
        {

#if defined(AAC_PLUS)
#if defined(PARAMETRICSTEREO)&&defined(HQ_SBR)
            if (pMC_Info->nch != 2 && pMC_Info->psPresentFlag != 1)
#else
            if (pMC_Info->nch != 2)
#endif
#else
            if (pMC_Info->nch != 2)
#endif
            {
                /* mono */


                Int16 * pt  = &pExt->pOutputBuffer[0];
                Int16 * pt2 = &pExt->pOutputBuffer[1];
                Int i;
                if (pMC_Info->upsamplingFactor == 2)
                {
                    for (i = 0; i < 1024; i++)
                    {
                        *pt2 = *pt;
                        pt += 2;
                        pt2 += 2;
                    }
                    pt  = &pExt->pOutputBuffer_plus[0];
                    pt2 = &pExt->pOutputBuffer_plus[1];

                    for (i = 0; i < 1024; i++)
                    {
                        *pt2 = *pt;
                        pt += 2;
                        pt2 += 2;
                    }
                }
                else
                {
                    for (i = 0; i < 1024; i++)
                    {
                        *pt2 = *pt;
                        pt += 2;
                        pt2 += 2;
                    }
                }

            }

#if defined(AAC_PLUS)
#if defined(PARAMETRICSTEREO)&&defined(HQ_SBR)

            else if (pMC_Info->psPresentFlag == 1)
            {
                Int32 frameSize = 0;
                if (pExt->aacPlusEnabled == false)
                {
                    /*
                     *  Decoding eaac+ when only aac is enabled, copy L into R
                     */
                    frameSize = 1024;
                }
                else if (sbrDecoderData->SbrChannel[0].syncState != SBR_ACTIVE)
                {
                    /*
                     *  Decoding eaac+ when no PS data was found, copy upsampled L into R
                     */
                    frameSize = 2048;
                }

                Int16 * pt  = &pExt->pOutputBuffer[0];
                Int16 * pt2 = &pExt->pOutputBuffer[1];
                Int i;
                for (i = 0; i < frameSize; i++)
                {
                    *pt2 = *pt;
                    pt += 2;
                    pt2 += 2;
                }
            }
#endif
#endif

        }
        else
        {

#if defined(AAC_PLUS)
#if defined(PARAMETRICSTEREO)&&defined(HQ_SBR)
            if (pMC_Info->nch != 2 && pMC_Info->psPresentFlag != 1)
#else
            if (pMC_Info->nch != 2)
#endif
#else
            if (pMC_Info->nch != 2)
#endif
            {
                /* mono */
                Int16 * pt  = &pExt->pOutputBuffer[0];
                Int16 * pt2 = &pExt->pOutputBuffer[0];
                Int i;

                if (pMC_Info->upsamplingFactor == 2)
                {
                    for (i = 0; i < 1024; i++)
                    {
                        *pt2++ = *pt;
                        pt += 2;
                    }

                    pt  = &pExt->pOutputBuffer_plus[0];
                    pt2 = &pExt->pOutputBuffer_plus[0];

                    for (i = 0; i < 1024; i++)
                    {
                        *pt2++ = *pt;
                        pt += 2;
                    }
                }
                else
                {
                    for (i = 0; i < 1024; i++)
                    {
                        *pt2++ = *pt;
                        pt += 2;
                    }
                }

            }

        }

        /* pVars->ltp_buffer_state cycles between 0 and 1024.  The value
         * indicates the location of the data corresponding to t == -2.
         *
         * | t == -2 | t == -1 |  pVars->ltp_buffer_state == 0
         *
         * | t == -1 | t == -2 |  pVars->ltp_buffer_state == 1024
         *
         */

#ifdef AAC_PLUS
        if (sbrBitStream->NrElements == 0 && pMC_Info->upsamplingFactor == 1)
        {
            pVars->ltp_buffer_state ^= frameLength;
        }
        else
        {
            pVars->ltp_buffer_state ^= (frameLength + 288);
        }
#else
        pVars->ltp_buffer_state ^= frameLength;
#endif

        if (pVars->bno <= 1)
        {
            /*
             * to set these values only during the second call
             * when they change.
             */

            pVars->parameters_acquired = true;

            pExt->samplingRate =
                samp_rate_info[pVars->mc_info.sampling_rate_idx].samp_rate;

            pVars->mc_info.implicit_channeling = 0; /* disable flag, as this is allowed
                                                      * only the first time
                                                      */

#ifdef AAC_PLUS

            if (pMC_Info->upsamplingFactor == 2)
            {
                pExt->samplingRate *= pMC_Info->upsamplingFactor;
                pExt->aacPlusUpsamplingFactor = pMC_Info->upsamplingFactor;
            }
#endif

            pExt->extendedAudioObjectType = pMC_Info->ExtendedAudioObjectType;
            pExt->audioObjectType = pMC_Info->audioObjectType;

            pExt->encodedChannels = pMC_Info->nch;
            pExt->frameLength = pVars->frameLength;


            pExt->multichannel_detected = pVars->multichannel_detected;
            if (pVars->multichannel_detected)
            {
                pExt->multichannel_numChannels = pVars->multichannel_numChannels ;
            }
        }

        pVars->bno++;


        /*
         * Using unit analysis, the bitrate is a function of the sampling rate, bits,
         * points in a frame
         *
         *     bits        samples                frame
         *     ----  =    --------- *  bits  *   -------
         *     sec           sec                  sample
         *
         * To save a divide, a shift is used. Presently only the value of
         * 1024 is used by this library, so make it the most accurate for that
         * value. This may need to be updated later.
         */

        pExt->bitRate = (pExt->samplingRate *
                         (pVars->inputStream.usedBits - initialUsedBits)) >> 10;  /*  LONG_WINDOW  1024 */

        pExt->bitRate >>= (pMC_Info->upsamplingFactor - 1);


    } /* end if (status == SUCCESS) */


    if (status != MP4AUDEC_SUCCESS)
    {
        /*
         *  A non-SUCCESS decoding could be due to an error on the bitstream or
         *  an incomplete frame. As access to the bitstream beyond frame boundaries
         *  are not allowed, in those cases the bitstream reading routine return a 0
         *  Zero values guarantees that the data structures are filled in with values
         *  that eventually will signal an error (like invalid parameters) or that allow
         *  completion of the parsing routine. Either way, the partial frame condition
         *  is verified at this time.
         */
        if (pVars->prog_config.file_is_adts == TRUE)
        {
            status = MP4AUDEC_LOST_FRAME_SYNC;
            pVars->prog_config.headerless_frames = 0; /* synchronization forced */
        }
        else
        {
            /*
             *  Check if the decoding error was due to buffer overrun, if it was,
             *  update status
             */
            if (pVars->inputStream.usedBits > pVars->inputStream.availableBits)
            {
                /* all bits were used but were not enough to complete decoding */
                pVars->inputStream.usedBits = pVars->inputStream.availableBits;

                status = MP4AUDEC_INCOMPLETE_FRAME; /* possible EOF or fractional frame */
            }
        }
    }

    /*
     * Translate from units of bits back into units of words.
     */

    pExt->inputBufferUsedLength =
        pVars->inputStream.usedBits >> INBUF_ARRAY_INDEX_SHIFT;

    pExt->remainderBits = (Int)(pVars->inputStream.usedBits & INBUF_BIT_MODULO_MASK);



    return (status);

} /* PVMP4AudioDecoderDecodeFrame */

