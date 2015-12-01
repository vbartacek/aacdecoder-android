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
#include "oscl_file_cache.h"
#include "oscl_mem.h"
#include "oscl_file_io.h"
#include "oscl_file_native.h"
#include "pvlogger.h"

OsclFileCache::OsclFileCache(Oscl_File& aContainer):
        iContainer(aContainer)
        , _curCache(NULL)
        , _fileSize(0)
        , _nativePosition(0)
        , iLogger(NULL)
{
    _movableCache.iContainer = this;
}

OsclFileCache::~OsclFileCache()
{
    Close();
}

int32 OsclFileCache::Open(uint32 mode, uint32 size)
//Called to open the cache for a newly opened file.
//The NativeOpen was just called prior to this and was successful.
{
    //should not be called with zero-size cache.
    OSCL_ASSERT(size > 0);

    //Save the mode
    _mode = mode;

    //open logger object only if logging is enabled on this
    //file
    if (iContainer.iLogger)
        iLogger = PVLogger::GetLoggerObject("OsclFileCache");
    else
        iLogger = NULL;

    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::Open mode %d size %d", this, mode, size));

    // Create the movable cache.
    // Re-allocate it if the size has changed.
    if (_movableCache.pBuffer
            && size != _movableCache.capacity)
    {
        OSCL_FREE(_movableCache.pBuffer);
        _movableCache.pBuffer = NULL;
    }
    if (!_movableCache.pBuffer
            && size > 0)
    {
        _movableCache.pBuffer = (uint8*)OSCL_MALLOC(size);
    }
    if (!_movableCache.pBuffer)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Open ERROR no memory %d", this));
        return (-1);//error
    }
    _movableCache.capacity = _movableCache.usableSize = size;
    _movableCache.filePosition = 0;
    _movableCache.updateStart = _movableCache.updateEnd = 0;
    _movableCache.currentPos = _movableCache.endPos = 0;

    //Position the cache at zero.
    SetCachePosition(0);

    //get initial file size & native position
    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::Open CallingNativeSize", this));
    _fileSize = iContainer.CallNativeSize();
    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::Open CallingNativeTell", this));
    _nativePosition = iContainer.CallNativeTell();

    return 0;
}

int32 OsclFileCache::UpdateFixedCaches()
//Process any queued requests to remove or add fixed caches.
{
    int32 error = 0;
    if (iContainer.iRemoveFixedCache.size())
    {
        for (uint32 i = 0; i < iContainer.iRemoveFixedCache.size(); i++)
        {
            for (uint32 j = 0; j < _fixedCaches.size(); j++)
            {
                if (_fixedCaches[j].filePosition < iContainer.iRemoveFixedCache[i])
                {
                    //fixed cache list is sorted, so we can end search now.
                    break;
                }
                else if (_fixedCaches[j].filePosition == iContainer.iRemoveFixedCache[i])
                {
                    //found it
                    if (_fixedCaches[j].IsUpdated())
                    {
                        int32 result = _fixedCaches[j].WriteUpdatesToFile();
                        if (result != 0)
                        {
                            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                            (0, "OsclFileCache(0x%x)::UpdateFixedCaches ERROR in WriteUpdatesToFile", this));
                            error = result;
                        }
                    }
                    if (_fixedCaches[j].pBuffer)
                    {
                        OSCL_FREE(_fixedCaches[j].pBuffer);
                        _fixedCaches[j].pBuffer = NULL;
                    }
                    _fixedCaches.erase(&_fixedCaches[j]);
                    break;
                }
            }
        }
        iContainer.iRemoveFixedCache.clear();
    }

    if (iContainer.iAddFixedCache.size())
    {
        for (uint32 i = 0; i < iContainer.iAddFixedCache.size(); i++)
        {
            if (!AddFixedCache(iContainer.iAddFixedCache[i]))
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::UpdateFixedCaches ERROR in AddFixedCache", this));
                error = (-1);
            }
        }
        iContainer.iAddFixedCache.clear();
    }
    return error;
}

//Enable/disable fixed cache array overlap checks.
//This is expensive, so it is normally disabled.
#define OVERLAP_CHECKS 0

//Add a new fixed cache, maintaining sorted order of the list.
OSCL_EXPORT_REF OsclFileCacheBuffer* OsclFileCache::AddFixedCache(const Oscl_File::OsclFixedCacheParam& aParam)
{
#if (OVERLAP_CHECKS)
    //Check for overlap with any existing fixed cache.
    //Caller should ensure there is no overlap.
    if (_fixedCaches.size())
    {
        for (uint32 i = 0; i < _fixedCaches.size(); i++)
        {
            if (_fixedCaches[i].Contains(aParam.iFilePosition))
            {
                //given start position falls in an existing cache.
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::AddFixedCache ERROR Overlap!", this));
                return NULL;
            }
            if (aParam.Contains(_fixedCaches[i].filePosition))
            {
                //some cache start position falls in this range.
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::AddFixedCache ERROR Overlap!", this));
                return NULL;
            }
            //verify sort while we're at it
            if (i > 0)
            {
                if (_fixedCaches[i].filePosition < _fixedCaches[i-1].filePosition)
                {
                    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                    (0, "OsclFileCache(0x%x)::AddFixedCache ERROR Sort!", this));
                    return NULL;
                }
            }
        }
    }
#endif

    //Check for overlap with current movable cache.
    if (_movableCache.Contains(aParam.iFilePosition)
            || aParam.Contains(_movableCache.filePosition))
    {
        //There is overlap. Dump the movable cache.
        //@TODO might be able to preserve some of the data here instead of complete
        //cache dump.

        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::AddFixedCache Movable Cache Overlap, dumping data", this));

        if (_movableCache.IsUpdated())
        {
            int32 result = _movableCache.WriteUpdatesToFile();
            if (result != 0)
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::AddFixedCache ERROR in WriteUpdatesToFile!", this));
                return NULL;
            }
        }
        _movableCache.endPos = _movableCache.currentPos = 0;
        _movableCache.filePosition = 0;
        _movableCache.usableSize = _movableCache.capacity;
    }


    //Create new entry
    OsclFileCacheBuffer fc;
    fc.iContainer = this;
    fc.isFixed = true;
    fc.pBuffer = (uint8*)OSCL_MALLOC(aParam.iSize);
    if (!fc.pBuffer)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::AddFixedCache ERROR no memory %d", this));
        return NULL;//error
    }
    fc.capacity = fc.usableSize = aParam.iSize;
    fc.filePosition = aParam.iFilePosition;

    //Add this entry, maintaining sorted order.
    int32 insertIndex = (-1);
    if (_fixedCaches.size())
    {
        for (uint32 i = 0; i < _fixedCaches.size(); i++)
        {
            if (fc.filePosition <= _fixedCaches[i].filePosition)
            {
                insertIndex = i;
                break;
            }
        }
    }
    if (insertIndex >= 0)
    {
        _fixedCaches.insert(&_fixedCaches[insertIndex], fc);
        return &_fixedCaches[insertIndex];
    }
    else
    {
        _fixedCaches.push_back(fc);
        return &_fixedCaches[_fixedCaches.size()-1];
    }
}

void OsclFileCache::Close()
{
    //flush any cache updates & free the buffers
    if (_movableCache.pBuffer)
    {
        _movableCache.WriteUpdatesToFile();
        OSCL_FREE(_movableCache.pBuffer);
        _movableCache.pBuffer = NULL;
        _movableCache.capacity = _movableCache.usableSize = 0;
    }

    for (uint32 i = 0; i < _fixedCaches.size(); i++)
    {
        _fixedCaches[i].WriteUpdatesToFile();
        if (_fixedCaches[i].pBuffer)
        {
            OSCL_FREE(_fixedCaches[i].pBuffer);
            _fixedCaches[i].pBuffer = NULL;
            _fixedCaches[i].capacity = _fixedCaches[i].usableSize = 0;
        }
    }
    _fixedCaches.clear();
}

/**
 * Read
 * Reads data from the file cache buffer and copies into
 * the buffer supplied (outputBuffer)
 *
 * @param outputBuffer pointer to buffer of type void
 * @param size   element size in bytes
 * @param numelements
 *               max number of elements to read
 *
 * @return returns the number of full elements actually read, which
 *         may be less than count if an error occurs or if the end
 *         of the file is encountered before reaching count.
 */
uint32 OsclFileCache::Read(void* outputBuffer, uint32 size, uint32 numelements)
{
    if (!outputBuffer)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Read ERROR invalid arg ", this));
        return 0;
    }

    //check for a valid read mode
    if ((_mode & Oscl_File::MODE_READWRITE)
            || (_mode & Oscl_File::MODE_READ)
            || (_mode & Oscl_File::MODE_APPEND)
            || (_mode & Oscl_File::MODE_READ_PLUS))
    {
        ;//ok to write
    }
    else
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Read ERROR invalid mode for reading ", this));
        return 0;//invalid mode.
    }

    uint8* destBuf = (uint8*)(outputBuffer);

    uint32 bytesToRead = numelements * size;

    // If file is smaller than requested data amount, reduce bytesToRead to the lowest multiple
    // of size that we can read
    uint32 bytesLeftInFile = (uint32)(FileSize() - Tell());
    if (bytesToRead > bytesLeftInFile)
    {
        numelements = bytesLeftInFile / size;
        bytesToRead = numelements * size;
    }

    if (bytesToRead)
    {
        //prep current cache for reading
        int32 retval = _curCache->PrepRead();
        if (retval != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::Read ERROR PrepRead failed ", this));
            return 0;
        }
    }

    //pull data out of the cache until we run out, then re-fill the cache
    //as needed until we get the desired amount.

    while (bytesToRead > 0)
    {
        OSCL_ASSERT(_curCache->endPos >= _curCache->currentPos);
        uint32 bytesInCache = (uint32)(_curCache->endPos - _curCache->currentPos);

        if (bytesInCache > 0)
        {
            //pull out either all data in cache, or number of bytes required,
            //whichever is less
            uint32 thisRead = (bytesInCache > bytesToRead) ? bytesToRead : bytesInCache;

            oscl_memcpy(destBuf, _curCache->pBuffer + _curCache->currentPos, thisRead);
            bytesToRead -= thisRead;
            destBuf += thisRead;

            //update virtual position
            _curCache->currentPos += thisRead;
        }
        else
        {
            //no more data-- reposition & refill the cache
            int32 retval = SetCachePosition(Tell());
            if (retval != 0)
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::Read ERROR SetCachePosition failed ", this));
                break;//error!
            }
            retval = _curCache->PrepRead();
            if (retval != 0)
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::Read ERROR PrepRead failed ", this));
                break;//error!
            }

            //When at EOF, cache will be empty after fillcache,
            //so break out of loop.
            if (_curCache->endPos - _curCache->currentPos == 0)
                break;
        }
    }

    //return number of whole elements read.
    return (size) ? ((size*numelements - bytesToRead) / size) : 0;

}


/**
 * Write
 * Writes data from the input buffer into
 * the buffer supplied (inputBuffer)
 *
 * @param inputBuffer pointer to buffer of type void
 * @param size   element size in bytes
 * @param numelements
 *               number of elements to write
 *
 * @return returns the number of elements written
 */
uint32 OsclFileCache::Write(const void* inputBuffer, uint32 size, uint32 numelements)
{
    if (inputBuffer == NULL)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Write ERROR invalid arg ", this));
        return 0;
    }

    //write the data only in the mode we are permitted to write
    if ((_mode & Oscl_File::MODE_READWRITE)
            || (_mode & Oscl_File::MODE_APPEND)
            || (_mode & Oscl_File::MODE_READ_PLUS))
    {
        ;//ok to write
    }
    else
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Write ERROR invalid mode for writing ", this));
        return 0;//invalid mode.
    }

    //In Append mode, write always happens at the end of file,
    //so relocate the cache now if needed.
    if ((_mode & Oscl_File::MODE_APPEND)
            && (Tell() != FileSize()))
    {
        int32 result = SetCachePosition(FileSize());
        if (result != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::Write ERROR SetCachePosition failed. ", this));
            return 0;
        }
    }

    //prep current cache for writing
    int32 result = _curCache->PrepWrite();
    if (result != 0)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Write ERROR PrepWrite failed. ", this));
        return 0;
    }

    uint8* srcBuf = (uint8*)(inputBuffer);
    uint32 bytesToWrite = size * numelements;

    //write into cache, flushing as needed when it fills up.

    while (bytesToWrite > 0)
    {
        OSCL_ASSERT(_curCache->usableSize >= _curCache->currentPos);
        uint32 spaceInCache = _curCache->usableSize - _curCache->currentPos;
        if (spaceInCache > 0)
        {
            //write to cache
            uint32 thisWrite = (spaceInCache > bytesToWrite) ? bytesToWrite : spaceInCache;

            oscl_memcpy((_curCache->pBuffer + _curCache->currentPos), srcBuf, thisWrite);
            bytesToWrite -= thisWrite;
            srcBuf += thisWrite;

            //keep track of the range of data in the cache that has been updated.
            if (_curCache->updateEnd == _curCache->updateStart)
            {
                //first update in this cache
                _curCache->updateStart = _curCache->currentPos;
                _curCache->updateEnd = _curCache->currentPos + thisWrite;
            }
            else
            {
                //cache has already been updated.  Expand the updated range
                //to include this update.

                if (_curCache->currentPos < _curCache->updateStart)
                    _curCache->updateStart = _curCache->currentPos;

                if ((_curCache->currentPos + thisWrite) > _curCache->updateEnd)
                    _curCache->updateEnd = _curCache->currentPos + thisWrite;
            }

            //update the virtual position.
            _curCache->currentPos += thisWrite;

            //extend the end of cache data if needed
            if (_curCache->endPos < _curCache->currentPos)
                _curCache->endPos = _curCache->currentPos;

            //extend the virtual file size if needed.
            if (_fileSize < (TOsclFileOffset)(_curCache->filePosition + _curCache->endPos))
                _fileSize = _curCache->filePosition + _curCache->endPos;

            //consistency checks.  if these asserts fire, there is
            //a logic error.
            OSCL_ASSERT(_curCache->updateEnd >= _curCache->updateStart);
            OSCL_ASSERT(_curCache->endPos >= _curCache->currentPos);
        }
        else
        {
            //entire cache is full-- re-set cache to current vpos and prep
            //for write
            int32 retval = SetCachePosition(Tell());
            if (retval != 0)
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::Write ERROR SetCachePosition failed ", this));
                break;//error!
            }
            retval = _curCache->PrepWrite();
            if (retval != 0)
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::Write ERROR PrepWrite failed ", this));
                break;//error!
            }
        }
    }

    //return number of whole elements written.
    return (size) ? ((size*numelements - bytesToWrite) / size) : 0;

}


/**
 * Seek
 *
 * @param [in] offset from origin
 * @param [in] origin: either SEEKSET, SEEKCUR, or SEEKEND
 *
 * @return 0 for success.
 */
int32 OsclFileCache::Seek(TOsclFileOffset offset, Oscl_File::seek_type origin)
{
    //figure out the file position we're trying to seek to
    TOsclFileOffset pos;
    switch (origin)
    {
        case Oscl_File::SEEKCUR:
            pos = Tell() + offset;
            break;
        case Oscl_File::SEEKSET:
            pos = 0 + offset;
            break;
        case Oscl_File::SEEKEND:
            pos = FileSize() + offset;
            break;
        default:
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::Seek ERROR invalid origin %d", this, origin));
            return (-1);//error-- invalid origin!
    }

    //don't allow seeking outside valid file size
    if (pos < 0 || pos > FileSize())
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Seek ERROR invalid seek position %d", this, pos));
        return -1;//error
    }

    if (_curCache->Contains(pos))
    {
        //Seek in cur cache
        _curCache->currentPos = (uint32)(pos - _curCache->filePosition);
    }
    else
    {
        //Seek outside cache
        int32 retval = SetCachePosition(pos);
        if (retval != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::Seek ERROR SetPosition error %d", this, retval));
            return retval;//error
        }
    }
    return 0;
}


/**
 * Flush
 * Flush file to disk.
 * After this call, previously cached data
 * is still available.
 *
 * @param void
 *
 * @return 0 for success.
 */
int32 OsclFileCache::Flush()
{
    bool nativeFlush = false;

    //Write all cache updates to file
    //Note: don't reset caches here, since
    //we may still want to use the data
    //in read operations.
    if (_movableCache.IsUpdated())
    {
        int32 result = _movableCache.WriteUpdatesToFile();
        if (result != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::Flush ERROR WriteUpdatesToFile failed", this));
            return result;
        }
        nativeFlush = true;
    }
    for (uint32 i = 0; i < _fixedCaches.size(); i++)
    {
        if (_fixedCaches[i].IsUpdated())
        {
            int32 result = _fixedCaches[i].WriteUpdatesToFile();
            if (result != 0)
            {
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::Flush ERROR WriteUpdatesToFile failed", this));
                return result;
            }
            nativeFlush = true;
        }
    }

    //Flush to disk if there were any updates.
    if (nativeFlush)
    {

        //flush file to disk.
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Flush CallingNativeFlush", this));
        int32 retval = iContainer.CallNativeFlush();
        if (retval != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::Flush ERROR CallNativeFlush failed", this));
        }

        //not sure if native file position is affected
        //by a native flush, so query now.
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::Flush CallingNativeTell", this));
        _nativePosition = iContainer.CallNativeTell();

        return retval;
    }
    else
    {
        //no updates in cache since last flush
        //so nothing is needed.

        return 0; //success!
    }
}


/**
 * SetCachePosition
 *
 * Select _curCache and set position to
 * the input position.
 *
 * @param [in] aNewPos: file position.
 *
 * return 0 on success.
 *
*/
int32 OsclFileCache::SetCachePosition(TOsclFileOffset aPos)
{
    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::SetCachePosition pos %d size %d", this, aPos));

    //Remove or add any fixed caches
    if (iContainer.iAddFixedCache.size()
            || iContainer.iRemoveFixedCache.size())
    {
        int32 result = UpdateFixedCaches();
        if (result != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::SetCachePosition ERROR in UpdateFixedCaches %d"
                             , this, result));
            return result;
        }
    }

    //Choose current cache
    if (iContainer.iCacheObserver)
    {
        //Invoke observer's algorithm if any was provided.

        _curCache = iContainer.iCacheObserver->ChooseCurCache(*this, aPos);
        if (!_curCache)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::SetCachePosition ERROR in ChooseCurCache"
                             , this));
            return (-1);
        }
    }
    else
    {
        //Default algorithm to choose current cache.

        _curCache = NULL;

        //First try to use a fixed cache.
        if (_fixedCaches.size())
        {
            for (uint32 i = 0; i < _fixedCaches.size(); i++)
            {
                if (aPos < _fixedCaches[i].filePosition)
                {
                    //fixed cache list is sorted, so we can end search now.
                    break;
                }
                else if (_fixedCaches[i].Contains(aPos))
                {
                    _curCache = &_fixedCaches[i];
                    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iLogger, PVLOGMSG_DEBUG,
                                    (0, "OsclFileCache(0x%x)::SetCachePosition Using fixed cache index %d, pos %d size %d"
                                     , this, i, (int32)_fixedCaches[i].filePosition, _fixedCaches[i].usableSize));
                    break;
                }
            }
        }

        //If no fixed cache works, use the movable cache.
        if (!_curCache)
        {
            _curCache = &_movableCache;
        }
    }

    //Set position in the chosen cache.
    return _curCache->SetPosition(aPos);
}

/**
 * SetPosition
 *
 * Set working position in this cache to the input
 * position.  For movable cache, may have a side-effect
 * of flushing current updates to the file.
 *
 * Note: cache is not necessarily usable for reads & writes
 * after this routine.  Use PrepRead or PrepWrite
 * to ensure valid data.
 *
 * @param [in] aNewPos: file position.
 *
 * return 0 on success.
 *
*/
int32 OsclFileCacheBuffer::SetPosition(TOsclFileOffset aNewPos)
{
    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::SetPosition newpos %d", this, aNewPos));

    if (Contains(aNewPos))
    {
        //new position is in current usable size
        currentPos = (uint32)(aNewPos - filePosition);
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::SetPosition adjusted position in cache"));
    }
    else
    {
        //relocating the cache
        if (isFixed)
        {
            //unexpected!
            OSCL_ASSERT(0);
            return -1;
        }
        else
        {
            //Movable cache

            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::SetPosition relocating movable cache"));

            //flush any updated data currently in cache.
            if (IsUpdated())
            {
                int32 result = WriteUpdatesToFile();
                if (result != 0)
                {
                    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                                    (0, "OsclFileCache(0x%x)::SetPosition ERROR FlushUpdatesToFile failed", this));
                    return result;//error!
                }
            }

            //reset the virtual position and the cache location.
            filePosition = aNewPos;
            currentPos = 0;

            //cache is empty
            endPos = 0;

            //Adjust the capacity downward to avoid overlapping any fixed cache
            usableSize = capacity;
            if (iContainer->_fixedCaches.size())
            {
                for (uint32 i = 0; i < iContainer->_fixedCaches.size(); i++)
                {
                    if (Preceeds(iContainer->_fixedCaches[i].filePosition))
                    {
                        //end search now because fixed cache list is sorted.
                        break;
                    }
                    else if (Contains(iContainer->_fixedCaches[i].filePosition))
                    {
                        //movable cache overlaps this fixed cache, so reduce its usable size
                        usableSize = (uint32)(iContainer->_fixedCaches[i].filePosition - filePosition);
                        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                                        (0, "OsclFileCache(0x%x)::SetPosition Movable Cache Overlap, adjusting size cap %d size %d"
                                         , this, (int32)capacity, usableSize));
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

/**
 * PrepRead
 *
 * Prepare to read from this cache.
 *
 * @param
 *
 * @return 0 if successful and a non-zero value otherwise
 */
int32 OsclFileCacheBuffer::PrepRead()
{
    //Prep for a read operation.  If there is no readable data at current
    //position, this will re-fill from end of usable data to end of cache.
    if (endPos <= currentPos
            && endPos < usableSize)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::PrepRead refilling cache", this));

        return FillFromFile(endPos, usableSize);
    }
    return 0;
}

/**
 * PrepWrite
 *
 * Prepare to write into this cache
 *
 * @param
 *
 * @return 0 if successful and a non-zero value otherwise
 */
int32 OsclFileCacheBuffer::PrepWrite()
{
    //Prep for a write operation.  Check for a gap from end of cache data to
    //current write position.  If there is any gap, then fill by reading from file.
    //This ensures that we never have undefined data in the cache.
    if (endPos < currentPos)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::PrepWrite filling gap in cache", this));
        return FillFromFile(endPos, currentPos);
    }
    return 0;
}

/**
 * FillFromFile
 *
 * Fills all or part of a cache from the file.
 *
 * @param aStart, aEnd: range to fill, units 0-based
 *    offset into cache.
 *
 * @return 0 if successful and a non-zero value otherwise
 */
int32 OsclFileCacheBuffer::FillFromFile(uint32 aStart, uint32 aEnd)
{
    OSCL_ASSERT(aStart < aEnd);

    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::FillFromFile fp %d start %d end %d", this, (int32)filePosition, aStart, aEnd));

    //we are going to refill this cache from aStart to aEnd position.
    //first make sure we do not lose any writes in the cache.
    if (IsUpdated()
            && updateStart <= aStart
            && aStart < updateEnd)
    {
        //the fill area overlaps some updates, so flush them
        int32 result = WriteUpdatesToFile();
        if (result != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::FillFromFile ERROR WriteUpdatesToFile failed", this));
            return result;//error!
        }
    }

    TOsclFileOffset newpos = filePosition + aStart;

    if (iContainer->_nativePosition != newpos)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::FillFromFile CallingNativeSeek : %d", this, (int32)newpos));
        int32 result = iContainer->iContainer.CallNativeSeek(newpos, Oscl_File::SEEKSET);
        if (result != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::FillFromFile ERROR CallNativeSeek failed", this));
            return result;//error!
        }

        //keep track of the native file position
        iContainer->_nativePosition = newpos;
    }

    //Fill from aStart to aEnd  We may hit EOF.
    uint32 size = aEnd - aStart;
    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::FillFromFile CallingNativeRead : %d", this, (int32)size));
    int32 nread = iContainer->iContainer.CallNativeRead((void*)(pBuffer + aStart), 1, size);

    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                    (0, "OsclFileCache(0x%x)::FillFromFile got %d bytes", this, nread));

    //update end pos
    endPos = aStart + nread;

    //update native position
    iContainer->_nativePosition += nread;

    //When reading to EOF in append mode, a subsequent native write will fail.
    //Seeking to the EOF point after the read fixes it.  Odd.
    if (iContainer->_mode & Oscl_File::MODE_APPEND
            && iContainer->_nativePosition >= iContainer->_fileSize)
    {
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::FillFromFile CallingNativeSeek : %d", this, (int32)iContainer->_nativePosition));
        int32 retval = iContainer->iContainer.CallNativeSeek(iContainer->_nativePosition, Oscl_File::SEEKSET);
        if (retval != 0)
        {
            PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                            (0, "OsclFileCache(0x%x)::FillFromFile ERROR CallNativeSeek failed", this));
            return retval;//error!
        }
    }

    //It's possible read may fail, even when filesize suggests there is data.
    //This has been observed in cases where a binary file is opened in text mode.
    //It could also occur due to other errors.  This results in seek position being
    //past the end of readable data.  This is an invalid state for the cache, so
    //flag an error.  It doesn't make sense to move the current position backward,
    //because the Seek call has already succeeded.
    if (endPos < currentPos)
    {
        return (-1);
    }

    return 0;
}


/**
 * WriteUpdatesToFile
 *
 * Writes any updated data in the cache to disk, but does not
 * otherwise alter cache position or contents.  Existing cache
 * data is still available for read.
 *
 * Has a side effect of adjusting the native file position.
 *
 * @param void
 *
 * @return 0 if successful and a non-zero value otherwise
 */
int32 OsclFileCacheBuffer::WriteUpdatesToFile()
{
    if (updateEnd > updateStart)
    {
        uint32 bytesToWrite = (updateEnd - updateStart);

        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::WriteUpdatesToFile nbytes %d filepos %d start %d end %d "
                         , this, bytesToWrite, filePosition, updateStart, updateEnd));

        //Seek to the correct write location in the file if needed

        TOsclFileOffset pos = filePosition + updateStart;

        if (iContainer->_nativePosition != pos)
        {
            if (iContainer->_mode & Oscl_File::MODE_APPEND)
            {
                //In Append mode, writes automatically happen at the end of file so there is no
                //need to seek.
                ;
            }
            else
            {
                //seek to the write location
                PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                                (0, "OsclFileCache(0x%x)::WriteUpdatesToFile CallingNativeSeek : %d", this, (int32) pos));
                int32 retval = iContainer->iContainer.CallNativeSeek(pos, Oscl_File::SEEKSET);
                if (retval != 0)
                {
                    PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                                    (0, "OsclFileCache(0x%x)::WriteUpdatesToFile ERROR CallNativeSeek failed", this));
                    return retval;//error!
                }
            }

            iContainer->_nativePosition = pos;
        }

        //write the updated data range.
        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::WriteUpdatesToFile CallingNativeWrite : %d", this, (int32) bytesToWrite));
        int32 retval = iContainer->iContainer.CallNativeWrite(pBuffer + updateStart, 1, bytesToWrite);

        //keep track of the native file position.
        iContainer->_nativePosition += retval;

        //clear the updated data range.
        updateStart = updateEnd = 0;

        if ((uint32)retval == bytesToWrite)
            return 0;//success!

        PVLOGGER_LOGMSG(PVLOGMSG_INST_LLDBG, iContainer->iLogger, PVLOGMSG_DEBUG,
                        (0, "OsclFileCache(0x%x)::WriteUpdatesToFile ERROR CallNativeWrite only wrote %d of %d", this, retval, bytesToWrite));

        /*
        //At this point, the cache is corrupt, since we lost data.
        //Recover by checking actual native file values, emptying the cache,
        //and locating it as close as possible to the desired position.
        iContainer->_fileSize = iContainer->iContainer.CallNativeSize();
        iContainer->_nativePosition = iContainer->iContainer.CallNativeTell();
        TOsclFileOffset newpos = iContainer->Tell();
        if (newpos > iContainer->_fileSize)
            newpos = iContainer->_fileSize;
        SetPosition(newpos);
        */

        return (-1); //error
    }
    return 0;//success-- nothing to do
}


