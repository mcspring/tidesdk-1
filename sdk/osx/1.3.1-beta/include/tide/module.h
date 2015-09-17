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

#ifndef _KR_PLUGIN_H_
#define _KR_PLUGIN_H_

#include "module_provider.h"

namespace tide
{
    class Host;

    /**
     * An interface that represents a Kroll Module.
     *
     * The easiest way to create a module is to use the convenience macros defined in module.h.
     * Example MyModule.h:
     * \code
     * #include <tide/tide.h>
     * class MyModule : public tide::Module
     * {
     *   TIDE_MODULE_CLASS(MyModule)
     * }
     * \endcode
     *
     * Example MyModule.cpp:
     * \code
     * #include "MyModule.h"
     * TIDE_MODULE(MyModule);
     *
     * void MyModule::Initialize() {
     *  // init code here..
     * }
     *
     * void MyModule::Stop() {
     *  // stop code here..
     * }
     * \endcode
     */
    class TIDE_API Module
    {
    public:
        Module(Host *host, const char* inpath, const char* inname, const char* inversion) :
            host(host),
            path(std::string(inpath)),
            name(std::string(inname)),
            version(std::string(inversion))
        {
        }

        virtual ~Module()
        {
        }

        /**
         * @return the path to this module's main directory
         */
        virtual std::string GetPath()
        {
            return this->path;
        }

        /*
         * @return the name of the module
         */
        virtual std::string GetName()
        {
            return this->name;
        }

        /*
         * @return the version of the module
         */
        virtual std::string GetVersion()
        {
            return this->version;
        }

        /**
         * Called directly after module loading, during the loading
         * process. Perform all initialization here that does not
         * depend on the existence of other modules.
         */
        virtual void Initialize() {};

        /**
         * Called once all modules have been loaded. Use this to
         * perform initialization that depends on the existence of
         * other modules.
         */
        virtual void Start() {};

        /**
         * Called by the host that wants to stop a module. This will happen
         * before any pending Unload events;
         */
        virtual void Stop() {};

        /**
         * Called before the Host unloads the module.
         * Perform all unload cleanup here.
         */
        virtual void Unload() {};

    protected:
        Host* host;
        std::string path;
        std::string name;
        std::string version;

    private:
        DISALLOW_EVIL_CONSTRUCTORS(Module);
    };
}

// MACROS that are used to make it much easier to define and implement a module
using namespace tide;
typedef void* ModuleMethod;

/**
 * \def TIDE_MODULE(klass)
 * \brief A convenience macro for the module's implementation file.
 * \description Defines the default constructor, destructor, library implementations for the module "klass"
 */
#define TIDE_MODULE(ClassName, Name, Version) \
ClassName::ClassName(tide::Host *host, const char* path, const char* name, const char* version) : \
    tide::Module(host, path, name, version) \
{ \
} \
  \
ClassName::~ClassName() \
{ \
} \
  \
extern "C" EXPORT ClassName* CreateModule(tide::Host *host, const char* path) \
{ \
    return new ClassName(host, path, Name, Version); \
}  \

/**
 * \def TIDE_MODULE_CLASS(klass)
 * \brief A convenience macro for the module's header file.
 * \description Defines the default constructor, destructor, and lifecycle methods for the module "klass"
 */
#define TIDE_MODULE_CLASS(ClassName) \
public: \
    ClassName(tide::Host *host, const char* path, const char* name, const char* version); \
    virtual ~ClassName(); \
    void Initialize(); \
    void Stop();

#endif
