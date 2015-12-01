/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
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

 Filename: find_adts_syncword.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This function includes the function declaration for find_adts_syncword()

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef FIND_ADTS_SYNCWORD_H
#define FIND_ADTS_SYNCWORD_H

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "s_bits.h"
#include "pvmp4audiodecoder_api.h"


/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here.
----------------------------------------------------------------------------*/
#define LENGTH_VARIABLE_HEADER  28
#define LENGTH_FIXED_HEADER     28
#define LENGTH_CRC              16

#define LENGTH_SYNCWORD         16
#define ID_BIT_FILTER           0xFFF0
#define SYNCWORD_15BITS         0xFFF0

#define MASK_28BITS             0x0FFFFFFFL

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

#ifdef __cplusplus
extern "C"
{
#endif


    Int find_adts_syncword(
        UInt32 *pSyncword,
        BITS   *pInputStream,
        Int     syncword_length,
        UInt32  syncword_mask);

    Int validate_adts_syncword(
        UInt32 adts_var_header,
        UInt32 *pSyncword,
        BITS   *pInputStream,
        Int    *pInvoke);

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
; END
----------------------------------------------------------------------------*/
#endif
