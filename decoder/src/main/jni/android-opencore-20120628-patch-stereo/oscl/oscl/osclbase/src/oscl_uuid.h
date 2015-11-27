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
/**
 *  @file oscl_uuid.h
 *  @brief This file defines the OSCL UUID structure used for unique
 *  identifiers as well as the short (32-bit) identifiers OsclUid32.
 */

#ifndef OSCL_UUID_H_INCLUDED
#define OSCL_UUID_H_INCLUDED

#ifndef OSCL_BASE_MACROS_H_INCLUDED
#include "oscl_base_macros.h"
#endif

#ifndef OSCL_MEM_BASIC_FUNCTIONS_H
#include "oscl_mem_basic_functions.h"
#endif

// __cplusplus

#define EMPTY_UUID PVUuid(0,0,0,0,0,0,0,0,0,0,0)

typedef uint32 OsclUid32;
/**
 * OSCL UUID structure used for unique identification of modules and interfaces.
 */
struct OsclUuid
{
#define BYTES_IN_UUID_ARRAY 8

    OsclUuid()
    {
        oscl_memset(this, 0, sizeof(OsclUuid));
    }

    OsclUuid(uint32 l, uint16 w1, uint16 w2, uint8 b1, uint8 b2, uint8 b3,
             uint8 b4, uint8 b5, uint8 b6, uint8 b7, uint8 b8)
    {
        data1 = l;
        data2 = w1;
        data3 = w2;
        data4[0] = b1;
        data4[1] = b2;
        data4[2] = b3;
        data4[3] = b4;
        data4[4] = b5;
        data4[5] = b6;
        data4[6] = b7;
        data4[7] = b8;
    }

    OsclUuid(const OsclUuid &uuid)
    {
        oscl_memcpy(this, &uuid, sizeof(OsclUuid));
    }

    OsclUuid &operator=(const OsclUuid& src)
    {
        oscl_memcpy(this, &src, sizeof(OsclUuid));
        return *this;
    }

    bool operator==(const OsclUuid& src) const
    {
        if (data1 != src.data1 || data2 != src.data2 || data3 != src.data3)
        {
            return false;
        }

        for (int ii = 0; ii < 8; ++ii)
        {
            if (data4[ii] != src.data4[ii])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const OsclUuid &src) const
    {
        return !(*this == src);
    }

    uint32  data1;
    uint16  data2;
    uint16  data3;
    uint8   data4[BYTES_IN_UUID_ARRAY];
};

#endif

