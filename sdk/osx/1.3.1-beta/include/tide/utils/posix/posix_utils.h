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

#ifndef _KR_POSIX_UTILS_H_
#define _KR_POSIX_UTILS_H_
#include <string>
namespace UTILS_NS
{
    TIDE_API std::wstring UTF8ToWide(const std::string& in);
    TIDE_API std::wstring UTF8ToWide(const char* in);
    TIDE_API std::string WideToUTF8(const std::wstring& in);
    TIDE_API std::string WideToUTF8(const wchar_t* in);
    TIDE_API std::string UTF8ToSystem(const std::string& in);
    TIDE_API std::string UTF8ToSystem(const char* in);
}
#endif
