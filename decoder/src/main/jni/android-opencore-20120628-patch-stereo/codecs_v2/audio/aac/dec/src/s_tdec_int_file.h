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

 Filename: s_tdec_int_file.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This include file defines the structure, tDec_Int_Chan

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef S_TDEC_INT_FILE_H
#define S_TDEC_INT_FILE_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*----------------------------------------------------------------------------
    ; INCLUDES
    ----------------------------------------------------------------------------*/
#include "pv_audio_type_defs.h"
#include "s_progconfig.h"
#include "s_frameinfo.h"
#include "s_mc_info.h"
#include "s_adif_header.h"
#include "s_tdec_int_chan.h"
#include "s_pulseinfo.h"
#include "s_bits.h"
#include "s_hcb.h"
#include "e_infoinitconst.h"

#include "s_sbr_channel.h"
#include "s_sbr_dec.h"
#include "s_sbrbitstream.h"

    /*----------------------------------------------------------------------------
    ; MACROS
    ; Define module specific macros here
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES
    ; Include all pre-processor statements here.
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; EXTERNAL VARIABLES REFERENCES
    ; Declare variables used in this module but defined elsewhere
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; SIMPLE TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; ENUMERATED TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; STRUCTURES TYPEDEF'S
    ----------------------------------------------------------------------------*/





    /*
     * Note: most of the names of the variables put into this structure were kept
     * the same because the name is also used in called functions.
     *
     * bno - block number
     *
     */
    typedef struct
    {
        UInt32         bno;
        Int            status;  /* save the status */

        bool           parameters_acquired;
        bool           aacPlusEnabled;
        bool           aacConfigUtilityEnabled;

        bool           multichannel_detected;
        Int            multichannel_numChannels;

        Int            current_program;
        Int            frameLength;
        Int            adif_test;


        BITS           inputStream;

        ProgConfig     prog_config;

        Int            SFBWidth128[(1<<LEN_MAX_SFBS)];

        /*
         * One of the two arrays should be deleted in the final version.
         */
        FrameInfo      longFrameInfo;
        FrameInfo      shortFrameInfo;
        FrameInfo     *winmap[NUM_WIN_SEQ];

        /*
         * Pns variables.
         */
        Int32          pns_cur_noise_state;

        /*
         *
         */
        MC_Info        mc_info;

        Int            ltp_buffer_state;



#ifdef AAC_PLUS

        SBRDECODER_DATA sbrDecoderData;/* allocates 2 SBR_CHANNEL, each has a SBR_FRAME_DATA */
        SBR_DEC         sbrDec;
        SBRBITSTREAM    sbrBitStr[Chans];

#endif


        /*
         * If ADTS support is needed, the following variables will
         * be required.
         */
        UInt32         syncword;
        Int            invoke;

        Int         mask[MAXBANDS];
        Int         hasmask;


        /*
         *  For eaac+, a scratch matrix is created with the rigth element ( perChan[1] is not used)
         *  and the fxpCoef matrix. These  2 matrices are [2][38][64] == 4864 Int32
         *    2349 coming from the perChan[1] plus 4096 coming from fxpCoef
         */
        tDec_Int_Chan  perChan[Chans];

        Int32          fxpCoef[2][LN];         /* LN  = 2048     */



        /*  SBR usage
         *  These two unions are used for the SBR tool and used
         *  as a single 2560 int32 continuous memory for circular
         *  buffering the synthesis QMF's bank history
         */

        /* This union specifies memory for arrays which are used
         * by only one function.  This is the simplest type of scratch
         * memory to implement, since there are no worries about
         * function interaction.
         */
        union scratch_memory
        {
            Int32  fft[LONG_WINDOW];    /* 1024, as needed by the FFT */
            Int32  tns_inv_filter[TNS_MAX_ORDER];
            struct
            {
                Int32  tns_decode_coef[2*TNS_MAX_ORDER];
                Int    huffbook_used[248];
            } a;
            Int16  tmp_spec[LN2];  /* Used in conjunction with quant_spec */

            ADIF_Header    adif_header;

            ProgConfig     scratch_prog_config;


            Int32  scratch_mem[16][64];
        } scratch;

        /* This union tries to take advantage of the fact that
         * some variables are only used before LTP, and
         * the long array, predictedSamples, is only used after LTP.
         */

        /*
         *  also used by the circular buffer scheme on aac+ (needs 4096 + 1152)
         *  from scratch_mem[2] + 5248  (uses most of shared_memory).
         *  For eaac+, shared memory is used by sbrQmfBufferReal which needs
         *  1824 bytes
         */
        union shared_memory
        {
            Int32       predictedSamples[LONG_BLOCK1];  /* 2048 Int32 */

            Char        data_stream_bytes[(1<<LEN_D_CNT)+1];

            struct
            {
                Int16         quantSpec[LN2];
                SectInfo    sect[MAXBANDS + 1];
                PulseInfo   pulseInfo;
            } a;

        } share;


    } tDec_Int_File;

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* S_TDEC_INT_FILE_H */
