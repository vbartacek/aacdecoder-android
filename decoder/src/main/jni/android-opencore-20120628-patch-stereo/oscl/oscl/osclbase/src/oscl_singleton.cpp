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


#include "oscl_base.h"
#if (OSCL_HAS_SINGLETON_SUPPORT)

#include "oscl_singleton.h"
#include "oscl_assert.h"
#include "oscl_lock_base.h"
#include "oscl_base_alloc.h"

// static object instantiation, alive with application
OsclSingletonRegistry::SingletonTable OsclSingletonRegistry::sSingletonTable;

OSCL_EXPORT_REF OsclAny* OsclSingletonRegistry::getInstance(uint32 ID, int32 &aError)
{
    OSCL_ASSERT(ID < OSCL_SINGLETON_ID_LAST);

    aError = 0;
    sSingletonTable.iSingletonLocks[ID].Lock();
    OsclAny* value = sSingletonTable.iSingletons[ID];
    sSingletonTable.iSingletonLocks[ID].Unlock();
    return value;
}

OSCL_EXPORT_REF void OsclSingletonRegistry::registerInstance(OsclAny* ptr, uint32 ID, int32 &aError)
{
    OSCL_ASSERT(ID < OSCL_SINGLETON_ID_LAST);

    aError = 0;
    sSingletonTable.iSingletonLocks[ID].Lock();
    sSingletonTable.iSingletons[ID] = ptr;
    sSingletonTable.iSingletonLocks[ID].Unlock();
}

OSCL_EXPORT_REF OsclAny* OsclSingletonRegistry::lockAndGetInstance(uint32 ID, int32 &aError)
{
    OSCL_ASSERT(ID < OSCL_SINGLETON_ID_LAST);

    aError = 0;
    sSingletonTable.iSingletonLocks[ID].Lock();
    OsclAny* value = sSingletonTable.iSingletons[ID];
    //leave this table entry locked

    return value;
}

OSCL_EXPORT_REF void OsclSingletonRegistry::registerInstanceAndUnlock(OsclAny* ptr, uint32 ID, int32 &aError)
{
    OSCL_ASSERT(ID < OSCL_SINGLETON_ID_LAST);

    aError = 0;

    //assume it's already locked.
    sSingletonTable.iSingletons[ID] = ptr;
    sSingletonTable.iSingletonLocks[ID].Unlock();
}

#endif //OSCL_HAS_SINGLETON_SUPPORT

