/**
* This file has been modified from its orginal sources.
*
* Copyright (c) 2012 Software in the Public Interest Inc (SPI)
* Copyright (c) 2012 David Pratt
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
***
* Copyright (c) 2008-2012 Appcelerator Inc.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#ifndef _KR_WIN32_UTILS_H_
#define _KR_WIN32_UTILS_H_
#include <string>
namespace UTILS_NS
{
    namespace Win32Utils
    {
        /*
         * Easily get the result of a FormatMessage
         * @param errorCode the error code to get the message for
         * @returns a normal, all-American std::string for once
         */
        TIDE_API std::string QuickFormatMessage(
            DWORD errorCode,
            DWORD flags=FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_IGNORE_INSERTS);
    };

    namespace FileUtils
    {
        TIDE_API void CopyRecursive(const std::string &dir,
            const std::string &dest, const std::string& exclude = "");

        /* Some wchar versions of popular FileUtils functions */
        TIDE_API bool IsFile(const std::wstring& path);
        TIDE_API std::string ReadFile(const std::wstring& path);

        /**
         * Delete the file at the given path
         */
        TIDE_API bool DeleteFile(const std::string &path);
    }

    TIDE_API std::wstring UTF8ToWide(const std::string& in);
    TIDE_API std::wstring UTF8ToWide(const char* in);
    TIDE_API std::string WideToUTF8(const std::wstring& in);
    TIDE_API std::string WideToUTF8(const wchar_t* in);
    TIDE_API std::string UTF8ToSystem(const std::string& in);
    TIDE_API std::string UTF8ToSystem(const char* in);
    TIDE_API std::string WideToSystem(const std::wstring& in);
    TIDE_API std::string WideToSystem(const wchar_t* in);

    TIDE_API std::wstring MultiByteToWide(const std::string& in, UINT codePage);
    TIDE_API std::wstring MultiByteToWide(const char* in, size_t length, UINT codePage);
    TIDE_API std::string WideToMultiByte(const std::wstring& in, UINT codePage);
    TIDE_API std::string WideToMultiByte(const wchar_t* in, size_t length, UINT codePage);
    TIDE_API std::string MultiByteToMultiByte(const std::string& in, UINT codePageIn,
        UINT codePageOut);
}
#endif
