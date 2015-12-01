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
------------------------------------------------------------------------------
   PacketVideo Corp.
   MP3 Decoder Library

   Filename: pvmp3_audio_type_defs.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This file was derived from a number of standards bodies. The type
 definitions below were created from some of the best practices observed
 in the standards bodies.

 This file is dependent on limits.h for defining the bit widths. In an
 ANSI C environment limits.h is expected to always be present and contain
 the following definitions:

     SCHAR_MIN
     SCHAR_MAX
     UCHAR_MAX

     INT_MAX
     INT_MIN
     UINT_MAX

     SHRT_MIN
     SHRT_MAX
     USHRT_MAX

     LONG_MIN
     LONG_MAX
     ULONG_MAX

------------------------------------------------------------------------------
*/

#ifndef PVMP3_AUDIO_TYPE_DEFS_H
#define PVMP3_AUDIO_TYPE_DEFS_H

#include    "oscl_base.h"


#ifndef Char
typedef int8        Char;
#endif

#ifndef UChar
typedef uint8       UChar;
#endif



/*----------------------------------------------------------------------------
; Define generic signed and unsigned int
----------------------------------------------------------------------------*/
#ifndef Int
typedef signed int  Int;
#endif

#ifndef UInt
typedef unsigned int    UInt;
#endif


/*----------------------------------------------------------------------------
; Define 16 bit signed and unsigned words
----------------------------------------------------------------------------*/


#ifndef Int16
typedef int16       Int16;
#endif

#ifndef INT16_MIN
#define INT16_MIN   (-32768)
#endif

#ifndef INT16_MAX
#define INT16_MAX   32767
#endif

#ifndef UInt16
typedef uint16      UInt16;

#endif


/*----------------------------------------------------------------------------
; Define 32 bit signed and unsigned words
----------------------------------------------------------------------------*/


#ifndef Int32
typedef int32       Int32;
#endif

#ifndef INT32_MIN
#define INT32_MIN   (-2147483647 - 1)
#endif
#ifndef INT32_MAX
#define INT32_MAX   2147483647
#endif

#ifndef UInt32
typedef uint32      UInt32;
#endif

#ifndef UINT32_MIN
#define UINT32_MIN  0
#endif
#ifndef UINT32_MAX
#define UINT32_MAX  0xffffffff
#endif


#ifndef INT_MAX
#define INT_MAX  INT32_MAX      /*  for 32 bit  */
#endif

/*----------------------------------------------------------------------------
; Define 64 bit signed and unsigned words
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; Define boolean type
----------------------------------------------------------------------------*/
#ifndef Bool
typedef int     Bool;
#endif
#ifndef FALSE
#define FALSE       0
#endif

#ifndef TRUE
#define TRUE        1
#endif

#ifndef OFF
#define OFF     0
#endif
#ifndef ON
#define ON      1
#endif

#ifndef NO
#define NO      0
#endif
#ifndef YES
#define YES     1
#endif

#ifndef SUCCESS
#define SUCCESS     0
#endif


#ifndef  NULL
#define  NULL       0
#endif


#endif  /* PVMP3_AUDIO_TYPE_DEFS_H */
