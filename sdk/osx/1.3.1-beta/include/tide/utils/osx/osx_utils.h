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

#ifndef _KR_OSX_UTILS_H_
#define _KR_OSX_UTILS_H_

#include <string>
#include <CoreFoundation/CoreFoundation.h>

// Most of the code was adapted from code in Chromium's src/base/...
namespace UTILS_NS
{
    TIDE_API std::string CFStringToUTF8(CFStringRef cfstring);
    TIDE_API CFStringRef UTF8ToCFString(const std::string& input);
    TIDE_API std::string CFErrorToString(CFErrorRef cferror);

    // CFRef<> is patterned after scoped_ptr<>, but maintains ownership
    // of a CoreFoundation object: any object that can be represented as a
    // CFTypeRef.  Style deviations here are solely for compatibility with
    // scoped_ptr<>'s interface, with which everyone is already familiar.
    //
    // When CFRef<> takes ownership of an object (in the constructor or
    // in reset()), it takes over the caller's existing ownership claim.  The 
    // caller must own the object it gives to CFRef<>, and relinquishes
    // an ownership claim to that object.  CFRef<> does not call
    // CFRetain().
    template<typename CFT>
    class CFRef {
    
    public:
        typedef CFT element_type;
        explicit CFRef(CFT object = NULL) :
            object_(object) { }

        ~CFRef()
        {
            if (object_)
                CFRelease(object_);
        }

        void reset(CFT object = NULL)
        {
            if (object_)
                CFRelease(object_);
            object_ = object;
        }

        bool operator==(CFT that) const
        {
            return object_ == that;
        }
    
        bool operator!=(CFT that) const
        {
            return object_ != that;
        }

        operator CFT() const
        {
            return object_;
        }

        CFT get() const
        {
            return object_;
        }

        void swap(CFRef& that)
        {
            CFT temp = that.object_;
            that.object_ = object_;
            object_ = temp;
        }

        // CFRef<>::release() is like scoped_ptr<>::release.  It is NOT
        // a wrapper for CFRelease().  To force a CFRef<> object to call
        // CFRelease(), use CFRef<>::reset().
        CFT release()
        {
            CFT temp = object_;
            object_ = NULL;
            return temp;
        }

    private:
        CFT object_;
    };
}

#endif
