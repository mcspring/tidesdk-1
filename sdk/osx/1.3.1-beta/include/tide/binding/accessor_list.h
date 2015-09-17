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

#ifndef _ACCESSOR_LIST_H_
#define _ACCESSOR_LIST_H_

namespace tide
{
    /**
     * The KAccessorList allows you to expose getters and setters as property access.
     * @see KAccessorObject
     */
    class TIDE_API KAccessorList : public StaticBoundList, public KAccessor
    {
    public:
        KAccessorList(const char* type = "KAccessorList");
        virtual void Set(const char* name, KValueRef value);
        virtual KValueRef Get(const char* name);
        virtual bool HasProperty(const char* name);

    private:
        DISALLOW_EVIL_CONSTRUCTORS(KAccessorList);
    };
}

#endif
