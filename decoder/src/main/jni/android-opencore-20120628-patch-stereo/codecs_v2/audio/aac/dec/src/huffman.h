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

 Filename: huffman.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 include function prototype definitions for Huffman decoding module

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef HUFFMAN_H
#define HUFFMAN_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*----------------------------------------------------------------------------
    ; INCLUDES
    ----------------------------------------------------------------------------*/
#include    "pv_audio_type_defs.h"
#include    "s_frameinfo.h"
#include    "s_sectinfo.h"
#include    "s_pulseinfo.h"
#include    "s_tdec_int_file.h"
#include    "s_tdec_int_chan.h"
#include    "ibstream.h"

#include    "s_hcb.h"
#include    "hcbtables.h"

#include    "get_pulse_data.h"
#include    "get_ics_info.h"

    /*----------------------------------------------------------------------------
    ; MACROS
    ; Define module specific macros here
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES
    ; Include all pre-processor statements here.
    ----------------------------------------------------------------------------*/
#define DIMENSION_4     4
#define DIMENSION_2     2

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

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/
    Int decode_huff_cw_tab1(
        BITS *pInputStream);

    Int decode_huff_cw_tab2(
        BITS *pInputStream);

    Int decode_huff_cw_tab3(
        BITS *pInputStream);

    Int decode_huff_cw_tab4(
        BITS *pInputStream);

    Int decode_huff_cw_tab5(
        BITS *pInputStream);

    Int decode_huff_cw_tab6(
        BITS *pInputStream);

    Int decode_huff_cw_tab7(
        BITS *pInputStream);

    Int decode_huff_cw_tab8(
        BITS *pInputStream);

    Int decode_huff_cw_tab9(
        BITS *pInputStream);

    Int decode_huff_cw_tab10(
        BITS *pInputStream);

    Int decode_huff_cw_tab11(
        BITS *pInputStream);

    Int decode_huff_scl(
        BITS          *pInputStream);

    Int infoinit(
        const  Int sampling_rate_idx,
        FrameInfo   **ppWin_seq_info,
        Int    *pSfbwidth128);

    void initScratchChannel(
        tDec_Int_File *pt_Scratch,
        tDec_Int_File *pVars,
        tDec_Int_Chan *pt_ChScratch[]);


    Int huffcb(
        SectInfo *pSect,
        BITS     *pInputStream,
        Int      *pSectbits,
        Int       tot_sfb,
        Int       sfb_per_sbk,
        Int       max_sfb);

    Int hufffac(
        FrameInfo   *pFrameInfo,
        BITS        *pInputStream,
        Int         *pGroup,
        Int          nsect,
        SectInfo    *pSect,
        Int          global_gain,
        Int         *pFactors,
        Int          huffBookUsed[]);

    Int huffspec_fxp(
        FrameInfo *pFrameInfo,
        BITS      *pInputStream,
        Int       nsect,
        SectInfo  *pSectInfo,
        Int       factors[],
        Int32     coef[],
        Int16     quantSpec[],
        Int16     tmp_spec[],
        const FrameInfo  *pLongFrameInfo,
        PulseInfo  *pPulseInfo,
        Int         qFormat[]);


    Int huffspec_fxp_parse_bits(
        FrameInfo *pFrameInfo,
        BITS      *pInputStream,
        Int       nsect,
        SectInfo  *pSectInfo);

    Int huffdecode(
        Int           id_syn_ele,
        BITS          *pInputStream,
        tDec_Int_File *pVars_0,
        tDec_Int_Chan *pChVars_0[]
    );


    void deinterleave(
        Int16          interleaved[],
        Int16        deinterleaved[],
        FrameInfo   *pFrameInfo);

    Int getics(
        Int             id_syn_ele,
        BITS            *pInputStream,
        Int             common_window,
        tDec_Int_File   *pVars,
        tDec_Int_Chan   *pChVars,
        Int             group[],
        Int             *pMax_sfb,
        Int             *pCodebookMap,
        TNS_frame_info  *pTnsInfo,
        FrameInfo       **pWinMap,
        PulseInfo       *pPulseInfo,
        SectInfo        sect[]);


    void  calc_gsfb_table(
        FrameInfo   *pFrameInfo,
        Int         group[]);

    Int getmask(
        FrameInfo   *pFrameInfo,
        BITS        *pInputStream,
        Int         *pGroup,
        Int         max_sfb,
        Int         *pMask);

    void getgroup(
        Int         group[],
        BITS        *pInputStream);


    /*----------------------------------------------------------------------------
    ; END
    ----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif
