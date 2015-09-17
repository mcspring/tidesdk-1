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

#ifndef _EVENT_H_
#define _EVENT_H_

namespace tide
{
    class TIDE_API Event : public KAccessorObject
    {
    public:
        Event(AutoPtr<KEventObject> target, const std::string& eventName);
        void _GetTarget(const ValueList&, KValueRef result);
        void _GetType(const ValueList&, KValueRef result);
        void _GetTimestamp(const ValueList&, KValueRef result);
        void _StopPropagation(const ValueList&, KValueRef result);
        void _PreventDefault(const ValueList&, KValueRef result);
        static void SetEventConstants(KObject* target);

        AutoPtr<KEventObject> target;
        std::string eventName;
        Poco::Timestamp timestamp;
        bool stopped;
        bool preventedDefault;
        static std::string ALL;
        static std::string FOCUSED;
        static std::string UNFOCUSED;
        static std::string OPEN;
        static std::string OPENED;
        static std::string CLOSE;
        static std::string CLOSED;
        static std::string HIDDEN;
        static std::string SHOWN;
        static std::string REOPEN;
        static std::string FULLSCREENED;
        static std::string UNFULLSCREENED;
        static std::string MAXIMIZED;
        static std::string MINIMIZED;
        static std::string RESIZED;
        static std::string MOVED;
        static std::string PAGE_INITIALIZED;
        static std::string PAGE_LOADED;
        static std::string CREATED;
        static std::string ACTIVATE;
        static std::string CLICKED;
        static std::string DOUBLE_CLICKED;
        static std::string EXIT;
        static std::string APP_EXIT;
        static std::string READ;
        static std::string HTTP_DONE;
        static std::string HTTP_STATE_CHANGED;
        static std::string HTTP_TIMEOUT;
        static std::string HTTP_REDIRECT;
        static std::string HTTP_ABORT;
        static std::string HTTP_DATA_SENT;
        static std::string HTTP_DATA_RECEIVED;
        static std::string OPEN_REQUEST;
    };
}

#endif
