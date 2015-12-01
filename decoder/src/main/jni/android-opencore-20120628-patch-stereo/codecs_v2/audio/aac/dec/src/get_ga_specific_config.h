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

 Filename: get_ga_specific_config.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This file includes the function declaration for get_GA_specific_config.c

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef GET_GA_SPECIFIC_CONFIG_H
#define GET_GA_SPECIFIC_CONFIG_H

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include    "pv_audio_type_defs.h"
#include    "s_tdec_int_file.h"
#include    "s_bits.h"

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

/*----------------------------------------------------------------------------
; GLOBAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/
Int get_GA_specific_config(
    tDec_Int_File * const pVars,
    BITS    *pInputStream,
    UInt     channel_config,
    const tMP4AudioObjectType audioObjectType
);

/*----------------------------------------------------------------------------
; END
----------------------------------------------------------------------------*/
#endif


