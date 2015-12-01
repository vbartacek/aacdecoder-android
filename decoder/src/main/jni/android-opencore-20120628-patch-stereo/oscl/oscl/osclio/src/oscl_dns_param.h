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

#ifndef OSCL_DNS_PARAM_H_INCLUDED
#define OSCL_DNS_PARAM_H_INCLUDED

#include "oscl_socket_types.h"
#include "oscl_dns_tuneables.h"
#include "oscl_namestring.h"
#include "oscl_dns.h"
#include "oscl_mutex.h"
#include "oscl_semaphore.h"

class OsclDNSRequestAO;
class OsclDNSRequest;

#if(PV_DNS_IS_THREAD)
/*
** Only the _OsclBasicAllocator is used in order to
** avoid the need to init memory manager in the DNS thread.
*/
typedef _OsclBasicAllocator TDNSRequestParamAllocator;
#else
typedef OsclMemAllocator TDNSRequestParamAllocator;
#endif

/*
** Base class for all DNS method parameter sets
** A thread-safe, reference-counted parameter set.
** A reference count is used since the data may need
** to persist after the request is canceled while still
** waiting on some blocking OS-level operation to complete.
*/
class DNSRequestParam
{
    public:

        virtual ~DNSRequestParam()
        {
#if(PV_DNS_IS_THREAD)
            iLock.Close();
            iStartup.Close();
#endif
        }

        void RemoveRef();

#if(PV_DNS_SERVER)
        void InThread();
#endif

        virtual void Destroy() = 0;

        TPVDNSFxn iFxn;
        OsclDNSRequest *iDNSRequest;

#if(PV_DNS_IS_THREAD)
        bool iThreadKillFlag;
        OsclMutex iLock;
        OsclSemaphore iStartup;
#endif


    protected:

        DNSRequestParam(TPVDNSFxn aFxn);

        uint32 iRefCount;
};


/*
** Parameters for GetHostByName request
*/
class GetHostByNameParam: public DNSRequestParam
{
    public:

        //Use this routine to create, use DNSRequestParam::RemoveRef when finished.
        static GetHostByNameParam* Create(const char *name, OsclNetworkAddress* &addr, Oscl_Vector<OsclNetworkAddress, OsclMemAllocator>* aAddressList);

        //from DNSRequestParam
        void Destroy();

        ~GetHostByNameParam();

        void PersistHostAddress(const OsclNetworkAddress& addr)
        {
            if (iAddressList && (iAddressList->size() < iAddressList->capacity()))
            {
                iAddressList->push_back(addr);
            }

            if (0 == oscl_strcmp(OSCL_STATIC_CAST(const char*, iAddr->ipAddr.Str()), ""))
                iAddr->ipAddr.Set(addr.ipAddr.Str());
        }

        bool canPersistMoreHostAddresses()
        {
            return (iAddressList && (iAddressList->size() < iAddressList->capacity())) || (0 == oscl_strcmp(OSCL_STATIC_CAST(const char*, iAddr->ipAddr.Str()), ""));
        }

        //request params.
        char *iName;
        OsclNetworkAddress *iAddr;
        Oscl_Vector<OsclNetworkAddress, OsclMemAllocator> *iAddressList;
        enum
        {
            addressListCapacity = 10
        };

    private:

        GetHostByNameParam(const char *name, OsclNetworkAddress* &addr, Oscl_Vector<OsclNetworkAddress, OsclMemAllocator>* aAddressList);


} ;


#endif

