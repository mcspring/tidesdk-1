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

#ifndef _EVENT_OBJECT_H_
#define _EVENT_OBJECT_H_

#include <list>
#include <Poco/Mutex.h>

namespace tide
{
    class EventListener;
    typedef std::list<EventListener*> EventListenerList;

    class TIDE_API KEventObject : public KAccessorObject
    {
    public:
        KEventObject(const char* name = "KEventObject");
        virtual ~KEventObject();

        AutoPtr<Event> CreateEvent(const std::string& eventName);

        virtual void AddEventListener(const char* event, KMethodRef listener);
        virtual void AddEventListener(std::string& event, KMethodRef listener);
        virtual void RemoveEventListener(std::string& event, KMethodRef listener);
        virtual void RemoveAllEventListeners();

        void FireEvent(const char* event);
        virtual void FireEvent(const char* event, const ValueList& args);
        virtual bool FireEvent(std::string& event, bool synchronous=true);
        virtual bool FireEvent(AutoPtr<Event>, bool synchronous=true);
        void FireErrorEvent(std::exception& e);

        void _AddEventListener(const ValueList&, KValueRef result);
        void _RemoveEventListener(const ValueList&, KValueRef result);
        void _RemoveAllEventListeners(const ValueList&, KValueRef result);

    private:
        void ReportDispatchError(std::string& reason);

        EventListenerList listeners;
        Poco::FastMutex listenersMutex;
    };

    class EventListener
    {
    public:
        EventListener(std::string& targetedEvent, KMethodRef callback);
        EventListener(const char* targetedEvent, KMethodRef callback);

        bool Handles(const char* event);
        bool Dispatch(KObjectRef thisObject, const ValueList& args, bool synchronous);
        KMethodRef Callback();

    private:
        std::string targetedEvent;
        KMethodRef callback;
    };
}

#endif
