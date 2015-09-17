#!/usr/bin/env python

# This file has been modified from its orginal sources.
#
# Copyright (c) 2012 Software in the Public Interest Inc (SPI)
# Copyright (c) 2012 David Pratt
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Copyright (c) 2008-2012 Appcelerator Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# TideSDK application packaging script

import env
import os
import platform
import re
import signal
import subprocess
import sys
import os.path as path
from optparse import OptionParser
from xml.etree.ElementTree import ElementTree

VERSION = '0.2'
ALLOWED_PLATFORMS = ['win32','osx','linux']

def get_platform():
    if 'Darwin' in platform.platform():
        return 'osx'
    elif 'Windows' in platform.platform():
        return 'win32'
    elif 'Linux' in platform.platform():
        return 'linux'

def run(executable_path):
    process = None
    platform = get_platform()

    def handler(signum, frame):
        print "signal caught: %d" % signum
        if not process == None:
            if platform != 'win32':
                print "kill app with pid %d" % process.pid
                os.system("kill -9 %d" % process.pid)

    if platform != 'win32':
        signal.signal(signal.SIGHUP, handler)
        signal.signal(signal.SIGQUIT, handler)
    signal.signal(signal.SIGINT, handler)
    signal.signal(signal.SIGABRT, handler)
    signal.signal(signal.SIGTERM, handler)

    try:
        process = subprocess.Popen([executable_path, '--debug'])
        os.waitpid(process.pid, 0)
    except OSError:
        handler(3, None)

def dequote(s):
    if s[0] == '"' or s[0] == "'":
        s = s[1:-1]
    if s[-1] == '"' or s[-1] == "'":
        s = s[0:-2]
    return s

if __name__ == '__main__':
    parser = OptionParser(usage="%prog [options] appdir", version="%prog " + VERSION)
    parser.add_option("-d", "--dest",dest="destination",default=".",help="destination folder for output", metavar="FILE")
    parser.add_option("-v", "--verbose",action="store_true",dest="verbose",default=False,help="turn on verbose logging")
    parser.add_option("-o", "--os",dest="platform",default=get_platform(),help="platform if different than %s" % get_platform())
    parser.add_option("-t", "--type",dest="type",default="network",help="package type: network or bundle")
    parser.add_option("-l", "--license",dest="license_file",default=None,help="location of application license",metavar="FILE")
    parser.add_option("-n", "--noinstall",action="store_true",dest="no_install",default=False,help="don't include installer dialog in packaged app")
    parser.add_option("-r","--run",action="store_true",dest="run",default=False,help="run the packaged app after building")
    parser.add_option("-p","--package",dest="package",default=False,help="build the installation package")
    parser.add_option("-i","--ignore",dest="ignore_patterns",default="",help="patterns to ignore when packaging, seperated by comma (default: .git,.svn,.gitignore,.cvsignore)")
    parser.add_option("-j", "--jsobfuscate",action="store_true",dest="js_obfuscate",default=False,help="obfuscate the javascript code within project")
    parser.add_option("-s", "--src",dest="source",help="source folder which contains dist files",metavar="FILE")
    parser.add_option("-a", "--assets",dest="assets_dir",default=None,help="location of platform assets",metavar="FILE")
    parser.add_option("--appstore", action="store_true", dest="appstore", default=False, help="Package for app store submission")

    (options, args) = parser.parse_args()
    if len(args) == 0:
        parser.print_help()
        print 
        print "To stage an application in ~/tmp/myproject in the current directory and then run it:"
        print "\t> tidebuilder.py -d . -r ~/tmp/myproject"
        print
        sys.exit(1)

    appdir = path.abspath(path.expanduser(dequote(args[0])))
    if len(appdir) <= 0:
        parser.print_help()
        sys.exit(1)
    if not path.exists(appdir):
        print "Couldn't find application directory at: %s" % appdir
        sys.exit(1)
    if not path.exists(options.destination):
        print('Invalid destination directory: %s' % options.destination)
        sys.exit(1)
    if not options.platform in ALLOWED_PLATFORMS:
        print "Error: unsupported/unknown platform: %s" % options.platform
        print "Must be one of: %s" % str(ALLOWED_PLATFORMS)
        sys.exit(1)

    if options.appstore:
        bundle = True
        no_install = True
    else:
        bundle = options.type == 'bundle'
        no_install = options.no_install

    # Eventually we should detect if we are a packager
    # and not use any installed components.
    script_dir = os.path.abspath(os.path.dirname(sys._getframe(0).f_code.co_filename))
    packager = os.path.exists(path.join(script_dir, '.packager'))

    environment = env.PackagingEnvironment(options.platform, packager, options.appstore)
    app = environment.create_app(appdir)
    app.stage(path.join(options.destination, app.name), bundle=bundle, no_install=no_install, js_obfuscate=options.js_obfuscate, ignore_patterns=options.ignore_patterns)

    # Always create the package on the packaging server.
    if options.package or packager:
        app.package(options.destination, bundle=bundle)

    if options.run:
        run(app.executable_path)
