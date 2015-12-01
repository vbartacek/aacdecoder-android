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

 Filename: s_hcb.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 define the structure Hcb to store Huffman codebook information,
 this structure was originally defined in all.h

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef S_HCB_H
#define S_HCB_H


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include    "pv_audio_type_defs.h"
#include    "s_huffman.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
    typedef struct
    {
        Int     n;
        Int     dim;
        Int     mod;
        Int     off;
        Int     signed_cb;
    } Hcb;

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* S_HCB_H */

