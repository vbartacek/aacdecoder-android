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
/*! \file oscl_file_native.cpp
    \brief This file contains file io APIs
*/

#include "oscl_file_native.h"
#include "oscl_stdstring.h"
#include "oscl_utf8conv.h"
#include "oscl_int64_utils.h"

#include "oscl_mem.h"
#include "oscl_file_types.h"
#include "oscl_file_handle.h"

#ifdef ANDROID
struct AssethandleElementStruct
{
    FILE* assethandle;
    pthread_mutex_t* mutex;
    uint32 count;
};

static Oscl_Vector<AssethandleElementStruct, OsclMemAllocator> iAssethandleVector;
static pthread_mutex_t iConstruct_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

OsclNativeFile::OsclNativeFile()
#ifdef ANDROID
        :
        iAssethandle_mutex(NULL)
#endif
{
    iOpenFileHandle = false;
    iMode = 0;

    iFile = 0;
    iIsAsset = false;
    iIsAssetReadOnly = false;
    iAssetOffset = 0;
    iAssetSize = 0;
    iAssetLogicalFilePos = 0;

#ifdef ANDROID
    iFileDescriptor = 0;
#endif

}

OsclNativeFile::~OsclNativeFile()
{
}

int32  OsclNativeFile::Open(const OsclFileHandle& aHandle, uint32 mode
                            , const OsclNativeFileParams& params
                            , Oscl_FileServer& fileserv)
{
    //open with an external file handle

    OSCL_UNUSED_ARG(fileserv);

    iMode = mode;
    iOpenFileHandle = true;

    {
        OSCL_UNUSED_ARG(params);
        //Just save the open file handle
        iFile = aHandle.Handle();

#ifdef ANDROID
        iFileDescriptor = fileno(aHandle.Handle());
#endif
    }

    return 0;
}

int32 OsclNativeFile::Open(const oscl_wchar* filename, uint32 mode
                           , const OsclNativeFileParams& params
                           , Oscl_FileServer& fileserv)
{
    iMode = mode;
    iOpenFileHandle = false;

#ifdef ANDROID
    //This feature requires standard C file handles and is currently only
    //available on Android.
    //Do not combine this block of code with the general HAS_ANSI case below
    //since we like to debug this on Windows.
    //Test for "assethandle://" URI's first before the standard file handling.
    if (filename != NULL)
    {
        //Convert the unicode URI to ASCII.
        char uri[100];
        oscl_UnicodeToUTF8(filename, oscl_strlen(filename), uri, sizeof(uri));
        if (oscl_strncmp(uri, "assethandle://", 14) == 0)
        {
            //Call the narrow string Open method.
            return Open(uri, mode, params, fileserv);
        }
    }
#endif

    {
        OSCL_UNUSED_ARG(fileserv);
        OSCL_UNUSED_ARG(params);

        if (!filename || *filename == '\0') return -1; // Null string not supported in fopen, error out

        char openmode[4];
        uint32 index = 0;
#ifdef ANDROID
        int largeFileOpenMode = FindLargeFileOpenMode(mode);
#endif
        if (mode & Oscl_File::MODE_READWRITE)
        {
            if (mode & Oscl_File::MODE_APPEND)
            {
                openmode[index++] = 'a';
                openmode[index++] = '+';
            }
            else
            {
                openmode[index++] = 'w';
                openmode[index++] = '+';
            }
        }
        else if (mode & Oscl_File::MODE_APPEND)
        {
            openmode[index++] = 'a';
            openmode[index++] = '+';
        }
        else if (mode & Oscl_File::MODE_READ)
        {
            openmode[index++] = 'r';
        }
        else if (mode & Oscl_File::MODE_READ_PLUS)
        {
            openmode[index++] = 'r';
            openmode[index++] = '+';
        }



        if (mode & Oscl_File::MODE_TEXT)
        {
            openmode[index++] = 't';
        }
        else
        {
            openmode[index++] = 'b';
        }

        openmode[index++] = '\0';

#ifdef _UNICODE
        oscl_wchar convopenmode[4];
        if (0 == oscl_UTF8ToUnicode(openmode, oscl_strlen(openmode), convopenmode, 4))
        {
            return -1;
        }

        if ((iFile = _wfopen(filename, convopenmode)) == NULL)
        {
            return -1;
        }
#else
        //Convert to UTF8
        char convfilename[OSCL_IO_FILENAME_MAXLEN];
        if (0 == oscl_UnicodeToUTF8(filename, oscl_strlen(filename), convfilename, OSCL_IO_FILENAME_MAXLEN))
        {
            return -1;
        }

#ifdef ANDROID
        iFileDescriptor = open(convfilename, largeFileOpenMode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        //Populate iFile
        iFile = fdopen(iFileDescriptor, openmode);
        if (iFileDescriptor == -1)
        {
            return -1;
        }
        else
            return 0;
#endif
        if ((iFile = fopen(convfilename, openmode)) == NULL)
        {
            return -1;
        }

#endif
        return 0;
    }

}

int32 OsclNativeFile::Open(const char *filename, uint32 mode
                           , const OsclNativeFileParams& params
                           , Oscl_FileServer& fileserv)
{
    iMode = mode;
    iOpenFileHandle = false;

#ifdef ANDROID
    //This feature requires standard C file handles and is currently only
    //available on Android.
    //Do not combine this block of code with the general HAS_ANSI case below
    //since we like to debug this on Windows.
    //Test for "assethandle://" URI's first before the standard file handling.
    //Parse the URI for an asset file handle, offset, and size.
    const char* format = "assethandle://%ld:%ld:%ld";
    if (sizeof(TOsclFileOffset) > sizeof(long))
    {
        format = "assethandle://%ld:%lld:%lld";
    }
    //If the filename begins with "assethandle://", try to parse it.
    if ((filename != NULL) && (strncmp(filename, format, 14) == 0))
    {
        if (sscanf(filename, format, &iFile, &iAssetOffset, &iAssetSize) == 3)
        {
            if (iFile == NULL) return -1; //Bad handle.
            iFileDescriptor = fileno(iFile);
            //For this case, the file must already be open.
            iIsAsset = true;
            iIsAssetReadOnly = true;

            pthread_mutex_lock(&iConstruct_mutex);

            bool asset_found = false;
            if (!iAssethandleVector.empty())
            {
                // Vector is not empty.  Search the list for the assethandle
                Oscl_Vector<AssethandleElementStruct, OsclMemAllocator>::iterator it;
                for (it = iAssethandleVector.begin(); it != iAssethandleVector.end(); it++)
                {
                    if (it->assethandle == iFile)
                    {
                        asset_found = true;
                        // Assethandle found.  Increment the count
                        it->count++;
                        // Use the mutex associated with it.
                        iAssethandle_mutex = it->mutex;
                    }
                }
            }

            // Element not found.  Add it.
            if (asset_found == false)
            {
                // Didnt find the asset... create a new vector
                AssethandleElementStruct aNewAssetHandle;
                aNewAssetHandle.assethandle = iFile;
                aNewAssetHandle.mutex = NULL;
                aNewAssetHandle.mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
                if (aNewAssetHandle.mutex == NULL)
                {
                    pthread_mutex_unlock(&iConstruct_mutex);
                    // Unable to allocate memory for mutex... return failure.
                    return -1;
                }
                // Attempt to init the mutex
                if (0 != pthread_mutex_init(aNewAssetHandle.mutex, NULL))
                {
                    free(aNewAssetHandle.mutex);
                    pthread_mutex_unlock(&iConstruct_mutex);
                    // Failed to initalize the mutex
                    return -1;
                }
                // Init to 1
                aNewAssetHandle.count = 1;
                // Use the mutex in this object
                iAssethandle_mutex = aNewAssetHandle.mutex;
                // Add new element to the vector
                iAssethandleVector.push_back(aNewAssetHandle);
            }
            pthread_mutex_unlock(&iConstruct_mutex);

            //Seek to logical 0 to apply the offset.
            if (0 != Seek(0, Oscl_File::SEEKSET))
            {
                return -1; //Seek failed.
            }
            return 0;
        }
        else
        {
            //Parsing error, could not open.
            return -1;
        }
    }
#endif

    {
        OSCL_UNUSED_ARG(fileserv);
        OSCL_UNUSED_ARG(params);

        if (!filename || *filename == '\0') return -1; // Null string not supported in fopen, error out

        char openmode[4];
        uint32 index = 0;
#ifdef ANDROID
        int largeFileOpenMode = FindLargeFileOpenMode(mode);
#endif
        if (mode & Oscl_File::MODE_READWRITE)
        {
            if (mode & Oscl_File::MODE_APPEND)
            {
                openmode[index++] = 'a';
                openmode[index++] = '+';
            }
            else
            {
                openmode[index++] = 'w';
                openmode[index++] = '+';

            }
        }
        else if (mode & Oscl_File::MODE_APPEND)
        {
            openmode[index++] = 'a';
            openmode[index++] = '+';
        }
        else if (mode & Oscl_File::MODE_READ)
        {
            openmode[index++] = 'r';
        }
        else if (mode & Oscl_File::MODE_READ_PLUS)
        {
            openmode[index++] = 'r';
            openmode[index++] = '+';
        }

        if (mode & Oscl_File::MODE_TEXT)
        {
            openmode[index++] = 't';
        }
        else
        {
            openmode[index++] = 'b';
        }

        openmode[index++] = '\0';

#ifdef ANDROID
        iFileDescriptor = open(filename, largeFileOpenMode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        //Populate iFile
        iFile = fdopen(iFileDescriptor, openmode);
        if (iFileDescriptor == -1)
        {
            return -1;
        }
        else
            return 0;
#endif
        if ((iFile = fopen(filename, openmode)) == NULL)
        {
            return -1;
        }
        return 0;

    }

}

TOsclFileOffset OsclNativeFile::Size()
{
    //this is the default for platforms with no
    //native size query.
    //Just do seek to end, tell, then seek back.
    TOsclFileOffset curPos = Tell();
    if (curPos >= 0
            && Seek(0, Oscl_File::SEEKEND) == 0)
    {
        TOsclFileOffset endPos = Tell();
        if (Seek(curPos, Oscl_File::SEEKSET) == 0)
        {
            return endPos;
        }
        else
        {
            return (-1);
        }
    }
    return (-1);
}

int32 OsclNativeFile::Close()
{
    int32 closeret = 0;

    //Do not close asset file's shared file handle - the owner must close it.
    if (iIsAsset)
    {
#ifdef ANDROID
        pthread_mutex_lock(&iConstruct_mutex);

        // Assethandle vector should not be empty.
        OSCL_ASSERT(!iAssethandleVector.empty());

        if (!iAssethandleVector.empty())
        {
            // Vector is not empty.  Search the list for the assethandle
            Oscl_Vector<AssethandleElementStruct, OsclMemAllocator>::iterator it;
            for (it = iAssethandleVector.begin(); it != iAssethandleVector.end(); it++)
            {
                if (it->assethandle == iFile)
                {
                    // Assethandle found.  Dec the count
                    it->count--;
                    if (it->count == 0)
                    {
                        // Count is zero.  Destroy the mutex.  No longer needed
                        pthread_mutex_destroy(it->mutex);
                        free(it->mutex);
                        iAssethandleVector.erase(it);
                    }
                    pthread_mutex_unlock(&iConstruct_mutex);
                    return 0;
                }
            }
        }
        // Assethandle was not found on the list!
        OSCL_ASSERT(0);
        pthread_mutex_unlock(&iConstruct_mutex);
        return -1;
#else
        return 0;
#endif
    }

    {
        if (iOpenFileHandle)
            closeret = Flush();
        else if (iFile != NULL)
        {
            closeret = fclose(iFile);
            iFile = NULL;
#ifdef ANDROID
            iFileDescriptor = 0;
#endif

        }
        else
        {
            return -1; //Linux Porting : Fix 1
        }
    }

    return closeret;
}

uint32 OsclNativeFile::Read(OsclAny *buffer, uint32 size, uint32 numelements)
{
    uint32 read_ret = 0;
    if (iIsAsset)
    {
#ifdef ANDROID
        pthread_mutex_lock(iAssethandle_mutex);

        lseek64(iFileDescriptor, (iAssetLogicalFilePos + iAssetOffset), SEEK_SET);
#else
        //Asset file are opened multiple times by the source nodes, so always seek before reading.
        Seek(iAssetLogicalFilePos, Oscl_File::SEEKSET);
#endif

        //If the file is an asset file, don't allow reading past the end.
        //Calculate the new logical file position.
        uint32 bytes = size * numelements;
        iAssetLogicalFilePos += bytes;

        //If we read past the end of the asset...
        if (iAssetLogicalFilePos >= iAssetSize)
        {
            //Calculate the number of bytes read past the end.
            uint32 over = OSCL_STATIC_CAST(uint32, (iAssetLogicalFilePos - iAssetSize));
            //Calculate the number of elements that can be read.
            if (!size)
            {
#ifdef ANDROID
                pthread_mutex_unlock(iAssethandle_mutex);
#endif
                return 0; //avoid divide-by-zero
            }
            if (bytes < over)
            {
#ifdef ANDROID
                pthread_mutex_unlock(iAssethandle_mutex);
#endif
                return 0; //avoid negative count
            }
            numelements = (bytes - over) / size;
        }
    }

    if (iFile)
    {
#ifdef ANDROID
        int32 bytesToBeRead = size * numelements;
        int32 result = read(iFileDescriptor, buffer, bytesToBeRead);
        if (result != -1)
        {
            read_ret = (uint32)(result / size);
        }
        else
        {
            read_ret = -1;
        }
#else // else OSCL_HAS_LARGE_FILE_SUPPORT and NOT ANDROID
        read_ret = fread(buffer, OSCL_STATIC_CAST(int32, size), OSCL_STATIC_CAST(int32, numelements), iFile);
#endif // endif ANDROID
    }

#ifdef ANDROID
    if (iIsAsset)
    {
        pthread_mutex_unlock(iAssethandle_mutex);
    }
#endif
    return read_ret;
}

bool OsclNativeFile::HasAsyncRead()
{
    return false;//not supported.
}

int32 OsclNativeFile::ReadAsync(OsclAny*buffer, uint32 size, uint32 numelements, OsclAOStatus& status)
{
    OSCL_UNUSED_ARG(buffer);
    OSCL_UNUSED_ARG(size);
    OSCL_UNUSED_ARG(numelements);
    OSCL_UNUSED_ARG(status);
    return -1;//not supported
}

void OsclNativeFile::ReadAsyncCancel()
{
}

uint32 OsclNativeFile::GetReadAsyncNumElements()
{
    return 0;//not supported
}



uint32 OsclNativeFile::Write(const OsclAny *buffer, uint32 size, uint32 numelements)
{
    //Abort the write operation if the file is a read-only asset.
    if (iIsAsset && iIsAssetReadOnly)
    {
        return 0;
    }

    if (iFile)
    {
#ifdef ANDROID
        int32 num_bytes_written = write(iFileDescriptor, buffer, (size * numelements));
        if (num_bytes_written != -1)
        {
            return (uint32)(num_bytes_written / size);
        }
        else
            return -1;
#endif
        return fwrite(buffer, OSCL_STATIC_CAST(int32, size), OSCL_STATIC_CAST(int32, numelements), iFile);
    }
    return 0;
}

int32 OsclNativeFile::Seek(TOsclFileOffset offset, Oscl_File::seek_type origin)
{
    int32 seek_ret = -1;
    //If the file represents an individual asset from a file,
    //normalize the offset.
    if (iIsAsset)
    {
#ifdef ANDROID
        pthread_mutex_lock(iAssethandle_mutex);
#endif
        switch (origin)
        {
            case Oscl_File::SEEKCUR:
                iAssetLogicalFilePos += offset;
                break;
            case Oscl_File::SEEKEND:
                iAssetLogicalFilePos = iAssetSize + offset;
                break;
            case Oscl_File::SEEKSET:
            default:
                iAssetLogicalFilePos = offset;
                break;
        }
        offset = iAssetLogicalFilePos + iAssetOffset;
        origin = Oscl_File::SEEKSET;
    }

    {
        if (iFile)
        {
            int32 seekmode = SEEK_CUR;

            if (origin == Oscl_File::SEEKCUR)
                seekmode = SEEK_CUR;
            else if (origin == Oscl_File::SEEKSET)
                seekmode = SEEK_SET;
            else if (origin == Oscl_File::SEEKEND)
                seekmode = SEEK_END;

#ifdef ANDROID
            TOsclFileOffset seekResult = lseek64(iFileDescriptor, offset, seekmode);

            if (iIsAsset)
            {
                pthread_mutex_unlock(iAssethandle_mutex);
            }

            if (seekResult == -1)
                seek_ret = -1;
            else
                seek_ret = 0;

            return seek_ret;
#endif
            seek_ret = fseeko(iFile, offset, seekmode);
        }
    }

    return seek_ret;
}

int32 OsclNativeFile::SetSize(uint32 size)
{
    // unix leaves file position unchanged
    int32 fd = fileno(iFile);
    if (-1 != fd)
    {
        return ftruncate(fd, size);
    }
    return -1;
}


TOsclFileOffset OsclNativeFile::Tell()
{
    if (iIsAsset) return iAssetLogicalFilePos;

    TOsclFileOffset result = -1;
    if (iFile)
    {
#ifdef ANDROID
        return lseek64(iFileDescriptor, 0, SEEK_CUR);
#endif
        result = ftello(iFile);
    }
    return result;
}



int32 OsclNativeFile::Flush()
{


    if (!iFile || fflush(iFile) == EOF)
        return EOF;
    // flush OS buffers to disk
    return fsync(fileno(iFile));

}



int32 OsclNativeFile::EndOfFile()
{
    if (iIsAsset)
    {
        if (Tell() >= iAssetSize) return 1;
        return 0;
    }

#ifdef ANDROID
    if (iFile)
    {
        return Tell() < Size() ? 0 : 1;
    }
#endif
    if (iFile)
    {
        return feof(iFile);
    }
    return 0;
}


int32 OsclNativeFile::GetError()
{
    if (iFile)
        return ferror(iFile);
    return 0;
}

#ifdef ANDROID
int32 OsclNativeFile::FindLargeFileOpenMode(uint32 mode)
{
    int32 largeFileOpenMode = 0;

    if (mode & Oscl_File::MODE_APPEND)
    {
        largeFileOpenMode = O_CREAT | O_APPEND;
    }
    else if (mode & Oscl_File::MODE_READ)
    {
        largeFileOpenMode = O_RDONLY;
    }
    else if (mode & Oscl_File::MODE_READ_PLUS)
    {
        largeFileOpenMode = O_RDWR;
    }
    else if (mode & Oscl_File::MODE_READWRITE)
    {
        largeFileOpenMode = (O_RDWR | O_CREAT);
        if (mode & Oscl_File::MODE_APPEND)
        {
            largeFileOpenMode |= O_APPEND;
        }
        else
        {
            largeFileOpenMode |= O_TRUNC;
        }
    }

    largeFileOpenMode |= O_LARGEFILE;
    return largeFileOpenMode;
}
#endif

