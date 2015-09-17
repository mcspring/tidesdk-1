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

#ifndef _BYTES_H_
#define _BYTES_H_

#include "../tide.h"
#include <vector>
#include <string>
#include <map>
#include <cstring>

namespace tide
{
    /**
     * An object that represents an arbitrary amount of binary data§
     */
    class TIDE_API Bytes : public StaticBoundObject
    {
    public:
        // Create empty bytes object with no size
        Bytes();

        // Create new empty bytes object of specified size
        Bytes(size_t size);

        // Reference an existing bytes object. An offset and length
        // may be provided to "slice" only a part of the data.
        Bytes(BytesRef source, size_t offset = 0, size_t length = -1);

        // Create bytes object from a string.
        Bytes(std::string& str);
        Bytes(const char* str, size_t length = -1);

        virtual ~Bytes();

        size_t ExtraMemoryCost();

        // A pointer to the internal byte buffer
        char* Pointer() { return buffer; }

        // Returns length of bytes this object has in capacity
        size_t Length() { return size; }

        // Write data at the given offset. If no offset provided,
        // start writing at start of Bytes object.
        size_t Write(const char* data, size_t length, size_t offset = 0);
        size_t Write(BytesRef source, size_t offset = 0);

        // Return a string representation
        std::string AsString();

        static BytesRef Concat(std::vector<BytesRef>& bytes);

    private:
        // Binding methods
        void SetupBinding();
        void _Write(const ValueList& args, KValueRef result);
        void _ToString(const ValueList& args, KValueRef result);
        void _IndexOf(const ValueList& args, KValueRef result);
        void _LastIndexOf(const ValueList& args, KValueRef result);
        void _CharAt(const ValueList& args, KValueRef result);
        void _ByteAt(const ValueList& args, KValueRef result);
        void _Split(const ValueList& args, KValueRef result);
        void _Substr(const ValueList& args, KValueRef result);
        void _Substring(const ValueList& args, KValueRef result);
        void _ToLowerCase(const ValueList& args, KValueRef result);
        void _ToUpperCase(const ValueList& args, KValueRef result);
        void _Replace(const ValueList& args, KValueRef result);
        void _Concat(const ValueList& args, KValueRef result);
        void _Slice(const ValueList& args, KValueRef result);

        char* buffer;
        size_t size;
        BytesRef source;
    };
}

#endif
