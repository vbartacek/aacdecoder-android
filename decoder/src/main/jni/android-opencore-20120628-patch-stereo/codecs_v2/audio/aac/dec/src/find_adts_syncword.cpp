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

 Filename: find_adts_syncword.cpp

------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:
    pSyncword     = Pointer to variable containing the syncword that the
                    function should be scanning for in the buffer. [ UInt32 * ]

    pInputStream  = Pointer to a BITS structure, used by the function getbits
                    to retrieve data from the bitstream.  [ BITS * ]

    syncword_length = The length of the syncword. [ Int ]

    syncword_mask   = A mask to be applied to the bitstream before comparison
                      with the value pointed to by pSyncword. [ UInt32 ]

 Local Stores/Buffers/Pointers Needed:
    None

 Global Stores/Buffers/Pointers Needed:
    None

 Outputs:
    None

 Pointers and Buffers Modified:
    None

 Local Stores Modified:
    None

 Global Stores Modified:
    None

------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 This module scans the bitstream for a syncword of any length between 1 and 32.
 If certain bits in the syncword are to be ignored, that bit position should
 be set to 0 in both parameters *(pSyncword) and syncword_mask.  This allows
 for a syncword to be constructed out of non-contiguous bits.

 Upon finding the syncword's position in the bitstream, a value denoting the
 syncword's degree of deviance from being byte-aligned (byte_align_offset)
 is set in the structure pointed to by pInputStream.
 This is a value between 0 and 7.

 If no syncword is found, the function returns status == ERROR.

------------------------------------------------------------------------------
 REQUIREMENTS

 "Don't care" bits must be set to '0' in both *(pSyncword) and syncword_mask.

 This function should not be called if there are less than
 (8 + syncword_length) bits in the buffer.

------------------------------------------------------------------------------
 REFERENCES
 (1) ISO/IEC 13818-7:1997(E)
     Part 7
        Subpart 6.2 (Audio_Data_Transport_Stream frame, ADTS)

 (2) ISO/IEC 11172-3:1993(E)
     Part 3
        Subpart 2.4.3 The audio decoding process

------------------------------------------------------------------------------
 PSEUDO-CODE

    IF (pInputStream->usedBits <
            (pInputStream->availableBits + syncword_length) )

        max_search_length = (pInputStream->availableBits - pInputStream->usedBits);

        max_search_length = max_search_length - syncword_length;

        search_length = 0;

        adts_header =
        CALL getbits(syncword_length, pInputStream);
            MODIFYING pInputStream->usedBits
            RETURNING bits from bitstream of length (syncword_length)

        test_for_syncword = adts_header AND syncword_mask;
        test_for_syncword = test_for_syncword XOR syncword;

        WHILE ( (test_for_syncword != 0) && (search_length > 0) )

            search_length = search_length - 1;

            adts_header = adts_header << 1;
            adts_header = adts_header OR ...

            CALL getbits(syncword_length, pInputStream);
                MODIFYING pInputStream->usedBits
                RETURNING 1 bit from the bitstream

            test_for_syncword = adts_header AND syncword_mask;
            test_for_syncword = test_for_syncword XOR syncword;

        ENDWHILE

        IF (search_length == 0)
            status = ERROR;
        ENDIF

        *(pSyncword) = adts_header;

         pInputStream->byteAlignOffset =
             (pInputStream->usedBits - syncwordlength) AND 0x7;

    ELSE
        status = ERROR;
    ENDIF

    return (status);


------------------------------------------------------------------------------
*/


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "pv_audio_type_defs.h"
#include "s_bits.h"
#include "ibstream.h"
#include "find_adts_syncword.h"

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
Int find_adts_syncword(
    UInt32 *pSyncword,
    BITS   *pInputStream,
    Int     syncword_length,
    UInt32  syncword_mask)
{

    Int    status = SUCCESS;
    Int   search_length;
    UInt32 adts_header = 0;
    UInt32 test_for_syncword;
    UInt32 syncword = *(pSyncword);


    /*
     * Determine the maximum number of bits available to this function for
     * the syncword search.
     */
    if ((Int)pInputStream->usedBits <
            ((Int)pInputStream->availableBits - syncword_length))
    {
        search_length = (pInputStream->availableBits - pInputStream->usedBits);

        search_length -= syncword_length;

        adts_header  = getbits(syncword_length, pInputStream);

        /*
         * Mask the result in adts_header with the syncword_mask, so only the
         * bits relevant to syncword detection are compared to *(pSyncword).
         */
        test_for_syncword  = adts_header & syncword_mask;
        test_for_syncword ^= syncword;

        /*
         * Scan byte-by-byte through the bitstream, until the function either
         * runs out of bytes, or finds the syncword.
         */

        while ((test_for_syncword != 0) && (search_length > 0))
        {
            search_length -= 8;

            adts_header <<= 8;
            adts_header |= get9_n_lessbits(8, pInputStream);

            test_for_syncword  = adts_header & syncword_mask;
            test_for_syncword ^= syncword;
        }

        if (search_length <= 0)
        {
            status = MP4AUDEC_LOST_FRAME_SYNC;
        }

        *(pSyncword) = adts_header;

    } /* END if (pInputStream->usedBits < ...) */
    else
    {
        status = MP4AUDEC_LOST_FRAME_SYNC;
    }

    return (status);

} /* find_adts_syncword() */



/*----------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 This module get the distance in bytes between the current and next sync word
 then compare the content of the fix header (28 bits).

 If no match is found, the function returns
 status == MP4AUDEC_LOST_FRAME_SYNC, and reset the success counter *pInvoke

------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:

    adts_var_header 28 bit content of the variable part of the adts header
                    [UInt32]

    pSyncword     = Pointer to variable containing the syncword that the
                    function should be scanning for in the buffer. [ UInt32 * ]

    pInputStream  = Pointer to a BITS structure, used by the function getbits
                    to retrieve data from the bitstream.  [ BITS * ]

    pInvoke       = Pointer holding the success adts counter.  [ Int * ]


----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/


Int validate_adts_syncword(
    UInt32 adts_var_header,
    UInt32 *pSyncword,
    BITS   *pInputStream,
    Int    *pInvoke)
{

    UInt32 frame_length;
    UInt32 tmp;
    Int    status = SUCCESS;

    /*
     * frame_length is a 13-bit field which indicates the length,
     * in bytes, of the frame including error_check and headers.
     * This information can theoretically be used to help verify syncwords.
     * adts_var_header is 28 bits long, need to remove 13-bit conformed by
     * buffer fullnes and headerless frame info , and mask the rest
     */
    frame_length  = ((UInt)(adts_var_header >> 13)) & 0x1FFF;

    /* push current location, to validate 2 consecutive sync words */
    tmp = pInputStream->usedBits;

    /* Jump to next sync word, based on info on the header */
    pInputStream->usedBits += (frame_length << 3)
                              - LENGTH_FIXED_HEADER - LENGTH_VARIABLE_HEADER;


    if ((Int)pInputStream->usedBits <
            ((Int)pInputStream->availableBits - LENGTH_FIXED_HEADER))
    {
        uint32 temp = getbits(LENGTH_FIXED_HEADER, pInputStream);
        /*
         *  Check if fixed header in the very next predicted frame matches
         */
        if ((*(pSyncword) &  MASK_28BITS) != temp)
        {
            *(pInvoke) = 0;  /* reset valid adts frame counter */
            status = MP4AUDEC_LOST_FRAME_SYNC;  /* no match means a false lock on sync word */
        }
    }
    else
    {
        status = MP4AUDEC_LOST_FRAME_SYNC;  /* no match means a false lock on sync word */
    }
    /* pop current location */
    pInputStream->usedBits = tmp;

    return (status);

} /* validate_adts_syncword() */

