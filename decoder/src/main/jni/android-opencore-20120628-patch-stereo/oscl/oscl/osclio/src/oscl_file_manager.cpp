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
/*! \file oscl_file_man.cpp
    \brief This file contains file io APIs for file management functions
*/

#include "oscl_file_manager.h"
#include "oscl_file_types.h"
#include "oscl_utf8conv.h"
#include "oscl_stdstring.h"
#include "oscl_int64_utils.h"
#include "oscl_file_io.h"
#include "oscl_mem_basic_functions.h"

///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileSize(const oscl_wchar* aFileName, uint64& aFileSize)
{
    char convpathname[OSCL_IO_FILENAME_MAXLEN];
    if (0 == oscl_UnicodeToUTF8(aFileName, oscl_strlen(aFileName), convpathname, OSCL_IO_FILENAME_MAXLEN) &&
            oscl_strlen(aFileName) != 0)
    {
        return false;
    }
    return OsclGetFileSize(convpathname, aFileSize);

}
///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileSize(const char* aFileName, uint64& aFileSize)
{
    struct stat statbuf;
    aFileSize = 0;
    if (aFileName && *aFileName)
    {
        if (stat(aFileName, &statbuf) == 0)
        {
            Oscl_Int64_Utils::set_uint64(aFileSize, 0, statbuf.st_size);
            return true;
        }
    }
    return false;

}
///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileCreationTime(const oscl_wchar* aFileName, uint64& aFileCreationTime)
{

    char convpathname[OSCL_IO_FILENAME_MAXLEN];
    if (0 == oscl_UnicodeToUTF8(aFileName, oscl_strlen(aFileName), convpathname, OSCL_IO_FILENAME_MAXLEN) &&
            oscl_strlen(aFileName) != 0)
    {
        return false;
    }
    return OsclGetFileCreationTime(convpathname, aFileCreationTime);
}
///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileCreationTime(const char* aFileName, uint64& aFileCreationTime)
{

    struct stat statbuf;
    aFileCreationTime = 0;
    if (aFileName && *aFileName)
    {
        if (stat(aFileName, &statbuf) == 0)
        {
            Oscl_Int64_Utils::set_uint64(aFileCreationTime, 0, (statbuf.st_ctime));
            aFileCreationTime = (aFileCreationTime) * (1000000);
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileLastAccessTime(const oscl_wchar* aFileName, uint64& aFileLastAccessTime)
{

    char convpathname[OSCL_IO_FILENAME_MAXLEN];
    if (0 == oscl_UnicodeToUTF8(aFileName, oscl_strlen(aFileName), convpathname, OSCL_IO_FILENAME_MAXLEN) &&
            oscl_strlen(aFileName) != 0)
    {
        return false;
    }
    return OsclGetFileLastAccessTime(convpathname, aFileLastAccessTime);
}
///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileLastAccessTime(const char* aFileName, uint64& aFileLastAccessTime)
{
    struct stat statbuf;
    aFileLastAccessTime = 0;
    if (aFileName && *aFileName)
    {
        if (stat(aFileName, &statbuf) == 0)
        {
            Oscl_Int64_Utils::set_uint64(aFileLastAccessTime, 0, (statbuf.st_atime));
            aFileLastAccessTime = (aFileLastAccessTime) * (1000000);
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileLastWriteTime(const oscl_wchar* aFileName, uint64& aFileLastWriteTime)
{

    char convpathname[OSCL_IO_FILENAME_MAXLEN];
    if (0 == oscl_UnicodeToUTF8(aFileName, oscl_strlen(aFileName), convpathname, OSCL_IO_FILENAME_MAXLEN) &&
            oscl_strlen(aFileName) != 0)
    {
        return false;
    }
    return OsclGetFileLastWriteTime(convpathname, aFileLastWriteTime);
}

///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileLastWriteTime(const char* aFileName, uint64& aFileLastWriteTime)
{

    struct stat statbuf;
    aFileLastWriteTime = 0;
    if (aFileName && *aFileName)
    {
        if (stat(aFileName, &statbuf) == 0)
        {
            Oscl_Int64_Utils::set_uint64(aFileLastWriteTime, 0, (statbuf.st_mtime));
            aFileLastWriteTime = (aFileLastWriteTime) * (1000000);

            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileAttributes(const oscl_wchar* aFileName, uint32& aFileAttributes)
{

    char convpathname[OSCL_IO_FILENAME_MAXLEN];
    if (0 == oscl_UnicodeToUTF8(aFileName, oscl_strlen(aFileName), convpathname, OSCL_IO_FILENAME_MAXLEN) &&
            oscl_strlen(aFileName) != 0)
    {
        return false;
    }
    return OsclGetFileAttributes(convpathname, aFileAttributes);

}

///////////////////////////////////////////////////////////////////////////////
OSCL_EXPORT_REF bool OsclFileManager::OsclGetFileAttributes(const char* aFileName, uint32& aFileAttributes)
{

    struct stat statbuf;
    aFileAttributes = 0;
    char* aExactFileName = NULL;

    if (aFileName && *aFileName)
    {
        if (stat(aFileName, &statbuf) == 0)
        {
            if (true == S_ISDIR(statbuf.st_mode))
            {
                aFileAttributes |= OSCL_FILE_ATTRIBUTE_DIRECTORY;
            }
            if (!(statbuf.st_mode & S_IWUSR) && !(statbuf.st_mode & S_IWGRP) && !(statbuf.st_mode & S_IWOTH))
            {
                aFileAttributes |= OSCL_FILE_ATTRIBUTE_READONLY;
            }
            /*This function will provide File Name from Path */
            OsclExtractFilenameFromFullpath(aFileName, aExactFileName);
            if (aExactFileName && aExactFileName[0] == '.')
            {
                aFileAttributes |= OSCL_FILE_ATTRIBUTE_HIDDEN;
            }
            return true;
        }
    }
    return false;

}

/////////////////////////////////////////////////////////////////////////////////////

OSCL_EXPORT_REF void OsclFileManager::OsclExtractFilenameFromFullpath(const char* aPath, char* &aFileName)
{
    if (aPath && *aPath)
    {
        const char *pStrtmp = OSCL_FILE_CHAR_PATH_DELIMITER;
        char *pTmp = oscl_strstr((char*)aPath, pStrtmp);
        while (pTmp)
        {
            aPath = pTmp + oscl_strlen(pStrtmp);
            pTmp = oscl_strstr((char*)aPath, pStrtmp);
        }
        aFileName = (char*)aPath;
    }
    else
    {
        aFileName = NULL;
    }
}

OSCL_EXPORT_REF void OsclFileManager::OsclExtractFilenameFromFullpath(const oscl_wchar* aPath, oscl_wchar* &aFileName)
{
    if (aPath && *aPath)
    {
        const oscl_wchar *pStrtmp = OSCL_FILE_WCHAR_PATH_DELIMITER;
        oscl_wchar *pTmp = oscl_strstr((oscl_wchar*)aPath, pStrtmp);
        while (pTmp)
        {
            aPath = pTmp + oscl_strlen(pStrtmp);
            pTmp = oscl_strstr((oscl_wchar*)aPath, pStrtmp);
        }
        aFileName = (oscl_wchar*)aPath;
    }
    else
    {
        aFileName = NULL;
    }
}



