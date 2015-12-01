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
#include "oscl_mem_mempool.h"

#define ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG 0

#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
#ifndef PVLOGGER_H_INCLUDED
#include "pvlogger.h"
#endif

#define PVMF_POOLALLOC_LOGERROR(m)  PVLOGGER_LOGMSG(PVLOGMSG_INST_REL,iLogger,PVLOGMSG_ERR,m);

class OsclMemPoolResizableAllocatorLogger
{
    public:

        OsclMemPoolResizableAllocatorLogger()
        {
            iLogger = PVLogger::GetLoggerObject("OsclMemPoolResizableAllocator");
            iAllocCount = 0;
            iMemPoolUsedBlockList.clear();
        }

        ~OsclMemPoolResizableAllocatorLogger()
        {
            while (iMemPoolUsedBlockList.empty() == false)
            {
                iMemPoolUsedBlockList.erase(iMemPoolUsedBlockList.begin());
            }
            iLogger = NULL;
        }

        void logInitialPool(Oscl_Vector<OsclMemPoolResizableAllocator::MemPoolBufferInfo*, OsclMemAllocator>& aMemPoolBufferList)
        {
            PVMF_POOLALLOC_LOGERROR((0, "*******"))
            PVMF_POOLALLOC_LOGERROR((0, "OsclMemPoolResizableAllocatorLogger::logInitialPool() this 0x%x", this));
            PVMF_POOLALLOC_LOGERROR((0, "Free list: aMemPoolBufferList length %d", aMemPoolBufferList.size()));
            for (uint32 i = 0; i < aMemPoolBufferList.size(); ++i)
            {
                OsclMemPoolResizableAllocator::MemPoolBufferInfo* bufferinfo = aMemPoolBufferList[i];
                PVMF_POOLALLOC_LOGERROR((0, "aMemPoolBufferList[%d] MemPoolBufferInfo 0x%x", i, bufferinfo));
                OsclMemPoolResizableAllocator::MemPoolBlockInfo* blockinfo = bufferinfo->iNextFreeBlock;
                while (blockinfo != NULL)
                {
                    PVMF_POOLALLOC_LOGERROR((0, "aMemPoolBufferList[%d] MemPoolBlockInfo 0x%x size %d (last byte 0x%x)",
                                             i, blockinfo, blockinfo->iBlockSize, (uint32)blockinfo + blockinfo->iBlockSize - 1));
                    // Go to the next free block
                    blockinfo = blockinfo->iNextFreeBlock;
                }
            }
            PVMF_POOLALLOC_LOGERROR((0, "*******"))
        }

        void logFreeAndUsedBlocks(Oscl_Vector<OsclMemPoolResizableAllocator::MemPoolBufferInfo*, OsclMemAllocator>& aMemPoolBufferList, uint32 aMemPoolPrevAllocBufferIndex, bool aPeriodic)
        {
            bool logOK = false;
            if (aPeriodic)
            {
                /*
                ((iAllocCount == 5) || (iAllocCount == 10) || (iAllocCount == 15) ||
                 (iAllocCount == 20) || (iAllocCount == 25) || (iAllocCount == 30) ||
                 (iAllocCount == 35) || (iAllocCount == 40) || (iAllocCount == 45) ||
                 (iAllocCount % 50 == 0)))
                */
                // log every 10th alloc
                if (iAllocCount % 10 == 0)
                {
                    logOK = true;
                }
            }
            else
            {
                logOK = true;
            }

            // MBDS holds onto many used blocks, thus we can isolate MBDS usecase by checking the vector size
            if (logOK /* && (iMemPoolUsedBlockList.size() > 4) */)
            {
                PVMF_POOLALLOC_LOGERROR((0, "@@@@@@@"))
                if (aPeriodic)
                {
                    PVMF_POOLALLOC_LOGERROR((0, "OsclMemPoolResizableAllocatorLogger::logFreeAndUsedBlocks() alloc count %d this 0x%x", iAllocCount, this));
                }
                else
                {
                    PVMF_POOLALLOC_LOGERROR((0, "OsclMemPoolResizableAllocatorLogger::logFreeAndUsedBlocks() NO FREE BLOCKS alloc count %d this 0x%x", iAllocCount, this));

                }
                PVMF_POOLALLOC_LOGERROR((0, "Free list: aMemPoolBufferList length %d aMemPoolPrevAllocBufferIndex %d",
                                         aMemPoolBufferList.size(), aMemPoolPrevAllocBufferIndex));
                for (uint32 i = 0; i < aMemPoolBufferList.size(); ++i)
                {
                    OsclMemPoolResizableAllocator::MemPoolBufferInfo* bufferinfo = aMemPoolBufferList[i];
                    PVMF_POOLALLOC_LOGERROR((0, "aMemPoolBufferList[%d] MemPoolBufferInfo 0x%x iPrevAllocBlock 0x%x",
                                             i, bufferinfo, bufferinfo->iPrevAllocBlock));
                    if (bufferinfo)
                    {
                        OsclMemPoolResizableAllocator::MemPoolBlockInfo* blockinfo = bufferinfo->iNextFreeBlock;
                        while (blockinfo != NULL)
                        {
                            PVMF_POOLALLOC_LOGERROR((0, "aMemPoolBufferList[%d] MemPoolBlockInfo 0x%x size %d (next free block 0x%x)",
                                                     i, blockinfo, blockinfo->iBlockSize, (uint32)blockinfo + blockinfo->iBlockSize));
                            // Go to the next free block
                            blockinfo = blockinfo->iNextFreeBlock;
                        }
                    }
                }
                PVMF_POOLALLOC_LOGERROR((0, "Used list: iMemPoolUsedBlockList length %d", iMemPoolUsedBlockList.size()));
                OsclMemPoolResizableAllocator::MemPoolBlockInfo* nextblock = NULL;
                uint32 gapCount = 0;
                for (i = 0; i < iMemPoolUsedBlockList.size(); ++i)
                {
                    OsclMemPoolResizableAllocator::MemPoolBlockInfo* blockinfo = iMemPoolUsedBlockList[i];
                    if ((nextblock != NULL) && (blockinfo != nextblock))
                    {
                        PVMF_POOLALLOC_LOGERROR((0, "Gap between iMemPoolUsedBlockList[%d] 0x%x and iMemPoolUsedBlockList[%d] 0x%x",
                                                 i - 1, nextblock, i, blockinfo));
                    }
                    PVMF_POOLALLOC_LOGERROR((0, "iMemPoolUsedBlockList[%d] MemPoolBlockInfo 0x%x size %d (next block 0x%x)",
                                             i, blockinfo, blockinfo->iBlockSize, (uint32)blockinfo + blockinfo->iBlockSize));

                    nextblock = (OsclMemPoolResizableAllocator::MemPoolBlockInfo*)((uint32)blockinfo + blockinfo->iBlockSize);
                }
                PVMF_POOLALLOC_LOGERROR((0, "@@@@@@@"))
            }

        }

        void addUsedBlockToList(OsclMemPoolResizableAllocator::MemPoolBlockInfo* aUsedBlock)
        {
            // add to used list
            iMemPoolUsedBlockList.push_back(aUsedBlock);
        }

        void removeUsedBlockToList(OsclMemPoolResizableAllocator::MemPoolBlockInfo* aUsedBlock)
        {
            // remove from used list
            for (uint32 i = 0; i < iMemPoolUsedBlockList.size(); ++i)
            {
                OsclMemPoolResizableAllocator::MemPoolBlockInfo* blockinfo = iMemPoolUsedBlockList[i];
                if (iMemPoolUsedBlockList[i] == aUsedBlock)
                {
                    // remove from list
                    iMemPoolUsedBlockList.erase(&iMemPoolUsedBlockList[i]);
                    break;
                }
            }
        }

        void incrementAllocCount()
        {
            // update count
            iAllocCount++;
        }

    private:
        Oscl_Vector<OsclMemPoolResizableAllocator::MemPoolBlockInfo*, OsclMemAllocator> iMemPoolUsedBlockList;
        PVLogger *iLogger;
        uint32 iAllocCount;
};

#endif

/**
 *  OsclMemPoolFixedChunkAllocator section
 **/

OSCL_EXPORT_REF OsclMemPoolFixedChunkAllocator::OsclMemPoolFixedChunkAllocator(const uint32 numchunk, const uint32 chunksize, Oscl_DefAlloc* gen_alloc, const uint32 chunkalignment) :
        iNumChunk(1), iChunkSize(0), iChunkSizeMemAligned(0), iChunkAlignment(chunkalignment),
        iMemPoolAllocator(gen_alloc), iMemPool(NULL), iMemPoolAligned(NULL),
        iCheckNextAvailableFreeChunk(false), iObserver(NULL),
        iNextAvailableContextData(NULL),
        iRefCount(1),
        iEnableNullPtrReturn(false)
{
    iNumChunk = numchunk;
    iChunkSize = chunksize;
    iChunkAlignment = chunkalignment;

    if (iNumChunk == 0)
    {
        iNumChunk = 1;
    }

    // if alignment paramater is used - set it to the nearest larger power of 2
    if ((iChunkAlignment > 0) && (iChunkAlignment < 0x80000000))
    {
        uint32 align = 1;
        while (align < iChunkAlignment)
        {
            align <<= 1;
        }
        iChunkAlignment = align;
    }

    // 8 byte alignment is the default. It shouldn't be larger than 1k
    if ((iChunkAlignment < 8) || (iChunkAlignment > 1024))
    {
        iChunkAlignment = 0;
    }

    if (iChunkSize > 0)
    {
        createmempool();
    }
}

OSCL_EXPORT_REF OsclMemPoolFixedChunkAllocator::~OsclMemPoolFixedChunkAllocator()
{
    // Decrement the ref count
    --iRefCount;

    // If ref count reaches 0 then destroy this object
    if (iRefCount <= 0)
    {
        destroymempool();
    }
}

OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::enablenullpointerreturn()
{
    iEnableNullPtrReturn = true;
}

OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::addRef()
{
    // Just increment the ref count
    ++iRefCount;
}

OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::removeRef()
{
    // Decrement the ref count
    --iRefCount;

    // If ref count reaches 0 then destroy this object automatically
    if (iRefCount <= 0)
    {
        OSCL_DELETE(this);
    }
}

OSCL_EXPORT_REF OsclAny* OsclMemPoolFixedChunkAllocator::allocate(const uint32 n)
{
    // Create the memory pool if it hasn't been created yet.
    // Use the allocation size, n, as the chunk size for memory pool
    if (iChunkSize == 0)
    {
        iChunkSize = n;
        createmempool();
    }
    else if (n > iChunkSize)
    {
        OSCL_LEAVE(OsclErrArgument);
        // OSCL_UNUSED_RETURN(NULL);    This statement was removed to avoid compiler warning for Unreachable Code

    }

    if (iFreeMemChunkList.empty())
    {
        // No free chunk is available
        if (iEnableNullPtrReturn)
        {
            return NULL;
        }
        else
        {
            OSCL_LEAVE(OsclErrNoResources);
        }
    }

    // Return the next available chunk from the pool
    OsclAny* freechunk = iFreeMemChunkList.back();
    // Remove the chunk from the free list
    iFreeMemChunkList.pop_back();
    addRef();
    return freechunk;
}


OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::deallocate(OsclAny* p)
{
    if (iMemPool == NULL)
    {
        // Memory pool hasn't been allocated yet so error
        OSCL_LEAVE(OsclErrNotReady);
    }

    uint8* ptmp = (uint8*)p;
    uint8* mptmp = (uint8*)iMemPoolAligned;

    if ((ptmp < mptmp) || ptmp >= (mptmp + iNumChunk*iChunkSizeMemAligned))
    {
        // Returned memory is not part of this memory pool
        OSCL_LEAVE(OsclErrArgument);
    }

    if (((ptmp - mptmp) % iChunkSizeMemAligned) != 0)
    {
        // Returned memory is not aligned to the chunk.
        OSCL_LEAVE(OsclErrArgument);
    }

#if(!OSCL_BYPASS_MEMMGT)
    // check if the same chunk was deallocated multiple times in a row
    uint32 ii;
    for (ii = 0; ii < iFreeMemChunkList.size(); ii++)
    {
        if (iFreeMemChunkList[ii] == p)
        {
            OSCL_LEAVE(OsclErrArgument);
        }
    }
#endif

    // Put the returned chunk in the free pool
    iFreeMemChunkList.push_back(p);

    // Notify the observer about free chunk available if waiting for such callback
    if (iCheckNextAvailableFreeChunk)
    {
        iCheckNextAvailableFreeChunk = false;
        if (iObserver)
        {
            iObserver->freechunkavailable(iNextAvailableContextData);
        }
    }

    // Decrement the refcount since deallocating succeeded
    removeRef();
}


OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::notifyfreechunkavailable(OsclMemPoolFixedChunkAllocatorObserver& obs, OsclAny* aContextData)
{
    iCheckNextAvailableFreeChunk = true;
    iObserver = &obs;
    iNextAvailableContextData = aContextData;
}

OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::CancelFreeChunkAvailableCallback()
{
    iCheckNextAvailableFreeChunk = false;
    iObserver = NULL;
    iNextAvailableContextData = NULL;
}

OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::createmempool()
{
    if (iChunkSize == 0 || iNumChunk == 0)
    {
        OSCL_LEAVE(OsclErrArgument);
    }

    if (iChunkAlignment > 0)
    {
        uint32 temp = iChunkAlignment - 1;
        iChunkSizeMemAligned = ((iChunkSize + temp) & (~temp));
    }
    else
    {
        // Create one block of memory for the memory pool
        iChunkSizeMemAligned = oscl_mem_aligned_size(iChunkSize);
    }

    int32 leavecode = 0;
    if (iMemPoolAllocator)
    {
        OSCL_TRY(leavecode, iMemPool = iMemPoolAllocator->ALLOCATE((iNumChunk * iChunkSizeMemAligned) + iChunkAlignment));
    }
    else
    {
        iMemPool = OSCL_MALLOC((iNumChunk * iChunkSizeMemAligned) + iChunkAlignment);
    }

    if (leavecode || iMemPool == NULL)
    {
        OSCL_LEAVE(OsclErrNoMemory);
    }

#if OSCL_MEM_FILL_WITH_PATTERN
    oscl_memset(iMemPool, 0x55, (iNumChunk*iChunkSizeMemAligned) + iChunkAlignment);
#endif

    // Set up the free mem chunk list vector
    iFreeMemChunkList.reserve(iNumChunk);
    uint8* chunkptr = (uint8*)iMemPool;

    // do the alignment if necessary
    if (iChunkAlignment > 0)
    {

        uint32 chunkptrAddr = (uint32) chunkptr;
        uint32 tempAlign = (iChunkAlignment - 1);
        uint32 difference = ((chunkptrAddr + tempAlign) & (~tempAlign)) - chunkptrAddr;

        chunkptr = chunkptr + difference;
        iMemPoolAligned = (OsclAny*) chunkptr;
    }
    else
    {
        iMemPoolAligned = iMemPool;
    }

    for (uint32 i = 0; i < iNumChunk; ++i)
    {
        iFreeMemChunkList.push_back((OsclAny*)chunkptr);
        chunkptr += iChunkSizeMemAligned;
    }
}


OSCL_EXPORT_REF void OsclMemPoolFixedChunkAllocator::destroymempool()
{
    // If ref count reaches 0 then destroy this object
    if (iRefCount <= 0)
    {
#if OSCL_MEM_CHECK_ALL_MEMPOOL_CHUNKS_ARE_RETURNED
        // Assert if all of the chunks were not returned
        OSCL_ASSERT(iFreeMemChunkList.size() == iNumChunk);
#endif

        iFreeMemChunkList.clear();

        if (iMemPool)
        {
            if (iMemPoolAllocator)
            {
                iMemPoolAllocator->deallocate(iMemPool);
            }
            else
            {
                OSCL_FREE(iMemPool);
            }

            iMemPool = NULL;
            iMemPoolAligned = NULL;
        }
    }
}



/**
 *  OsclMemPoolResizableAllocator section
 **/

#define OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER 10
#define OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN 0x55
#define OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN 0xAA
#define OSCLMEMPOOLRESIZABLEALLOCATOR_MIN_BUFFERSIZE 8

OSCL_EXPORT_REF OsclMemPoolResizableAllocator::OsclMemPoolResizableAllocator(uint32 aMemPoolBufferSize, uint32 aMemPoolBufferNumLimit, uint32 aExpectedNumBlocksPerBuffer, Oscl_DefAlloc* gen_alloc) :
        iMemPoolBufferSize(aMemPoolBufferSize),
        iMemPoolBufferNumLimit(aMemPoolBufferNumLimit),
        iExpectedNumBlocksPerBuffer(aExpectedNumBlocksPerBuffer),
        iMemPoolBufferAllocator(gen_alloc),
        iMemPoolPrevAllocBufferIndex(0xFFFFFFFF),
        iCheckNextAvailable(false),
        iRequestedNextAvailableSize(0),
        iNextAvailableContextData(NULL),
        iObserver(NULL),
        iCheckFreeMemoryAvailable(false),
        iRequestedAvailableFreeMemSize(0),
        iFreeMemContextData(NULL),
        iFreeMemPoolObserver(NULL),
        iRefCount(1),
        iEnableNullPtrReturn(false),
        iDebugLogger(NULL)
{
    OSCL_ASSERT(aMemPoolBufferSize > OSCLMEMPOOLRESIZABLEALLOCATOR_MIN_BUFFERSIZE);

    iMaxNewMemPoolBufferSz = 0;
    // Calculate and save the mem aligned size of buffer and block info header structures
    iBufferInfoAlignedSize = oscl_mem_aligned_size(sizeof(MemPoolBufferInfo));
    iBlockInfoAlignedSize = oscl_mem_aligned_size(sizeof(MemPoolBlockInfo));

    // Pre-allocate memory for vector
    if (iMemPoolBufferNumLimit > 0)
    {
        iMemPoolBufferList.reserve(iMemPoolBufferNumLimit);
    }
    else
    {
        iMemPoolBufferList.reserve(2);
    }

    // Determine the size of memory pool buffer and create one
    uint32 buffersize = oscl_mem_aligned_size(iMemPoolBufferSize) + iBufferInfoAlignedSize;
    if (iExpectedNumBlocksPerBuffer > 0)
    {
        buffersize += (iExpectedNumBlocksPerBuffer * iBlockInfoAlignedSize);
    }
    else
    {
        buffersize += (OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER * iBlockInfoAlignedSize);
    }

    addnewmempoolbuffer(buffersize);

#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
    iDebugLogger = OSCL_NEW(OsclMemPoolResizableAllocatorLogger, ());
    // log pool info
    if (NULL != iDebugLogger)
    {
        iDebugLogger->logInitialPool(iMemPoolBufferList);
    }
#endif
}

OsclMemPoolResizableAllocator::~OsclMemPoolResizableAllocator()
{
    destroyallmempoolbuffers();

#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
    if (NULL != iDebugLogger)
    {
        OSCL_DELETE(iDebugLogger);
    }
#endif
}


OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::enablenullpointerreturn()
{
    iEnableNullPtrReturn = true;
}

OSCL_EXPORT_REF OsclAny* OsclMemPoolResizableAllocator::allocate(const uint32 aNumBytes)
{
    MemPoolBlockInfo* freeblock = NULL;
    uint32 alignednumbytes = oscl_mem_aligned_size(aNumBytes);

    if (aNumBytes == 0)
    {
        OSCL_LEAVE(OsclErrArgument);
        // OSCL_UNUSED_RETURN(NULL);    This statement was removed to avoid compiler warning for Unreachable Code
    }

    // Find a free block that would accomodate the requested size with a block info header
    freeblock = findfreeblock(alignednumbytes + iBlockInfoAlignedSize);
    if (freeblock == NULL)
    {
        //We could not find a free buffer of requested size. This could be due to:
        //1) We have not created even a single parent chunk (or in other words this is the first allocation)
        //2) We are out of memory and might need to expand


        // Check if the requested size is bigger than the specified buffer size
        // Some of the users of this allocator, count on the allocator to expand beyond the original size
        // specified in the constructor. These users do NOT use setMaxSzForNewMemPoolBuffer to control expansion size.
        // If they did then it is wrong usage and we fail the allocation.
        // For example the allocator was intialized with 200KB size,
        // and overtime a request is made for say 300KB. Users of the allocator expect the allocator to do one of the following:
        // 1) If iMemPoolBufferNumLimit has been set and it has been reached then see
        // if one of older blocks can be freed up and we allocate a new block of 300KB. If we cannot then alloc will fail.
        // 2) If iMemPoolBufferNumLimit has not set then simply allocate a new block of 300 KB. Note that if iMemPoolBufferNumLimit
        // is not set allocator expands indefinitely.
        if (alignednumbytes > iMemPoolBufferSize)
        {
            if (iMaxNewMemPoolBufferSz != 0)
            {
                //wrong usage - fail allocation
                if (iEnableNullPtrReturn)
                {
                    return NULL;
                }
                else
                {
                    // Leave with resource limitation
                    OSCL_LEAVE(OsclErrNoResources);
                }
            }
            // Would need to create a new buffer to accomodate this request
            // Check if another buffer can be created
            if (iMemPoolBufferNumLimit > 0 && iMemPoolBufferList.size() >= iMemPoolBufferNumLimit)
            {
                // Check if there is a memory pool buffer that has no outstanding buffers
                // If present then remove it so a new one can be added
                bool emptybufferfound = false;
                for (uint32 j = 0; j < iMemPoolBufferList.size(); ++j)
                {
                    if (iMemPoolBufferList[j]->iNumOutstanding == 0)
                    {
                        // Free the memory
                        if (iMemPoolBufferAllocator)
                        {
                            iMemPoolBufferAllocator->deallocate((OsclAny*)iMemPoolBufferList[j]);
                        }
                        else
                        {
                            OSCL_FREE((OsclAny*)iMemPoolBufferList[j]);
                        }

                        // Remove the mempool buffer from the list
                        iMemPoolBufferList.erase(iMemPoolBufferList.begin() + j);
                        emptybufferfound = true;
                        break;
                    }
                }
                // Need to leave and return if empty buffer not found
                if (!emptybufferfound)
                {
                    if (iEnableNullPtrReturn)
                    {
                        return NULL;
                    }
                    else
                    {
                        // Leave with resource limitation
                        OSCL_LEAVE(OsclErrNoResources);
                    }
                }
                // Continue on to create a new buffer
                OSCL_ASSERT(iMemPoolBufferList.size() < iMemPoolBufferNumLimit);
            }
            // Determine the size of memory pool buffer and create one
            uint32 buffersize = alignednumbytes + iBufferInfoAlignedSize;
            if (iExpectedNumBlocksPerBuffer > 0)
            {
                buffersize += (iExpectedNumBlocksPerBuffer * iBlockInfoAlignedSize);
            }
            else
            {
                buffersize += (OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER * iBlockInfoAlignedSize);
            }

            MemPoolBufferInfo* newbuffer = addnewmempoolbuffer(buffersize);
            OSCL_ASSERT(newbuffer != NULL);
            OSCL_ASSERT(newbuffer->iNextFreeBlock != NULL);
            freeblock = (MemPoolBlockInfo*)(newbuffer->iNextFreeBlock);
            OSCL_ASSERT(freeblock != NULL);
            OSCL_ASSERT(freeblock->iBlockSize >= alignednumbytes);
        }
        else
        {
            // Check if another buffer can be created
            if (iMemPoolBufferNumLimit > 0 && iMemPoolBufferList.size() >= iMemPoolBufferNumLimit)
            {
                if (iEnableNullPtrReturn)
                {
                    return NULL;
                }
                else
                {
                    // Leave with resource limitation
                    OSCL_LEAVE(OsclErrNoResources);
                }
            }
            // Determine the size of memory pool buffer and create one
            // By default this allocator expands by iMemPoolBufferSize.
            // iMaxNewMemPoolBufferSz could specify the amount by which this allocator expands.
            // setMaxSzForNewMemPoolBuffer API can be used to control the expansion size.
            uint32 expansion_size = iMemPoolBufferSize;
            if (iMaxNewMemPoolBufferSz != 0)
            {
                expansion_size = iMaxNewMemPoolBufferSz;
            }
            //if alignednumbytes is larger than expansion_size, we cannot satisfy the request, so fail the allocation
            if (alignednumbytes > expansion_size)
            {
                if (iEnableNullPtrReturn)
                {
                    return NULL;
                }
                else
                {
                    // Leave with resource limitation
                    OSCL_LEAVE(OsclErrNoResources);
                }
            }
            uint32 buffersize = oscl_mem_aligned_size(expansion_size) + iBufferInfoAlignedSize;
            if (iExpectedNumBlocksPerBuffer > 0)
            {
                buffersize += (iExpectedNumBlocksPerBuffer * iBlockInfoAlignedSize);
            }
            else
            {
                buffersize += (OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER * iBlockInfoAlignedSize);
            }

            MemPoolBufferInfo* newbuffer = addnewmempoolbuffer(buffersize);
            OSCL_ASSERT(newbuffer != NULL);
            OSCL_ASSERT(newbuffer->iNextFreeBlock != NULL);
            freeblock = (MemPoolBlockInfo*)(newbuffer->iNextFreeBlock);
            OSCL_ASSERT(freeblock != NULL);
            OSCL_ASSERT(freeblock->iBlockSize >= alignednumbytes);
        }

    }

    // Use the free block and return the buffer pointer
    OsclAny* bufptr = allocateblock(*freeblock, alignednumbytes);
    if (bufptr)
    {
#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
        // add to used list
        if (NULL != iDebugLogger)
        {
            iDebugLogger->addUsedBlockToList(freeblock);
        }
#endif
        addRef();
        ++(freeblock->iParentBuffer->iNumOutstanding);
    }
    return bufptr;
}


OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::deallocate(OsclAny* aPtr)
{
    // Check that the returned pointer is from the memory pool
    if (validateblock(aPtr) == false)
    {
        OSCL_LEAVE(OsclErrArgument);
    }

    // Retrieve the block info header and validate the info
    uint8* byteptr = (uint8*)aPtr;
    MemPoolBlockInfo* retblock = (MemPoolBlockInfo*)(byteptr - iBlockInfoAlignedSize);
    OSCL_ASSERT(retblock != NULL);
    OSCL_ASSERT(retblock->iBlockPreFence == OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN);
    OSCL_ASSERT(retblock->iBlockPostFence == OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN);

#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
    // remove from used list
    if (NULL != iDebugLogger)
    {
        iDebugLogger->removeUsedBlockToList(retblock);
    }
#endif

    // Return the block to the memory pool buffer
    deallocateblock(*retblock);
    --(retblock->iParentBuffer->iNumOutstanding);

    // Check if user needs to be notified when block becomes available
    if (iCheckNextAvailable)
    {
        // Check if user is waiting for certain size
        if (iRequestedNextAvailableSize == 0)
        {
            // No so just make the callback
            iCheckNextAvailable = false;
            if (iObserver)
            {
                iObserver->freeblockavailable(iNextAvailableContextData);
            }
        }
        else
        {
            // Check if the requested size is available now
            if (findfreeblock(iRequestedNextAvailableSize + iBlockInfoAlignedSize) != NULL)
            {
                iCheckNextAvailable = false;
                if (iObserver)
                {
                    iObserver->freeblockavailable(iNextAvailableContextData);
                }
            }
            else if (iRequestedNextAvailableSize > iMemPoolBufferSize)
            {
                // The requested size is bigger than the set buffer size

                // Check if there is space to grow the buffer,
                if (iMemPoolBufferNumLimit == 0 || iMemPoolBufferList.size() < iMemPoolBufferNumLimit)
                {
                    // Available
                    iCheckNextAvailable = false;
                    if (iObserver)
                    {
                        iObserver->freeblockavailable(iNextAvailableContextData);
                    }
                }
                else
                {
                    // Not available so see if there is a buffer with
                    // no outstanding buffers which can be destroyed
                    // in the next allocate() call.
                    bool emptybufferfound = false;
                    for (uint32 j = 0; j < iMemPoolBufferList.size(); ++j)
                    {
                        if (iMemPoolBufferList[j]->iNumOutstanding == 0)
                        {
                            emptybufferfound = true;
                            break;
                        }
                    }

                    if (emptybufferfound)
                    {
                        iCheckNextAvailable = false;
                        if (iObserver)
                        {
                            iObserver->freeblockavailable(iNextAvailableContextData);
                        }
                    }
                }
            }
        }
    }
    if (iCheckFreeMemoryAvailable)
    {
        if (iRequestedAvailableFreeMemSize == 0)
        {
            // No so just make the callback
            iCheckFreeMemoryAvailable = false;
            if (iFreeMemPoolObserver)
            {
                iFreeMemPoolObserver->freememoryavailable(iFreeMemContextData);
            }
        }
        else
        {
            // Check if the requested size is available now
            if (getAvailableSize() >= iRequestedAvailableFreeMemSize)
            {
                iCheckFreeMemoryAvailable = false;
                if (iFreeMemPoolObserver)
                {
                    iFreeMemPoolObserver->freememoryavailable(iFreeMemContextData);
                }
            }
        }
    }

    // Decrement the refcount since deallocating succeeded
    removeRef();
}


OSCL_EXPORT_REF bool OsclMemPoolResizableAllocator::trim(OsclAny* aPtr, uint32 aBytesToFree)
{
    // Amount to free has to be aligned
    uint32 alignedbytestofree = oscl_mem_aligned_size(aBytesToFree);
    if (alignedbytestofree > aBytesToFree)
    {
        // Not aligned so decrease amount to free by one alignment size
        alignedbytestofree -= 8;
    }
    OSCL_ASSERT(alignedbytestofree <= aBytesToFree);

    // Check that the returned pointer is from the memory pool
    if (validateblock(aPtr) == false)
    {
        OSCL_LEAVE(OsclErrArgument);
        // OSCL_UNUSED_RETURN(false);   This statement was removed to avoid compiler warning for Unreachable Code
    }

    // Retrieve the block info header and validate the info
    uint8* byteptr = (uint8*)aPtr;
    MemPoolBlockInfo* resizeblock = (MemPoolBlockInfo*)(byteptr - iBlockInfoAlignedSize);
    OSCL_ASSERT(resizeblock != NULL);
    OSCL_ASSERT(resizeblock->iBlockPreFence == OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN);
    OSCL_ASSERT(resizeblock->iBlockPostFence == OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN);

    if ((resizeblock->iBlockSize - iBlockInfoAlignedSize) < alignedbytestofree)
    {
        // The bytes to free in the resize is bigger than the original buffer size
        OSCL_LEAVE(OsclErrArgument);
        // OSCL_UNUSED_RETURN(false);   This statement was removed to avoid compiler warning for Unreachable Code
    }

    if (alignedbytestofree < (iBlockInfoAlignedSize + OSCLMEMPOOLRESIZABLEALLOCATOR_MIN_BUFFERSIZE))
    {
        // The resizing cannot be done since the amount to free doesn't have
        // enough space to put in a block info header plus the minimum buffer for the new free block
        // So don't do anything and return
        return false;
    }

    // Create and fill in a block info header for the memory being freed back to memory pool
    MemPoolBlockInfo* freeblock = (MemPoolBlockInfo*)((uint8*)resizeblock + resizeblock->iBlockSize - alignedbytestofree);
    freeblock->iBlockPreFence = OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN;
    freeblock->iNextFreeBlock = NULL;
    freeblock->iPrevFreeBlock = NULL;
    freeblock->iBlockSize = alignedbytestofree;
    freeblock->iBlockBuffer = (uint8*)freeblock + iBlockInfoAlignedSize;
    freeblock->iParentBuffer = resizeblock->iParentBuffer;
    freeblock->iBlockPostFence = OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN;

    // Return the free block to the memory pool buffer
    deallocateblock(*freeblock);

    // Adjust the block info for the block being resized
    resizeblock->iBlockSize -= alignedbytestofree;
    return true;
}


OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::notifyfreeblockavailable(OsclMemPoolResizableAllocatorObserver& aObserver, uint32 aRequestedSize, OsclAny* aContextData)
{
    // Save the parameters for the next deallocate() call
    iCheckNextAvailable = true;
    iObserver = &aObserver;
    iRequestedNextAvailableSize = oscl_mem_aligned_size(aRequestedSize);
    iNextAvailableContextData = aContextData;
}

OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::CancelFreeChunkAvailableCallback()
{
    iCheckNextAvailable = false;
    iObserver = NULL;
    iRequestedNextAvailableSize = 0;
    iNextAvailableContextData = NULL;
}

OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::notifyfreememoryavailable(OsclMemPoolResizableAllocatorMemoryObserver& aObserver, uint32 aRequestedSize, OsclAny* aContextData)
{
    // Save the parameters for the next deallocate() call
    iCheckFreeMemoryAvailable = true;
    iFreeMemPoolObserver = &aObserver;
    iRequestedAvailableFreeMemSize = oscl_mem_aligned_size(aRequestedSize);
    iFreeMemContextData = aContextData;
}

OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::CancelFreeMemoryAvailableCallback()
{
    iCheckFreeMemoryAvailable = false;
    iFreeMemPoolObserver = NULL;
    iRequestedAvailableFreeMemSize = 0;
    iFreeMemContextData = NULL;
}

OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::addRef()
{
    // Just increment the ref count
    ++iRefCount;
}


OSCL_EXPORT_REF void OsclMemPoolResizableAllocator::removeRef()
{
    // Decrement the ref count
    --iRefCount;

    // If ref count reaches 0 then destroy this object automatically
    if (iRefCount <= 0)
    {
        OSCL_DELETE(this);
    }
}

OsclMemPoolResizableAllocator::MemPoolBufferInfo* OsclMemPoolResizableAllocator::addnewmempoolbuffer(uint32 aBufferAlignedSize)
{
    OSCL_ASSERT(aBufferAlignedSize > 0);
    OSCL_ASSERT(aBufferAlignedSize == oscl_mem_aligned_size(aBufferAlignedSize));

    // Allocate memory for one buffer
    uint8* newbuffer = NULL;
    if (iMemPoolBufferAllocator)
    {
        // Use the outside allocator
        newbuffer = (uint8*)iMemPoolBufferAllocator->ALLOCATE(aBufferAlignedSize);
    }
    else
    {
        // Allocate directly from heap
        newbuffer = (uint8*)OSCL_MALLOC(aBufferAlignedSize);
    }

    if (newbuffer == NULL)
    {
        OSCL_LEAVE(OsclErrNoMemory);
        // OSCL_UNUSED_RETURN(NULL);    This statement was removed to avoid compiler warning for Unreachable Code
    }

#if OSCL_MEM_FILL_WITH_PATTERN
    oscl_memset(newbuffer, 0x55, aBufferAlignedSize);
#endif

    // Fill in the buffer info header
    MemPoolBufferInfo* newbufferinfo = (MemPoolBufferInfo*)newbuffer;
    newbufferinfo->iBufferPreFence = OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN;
    newbufferinfo->iStartAddr = (OsclAny*)(newbuffer + iBufferInfoAlignedSize);
    newbufferinfo->iEndAddr = (OsclAny*)(newbuffer + aBufferAlignedSize - 1);
    newbufferinfo->iBufferSize = aBufferAlignedSize;
    newbufferinfo->iNumOutstanding = 0;
    newbufferinfo->iNextFreeBlock = (MemPoolBlockInfo*)(newbufferinfo->iStartAddr);
    newbufferinfo->iAllocatedSz = 0;
    newbufferinfo->iBufferPostFence = OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN;
    newbufferinfo->iPrevAllocBlock = NULL;

    // Put in one free block in the new buffer
    MemPoolBlockInfo* freeblockinfo = (MemPoolBlockInfo*)(newbufferinfo->iStartAddr);
    freeblockinfo->iBlockPreFence = OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN;
    freeblockinfo->iNextFreeBlock = NULL;
    freeblockinfo->iPrevFreeBlock = NULL;
    freeblockinfo->iBlockSize = aBufferAlignedSize - iBufferInfoAlignedSize;
    freeblockinfo->iBlockBuffer = (uint8*)freeblockinfo + iBlockInfoAlignedSize;
    freeblockinfo->iParentBuffer = newbufferinfo;
    freeblockinfo->iBlockPostFence = OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN;

    // Add the new buffer to the end of list
    iMemPoolBufferList.push_back(newbufferinfo);

    iMemPoolPrevAllocBufferIndex = iMemPoolBufferList.size() - 1;

    return newbufferinfo;
}


void OsclMemPoolResizableAllocator::destroyallmempoolbuffers()
{
    while (iMemPoolBufferList.empty() == false)
    {
        MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[0];
        // Check the buffer
        OSCL_ASSERT(bufferinfo != NULL);
        OSCL_ASSERT(bufferinfo->iBufferPreFence == OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN);
        OSCL_ASSERT(bufferinfo->iBufferPostFence == OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN);
        OSCL_ASSERT(bufferinfo->iNumOutstanding == 0);

        // Free the memory
        if (iMemPoolBufferAllocator)
        {
            iMemPoolBufferAllocator->deallocate((OsclAny*)bufferinfo);
        }
        else
        {
            OSCL_FREE((OsclAny*)bufferinfo);
        }

        iMemPoolBufferList.erase(iMemPoolBufferList.begin());
    }
}


OsclMemPoolResizableAllocator::MemPoolBlockInfo* OsclMemPoolResizableAllocator::findfreeblock(uint32 aBlockAlignedSize)
{
    OSCL_ASSERT(aBlockAlignedSize > 0);
    OSCL_ASSERT(aBlockAlignedSize == oscl_mem_aligned_size(aBlockAlignedSize));

    // Treat the mem pool of as if it is one circular buffer
    // to prevent fragmentation of the pool
    // In most cases, the caller deallocates the blocks in the order that they were allocated
    // If we skip around in the mem pool during allocation, because of resizable nature,
    // we will be leaving holes if different sizes in the mem pool.
    // The deallocated blocks are put back into the pool in address order.
    // iMemPoolPrevAllocBuffer keeps track of which buffer the previous allocation was made
    // MemPoolBufferInfo field iPrevAllocBlock keeps track of which block the previous allocation was made
    // Start from iMemPoolPrevAllocBuffer + iPrevAllocBlock for the next allocate

#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
    // free list and used list info periodically
    if (NULL != iDebugLogger)
    {
        iDebugLogger->logFreeAndUsedBlocks(iMemPoolBufferList, iMemPoolPrevAllocBufferIndex, true);
    }
#endif

    // Go through each mempool buffer and return the first free block that
    // is bigger than the specified size

    if (aBlockAlignedSize == 0)
    {
        // Request should be non-zero
        OSCL_LEAVE(OsclErrArgument);
        // OSCL_UNUSED_RETURN(NULL);    This statement was removed to avoid compiler warning for Unreachable Code
    }

    // the free blocks in each buffer are linked together in ascending order,
    // starting from the beginning of the buffer to end of the buffer
    uint32 numBuffers = iMemPoolBufferList.size();
    uint32 index = iMemPoolPrevAllocBufferIndex;
    while (numBuffers > 0)
    {
        MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[index];

        MemPoolBlockInfo* freeblockinfo = bufferinfo->iNextFreeBlock;
        MemPoolBlockInfo* prevblockinfo = bufferinfo->iPrevAllocBlock;
        // look first at the free blocks from iPrevAllocBlock to the end of the buffer
        // but note if there is a block that will fit somewhere
        bool blockFits = false;
        MemPoolBlockInfo* firstFreeBlock = NULL;
        while (freeblockinfo != NULL)
        {
            if ((freeblockinfo->iBlockSize/* - iBlockInfoAlignedSize*/) >= aBlockAlignedSize)
            {
                if (freeblockinfo > prevblockinfo)
                {
#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
                    // update count
                    if (NULL != iDebugLogger)
                    {
                        iDebugLogger->incrementAllocCount();
                    }
#endif
                    // This free block fits the request
                    // remember where this block is allocated from
                    // so the mem pool can be treated as a circular buffer
                    // to prevent fragmentation
                    bufferinfo->iPrevAllocBlock = freeblockinfo;
                    return freeblockinfo;
                }
                else if (firstFreeBlock == NULL)
                {
                    // save this block ptr
                    blockFits = true;
                    firstFreeBlock = freeblockinfo;
                }
            }
            // Go to the next free block
            freeblockinfo = freeblockinfo->iNextFreeBlock;
        }

        // did not find a free block from iPrevAllocBlock to end of buffer,
        // if we know there is a block that will fit,
        // look then from the beginning of the buffer
        // otherwise move on to the next buffer
        if (blockFits)
        {
            // remember where this block is allocated from
            // so the mem pool can be treated as a circular buffer
            // to prevent fragmentation
            bufferinfo->iPrevAllocBlock = firstFreeBlock;
            return firstFreeBlock;
        }

        // did not find anything in this buffer
        // look at the next buffer
        numBuffers--;
        index++;
        if (index >= iMemPoolBufferList.size())
        {
            // wrap around to the first buffer if needed
            index = 0;
        }
    }

#if ENABLE_OSCL_MEM_POOL_RESIZEABLE_ALLOCATOR_DEBUG_LOG
    // free list and used list info
    if (NULL != iDebugLogger)
    {
        iDebugLogger->logFreeAndUsedBlocks(iMemPoolBufferList, iMemPoolPrevAllocBufferIndex, false);
    }
#endif
    return NULL;
}


OsclAny* OsclMemPoolResizableAllocator::allocateblock(MemPoolBlockInfo& aBlockPtr, uint32 aNumAlignedBytes)
{
    OSCL_ASSERT(aNumAlignedBytes > 0);
    OSCL_ASSERT(aNumAlignedBytes == oscl_mem_aligned_size(aNumAlignedBytes));

    if (aNumAlignedBytes == 0)
    {
        OSCL_LEAVE(OsclErrArgument);
        // OSCL_UNUSED_RETURN(NULL);    This statement was removed to avoid compiler warning for Unreachable Code
    }

    // Remove the free block from the double linked list
    if (aBlockPtr.iPrevFreeBlock == NULL && aBlockPtr.iNextFreeBlock != NULL)
    {
        // Removing from the beginning of the free list
        aBlockPtr.iNextFreeBlock->iPrevFreeBlock = NULL;
        aBlockPtr.iParentBuffer->iNextFreeBlock = aBlockPtr.iNextFreeBlock;
    }
    else if (aBlockPtr.iPrevFreeBlock != NULL && aBlockPtr.iNextFreeBlock == NULL)
    {
        // Removing from the end of the free list
        aBlockPtr.iPrevFreeBlock->iNextFreeBlock = NULL;
    }
    else if (aBlockPtr.iPrevFreeBlock == NULL && aBlockPtr.iNextFreeBlock == NULL)
    {
        // Free list becomes empty so update the parent buffer's link
        aBlockPtr.iParentBuffer->iNextFreeBlock = NULL;
    }
    else
    {
        // Removing from middle of the free list
        aBlockPtr.iPrevFreeBlock->iNextFreeBlock = aBlockPtr.iNextFreeBlock;
        aBlockPtr.iNextFreeBlock->iPrevFreeBlock = aBlockPtr.iPrevFreeBlock;
    }

    aBlockPtr.iNextFreeBlock = NULL;
    aBlockPtr.iPrevFreeBlock = NULL;

    aBlockPtr.iParentBuffer->iAllocatedSz += aBlockPtr.iBlockSize;

    // Resize the block if too large
    uint32 extraspace = aBlockPtr.iBlockSize - iBlockInfoAlignedSize - aNumAlignedBytes;
    if (extraspace > (iBlockInfoAlignedSize + OSCLMEMPOOLRESIZABLEALLOCATOR_MIN_BUFFERSIZE))
    {
        trim(aBlockPtr.iBlockBuffer, extraspace);
    }

#if OSCL_MEM_FILL_WITH_PATTERN
    oscl_memset(aBlockPtr.iBlockBuffer, 0x55, (aBlockPtr.iBlockSize - iBlockInfoAlignedSize));
#endif
    return aBlockPtr.iBlockBuffer;
}


void OsclMemPoolResizableAllocator::deallocateblock(MemPoolBlockInfo& aBlockPtr)
{
    OSCL_ASSERT(aBlockPtr.iParentBuffer);

    MemPoolBufferInfo* bufferinfo = aBlockPtr.iParentBuffer;
    MemPoolBlockInfo* rightblockinfo = bufferinfo->iNextFreeBlock;
    MemPoolBlockInfo* leftblockinfo = NULL;

    // Go through the free block list and find the free block which would
    // become the right neighbor of the block being freed
    while (rightblockinfo != NULL)
    {
        if (&aBlockPtr < rightblockinfo)
        {
            break;
        }
        leftblockinfo = rightblockinfo;
        rightblockinfo = rightblockinfo->iNextFreeBlock;
    }

    // Check where the newly freed block is in the list
    if (leftblockinfo == NULL && rightblockinfo == NULL)
    {
        // The free block list is empty.
        // Trivial case so add to list and return to list without merge
        bufferinfo->iNextFreeBlock = &aBlockPtr;
        aBlockPtr.iNextFreeBlock = NULL;
        aBlockPtr.iPrevFreeBlock = NULL;
        aBlockPtr.iParentBuffer->iAllocatedSz -= aBlockPtr.iBlockSize;
        return;
    }
    else if (leftblockinfo != NULL && rightblockinfo == NULL)
    {
        // Adding to the end of the list
        OSCL_ASSERT(leftblockinfo->iNextFreeBlock == NULL);

        // Check that the newly freed block doesn't overlap with an existing free block
        if (((uint8*)leftblockinfo + leftblockinfo->iBlockSize) > (uint8*)&aBlockPtr)
        {
            OSCL_LEAVE(OsclErrArgument);
        }

        leftblockinfo->iNextFreeBlock = &aBlockPtr;
        aBlockPtr.iPrevFreeBlock = leftblockinfo;
        aBlockPtr.iNextFreeBlock = NULL;
    }
    else if (leftblockinfo == NULL && rightblockinfo != NULL)
    {
        // Adding to the beginning of the list
        OSCL_ASSERT(rightblockinfo->iPrevFreeBlock == NULL);

        // Check that the newly freed block doesn't overlap with an existing free block
        if (((uint8*)&aBlockPtr + aBlockPtr.iBlockSize) > (uint8*)rightblockinfo)
        {
            OSCL_LEAVE(OsclErrArgument);
        }

        bufferinfo->iNextFreeBlock = &aBlockPtr;
        rightblockinfo->iPrevFreeBlock = &aBlockPtr;
        aBlockPtr.iPrevFreeBlock = NULL;
        aBlockPtr.iNextFreeBlock = rightblockinfo;
    }
    else
    {
        // Adding to the middle of the list
        OSCL_ASSERT(leftblockinfo->iNextFreeBlock == rightblockinfo);
        OSCL_ASSERT(rightblockinfo->iPrevFreeBlock == leftblockinfo);

        // Check that the newly freed block doesn't overlap with the existing free blocks
        if (((uint8*)&aBlockPtr + aBlockPtr.iBlockSize) > (uint8*)rightblockinfo ||
                ((uint8*)leftblockinfo + leftblockinfo->iBlockSize) > (uint8*)&aBlockPtr)
        {
            OSCL_LEAVE(OsclErrArgument);
        }

        leftblockinfo->iNextFreeBlock = &aBlockPtr;
        rightblockinfo->iPrevFreeBlock = &aBlockPtr;
        aBlockPtr.iPrevFreeBlock = leftblockinfo;
        aBlockPtr.iNextFreeBlock = rightblockinfo;
    }
    aBlockPtr.iParentBuffer->iAllocatedSz -= aBlockPtr.iBlockSize;

    // Merge the newly freed block with neighbors if contiguous
    // Check which neighbors are contiguous in memory space
    bool rightadj = false;
    bool leftadj = false;
    if (aBlockPtr.iPrevFreeBlock)
    {
        MemPoolBlockInfo* leftnb = aBlockPtr.iPrevFreeBlock;
        if (((uint8*)leftnb + leftnb->iBlockSize) == (uint8*)&aBlockPtr)
        {
            leftadj = true;
        }
    }
    if (aBlockPtr.iNextFreeBlock)
    {
        MemPoolBlockInfo* rightnb = aBlockPtr.iNextFreeBlock;
        if (((uint8*)&aBlockPtr + aBlockPtr.iBlockSize) == (uint8*)rightnb)
        {
            rightadj = true;
        }
    }

    // Do the merge based on the check
    if (leftadj == false && rightadj == true)
    {
        // Merge the right neighbor with the newly freed block
        // Update newly freed block's size and remove the right neighbor from the list
        MemPoolBlockInfo* midblock = &aBlockPtr;
        MemPoolBlockInfo* rightblock = aBlockPtr.iNextFreeBlock;
        // Size update
        midblock->iBlockSize += rightblock->iBlockSize;
        // Right neighbor removal
        if (rightblock->iNextFreeBlock)
        {
            rightblock->iNextFreeBlock->iPrevFreeBlock = midblock;
        }
        midblock->iNextFreeBlock = rightblock->iNextFreeBlock;
    }
    else if (leftadj == true && rightadj == false)
    {
        // Merge the newly freed block with the left neighbor
        // Update the left neighbor's block size to include the newly freed block and
        // remove the newly freed block from the list
        MemPoolBlockInfo* midblock = &aBlockPtr;
        MemPoolBlockInfo* leftblock = aBlockPtr.iPrevFreeBlock;
        // Size update
        leftblock->iBlockSize += midblock->iBlockSize;
        // Newly freed block removal
        if (midblock->iNextFreeBlock)
        {
            midblock->iNextFreeBlock->iPrevFreeBlock = leftblock;
        }
        leftblock->iNextFreeBlock = midblock->iNextFreeBlock;
    }
    else if (leftadj == true && rightadj == true)
    {
        // Merge the newly freed block and right neighbor with the left neighbor
        // and remove the newly freed block and right neighbor from the list
        MemPoolBlockInfo* midblock = &aBlockPtr;
        MemPoolBlockInfo* leftblock = aBlockPtr.iPrevFreeBlock;
        MemPoolBlockInfo* rightblock = aBlockPtr.iNextFreeBlock;
        // Size update
        leftblock->iBlockSize += (midblock->iBlockSize + rightblock->iBlockSize);
        // Newly freed and right neighbor block removal
        if (rightblock->iNextFreeBlock)
        {
            rightblock->iNextFreeBlock->iPrevFreeBlock = leftblock;
        }
        leftblock->iNextFreeBlock = rightblock->iNextFreeBlock;
    }
}


bool OsclMemPoolResizableAllocator::validateblock(OsclAny* aBlockBufPtr)
{
    uint32 i = 0;

    if (aBlockBufPtr == NULL)
    {
        // Invalid pointer
        return false;
    }

    // Check if the pointer falls within one of the memory pool buffer's memory address
    for (i = 0; i < iMemPoolBufferList.size(); ++i)
    {
        MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[i];
        if (aBlockBufPtr > bufferinfo->iStartAddr && aBlockBufPtr < bufferinfo->iEndAddr)
        {
            break;
        }
    }
    if (i >= iMemPoolBufferList.size())
    {
        // Parent buffer is not part of this memory pool instance
        return false;
    }

    // Retrieve the block info header
    MemPoolBlockInfo* chkblock = (MemPoolBlockInfo*)((uint8*)aBlockBufPtr - iBlockInfoAlignedSize);

    if (chkblock->iBlockPreFence != OSCLMEMPOOLRESIZABLEALLOCATOR_PREFENCE_PATTERN ||
            chkblock->iBlockPostFence != OSCLMEMPOOLRESIZABLEALLOCATOR_POSTFENCE_PATTERN)
    {
        // Memory fence checking failed
        return false;
    }

    // Check the parent buffer is one in the list
    MemPoolBufferInfo* parentbuffer = chkblock->iParentBuffer;
    if (parentbuffer == NULL)
    {
        return false;
    }
    for (i = 0; i < iMemPoolBufferList.size(); ++i)
    {
        if (parentbuffer == iMemPoolBufferList[i])
        {
            break;
        }
    }
    if (i >= iMemPoolBufferList.size())
    {
        // Parent buffer is not part of this memory pool instance
        return false;
    }

    if (aBlockBufPtr < parentbuffer->iStartAddr || aBlockBufPtr > parentbuffer->iEndAddr)
    {
        // The address of the buffer is not part of the parent buffer
        return false;
    }

    if ((OsclAny*)((uint8*)chkblock + chkblock->iBlockSize - 1) > (parentbuffer->iEndAddr))
    {
        // The block size is too big
        return false;
    }

    return true;
}


OSCL_EXPORT_REF uint32 OsclMemPoolResizableAllocator::getBufferSize() const
{
    if (iMemPoolBufferNumLimit == 0)
        OSCL_LEAVE(OsclErrNotSupported);

    uint32 bufferSize = 0;
    for (uint32 i = 0; i < iMemPoolBufferList.size(); ++i)
    {
        MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[i];
        bufferSize += getMemPoolBufferSize(bufferinfo);
    }

    return bufferSize;
}

OSCL_EXPORT_REF uint32 OsclMemPoolResizableAllocator::getAllocatedSize() const
{
    //const uint32 expectedNumBlocksPerBuffer = iExpectedNumBlocksPerBuffer > 0 ? iExpectedNumBlocksPerBuffer : OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER;
    uint32 allocatedSz = 0;
    for (uint32 i = 0; i < iMemPoolBufferList.size(); ++i)
    {
        MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[i];
        allocatedSz += getMemPoolBufferAllocatedSize(bufferinfo);
    }
    return allocatedSz;
}

OSCL_EXPORT_REF uint32 OsclMemPoolResizableAllocator::getAvailableSize() const
{
    if (iMemPoolBufferNumLimit == 0)
        OSCL_LEAVE(OsclErrNotSupported);

    uint32 availableSize = 0;
    for (uint32 i = 0; i < iMemPoolBufferList.size(); ++i)
    {
        MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[i];
        uint32 memPoolBufferAvailableSz = 0;
        memPoolBufferAvailableSz = (getMemPoolBufferSize(bufferinfo) - getMemPoolBufferAllocatedSize(bufferinfo));
        availableSize += memPoolBufferAvailableSz;
    }

    return availableSize;
}

OSCL_EXPORT_REF uint32 OsclMemPoolResizableAllocator::getLargestContiguousFreeBlockSize() const
{
    uint32 blockSz = 0;

    if (iMemPoolBufferNumLimit > 0)
    {
        for (uint32 i = 0; i < iMemPoolBufferList.size(); ++i)
        {
            MemPoolBufferInfo* bufferinfo = iMemPoolBufferList[i];
            if (bufferinfo)
            {
                MemPoolBlockInfo* blockinfo = bufferinfo->iNextFreeBlock;
                while (blockinfo != NULL)
                {
                    if (blockinfo->iBlockSize > blockSz) blockSz = blockinfo->iBlockSize;
                    blockinfo = blockinfo->iNextFreeBlock;
                }
            }
        }
    }
    else
        OSCL_LEAVE(OsclErrNotSupported);

    if (blockSz > iBlockInfoAlignedSize) blockSz -= iBlockInfoAlignedSize;
    else blockSz = 0;

    return blockSz;
}

OSCL_EXPORT_REF bool OsclMemPoolResizableAllocator::setMaxSzForNewMemPoolBuffer(uint32 aMaxNewMemPoolBufferSz)
{
    bool retval = true;
    if (iMemPoolBufferNumLimit > 0)
        iMaxNewMemPoolBufferSz = aMaxNewMemPoolBufferSz;
    else
        retval = false;
    return retval;
}

uint32 OsclMemPoolResizableAllocator::getMemPoolBufferSize(MemPoolBufferInfo* aBufferInfo) const
{
    uint32 memPoolBufferSz = 0;

    if (aBufferInfo)
        memPoolBufferSz = aBufferInfo->iBufferSize;

    return memPoolBufferSz;
}

uint32 OsclMemPoolResizableAllocator::getMemPoolBufferAllocatedSize(MemPoolBufferInfo* aBufferInfo) const
{
    return aBufferInfo->iAllocatedSz;
    /*
    uint32 allocatedSz = 0;
    const uint32 expectedNumBlocksPerBuffer = iExpectedNumBlocksPerBuffer > 0 ? iExpectedNumBlocksPerBuffer : OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER;

    if (aBufferInfo)
    {
        if (aBufferInfo->iNumOutstanding > expectedNumBlocksPerBuffer)
        {
            allocatedSz = (aBufferInfo->iAllocatedSz - (expectedNumBlocksPerBuffer * iBlockInfoAlignedSize));
        }
        else
        {
            allocatedSz = (aBufferInfo->iAllocatedSz - (aBufferInfo->iNumOutstanding * iBlockInfoAlignedSize));
        }
    }
    return allocatedSz;
    */
}

uint32 OsclMemPoolResizableAllocator::memoryPoolBufferMgmtOverhead() const
{
    uint32 overheadBytes = iBufferInfoAlignedSize;
    if (iExpectedNumBlocksPerBuffer > 0)
    {
        overheadBytes += (iExpectedNumBlocksPerBuffer * iBlockInfoAlignedSize);
    }
    else
    {
        overheadBytes += (OSCLMEMPOOLRESIZABLEALLOCATOR_DEFAULT_NUMBLOCKPERBUFFER * iBlockInfoAlignedSize);
    }
    return overheadBytes;
}



