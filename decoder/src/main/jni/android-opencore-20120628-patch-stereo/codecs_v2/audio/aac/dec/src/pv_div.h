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

 Filename: pv_div.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

------------------------------------------------------------------------------
*/

#ifndef PV_DIV_H
#define PV_DIV_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*----------------------------------------------------------------------------
    ; INCLUDES
    ----------------------------------------------------------------------------*/

#include "pv_audio_type_defs.h"

    /*----------------------------------------------------------------------------
    ; MACROS
    ; Define module specific macros here
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; EXTERNAL VARIABLES REFERENCES
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES AND SIMPLE TYPEDEF'S
    ----------------------------------------------------------------------------*/

    struct intg_div
    {
        Int32 quotient;
        Int32 shift_factor;
    };
    typedef struct intg_div Quotient;


    void pv_div(Int32 x, Int32 y, Quotient *quotient);

#ifdef __cplusplus
}
#endif

#endif  /* PV_DIV_H */
