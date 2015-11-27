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
 *  @file oscl_uuid_utils.h
 */

#ifndef OSCL_UUID_UTILS_H_INCLUDED
#define OSCL_UUID_UTILS_H_INCLUDED

#ifndef OSCL_STRING_UTILS_H
#include "oscl_string_utils.h"
#endif

#ifndef OSCL_STDSTRING_H_INCLUDED
#include "oscl_stdstring.h"
#endif

const char PV_CHAR_CLOSE_BRACKET = ')';
const char PV_CHAR_COMMA = ',';
static void SetOsclUuid(OsclUuid& uuid, const char* aUuidString)
{
    //Initialize all data members to 0 to begin with
    uuid.data1 = uuid.data2 = uuid.data3 = 0;

    for (int ii = 0; ii < 8; ++ii)
    {
        uuid.data4[ii] = 0;
    }

    if (!aUuidString)
    {
        return;
    }
    int uuidStrLen = oscl_strlen(aUuidString);

    if (uuidStrLen != 0)
    {
        const char* sptr = NULL, *eptr = NULL;
        int commaval = 0;
        sptr = aUuidString;
        ++sptr; //Increment over the starting parantheses '('
        eptr = sptr;
        for (int i = 0; i < uuidStrLen - 1 ; ++i)
        {
            if ((*eptr != PV_CHAR_COMMA) && (*eptr != PV_CHAR_CLOSE_BRACKET)) //Increment the pointer unless you get to the ","
            {                               //The comma signifies the beginning of the new OsclUuid parameter
                ++eptr;
            }
            else
            {
                sptr = sptr + 2;//Move over the 0x characters in the beginning of the hex value;
                ++commaval;
                switch (commaval)
                {
                    case 1:
                    {
                        PV_atoi(sptr , 'x', eptr - sptr, uuid.data1);
                        break;
                    }
                    case 2:
                    {
                        uint32 tempdata2 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata2);
                        uuid.data2 = (uint16)tempdata2;
                        break;
                    }
                    case 3:
                    {
                        uint32 tempdata3 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata3);
                        uuid.data3 = (uint16)tempdata3;
                        break;
                    }
                    case 4:
                    {
                        uint32 tempdata4_0 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_0);
                        uuid.data4[0] = (uint8)tempdata4_0;
                        break;
                    }
                    case 5:
                    {
                        uint32 tempdata4_1 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_1);
                        uuid.data4[1] = (uint8)tempdata4_1;
                        break;
                    }
                    case 6:
                    {
                        uint32 tempdata4_2 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_2);
                        uuid.data4[2] = (uint8)tempdata4_2;
                        break;
                    }
                    case 7:
                    {
                        uint32 tempdata4_3 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_3);
                        uuid.data4[3] = (uint8)tempdata4_3;
                        break;
                    }
                    case 8:
                    {
                        uint32 tempdata4_4 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_4);
                        uuid.data4[4] = (uint8)tempdata4_4;
                        break;
                    }
                    case 9:
                    {
                        uint32 tempdata4_5 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_5);
                        uuid.data4[5] = (uint8)tempdata4_5;
                        break;
                    }
                    case 10:
                    {
                        uint32 tempdata4_6 = 0;
                        PV_atoi(sptr , 'x', (eptr - sptr), tempdata4_6);
                        uuid.data4[6] = (uint8)tempdata4_6;
                        break;
                    }
                    case 11:
                    {
                        uint32 tempdata4_7 = 0;
                        PV_atoi(sptr, 'x', (eptr - sptr), tempdata4_7);
                        uuid.data4[7] = (uint8)tempdata4_7;
                        break;
                    }
                }
                if (*eptr == PV_CHAR_CLOSE_BRACKET) //Break from the loop on finding
                {
                    break;
                }
                ++eptr;
                sptr = eptr;
            }
        }
    }
}
#endif


