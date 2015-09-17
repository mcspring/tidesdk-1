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

#ifndef _JS_METHOD_H_
#define _JS_METHOD_H_

#include "javascript_module.h"

#include <vector>
#include <string>
#include <map>

namespace tide
{
    class TIDE_API KKJSMethod : public KMethod
    {
        public:
        KKJSMethod(JSContextRef, JSObjectRef, JSObjectRef);
        ~KKJSMethod();

        virtual void Set(const char *name, KValueRef value);
        virtual KValueRef Get(const char *name);
        KValueRef Call(JSObjectRef thisObject, const ValueList& args);
        virtual KValueRef Call(const ValueList& args);
        virtual KValueRef Call(KObjectRef thisObject, const ValueList& args);
        virtual SharedStringList GetPropertyNames();
        virtual bool HasProperty(const char* name);
        virtual bool Equals(KObjectRef);

        virtual bool SameContextGroup(JSContextRef c);
        JSObjectRef GetJSObject();

        protected:
        JSGlobalContextRef context;
        JSObjectRef jsobject;
        JSObjectRef thisObject;
        AutoPtr<KKJSObject> kobject;

        private:
        DISALLOW_EVIL_CONSTRUCTORS(KKJSMethod);
    };
}

#endif
