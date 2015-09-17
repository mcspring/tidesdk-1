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

import effess
import os
import os.path as p
from app import App

class LinuxApp(App):
    def stage(self, stage_dir, bundle, no_install, js_obfuscate, ignore_patterns):
        App.stage(self, stage_dir, bundle=bundle, no_install=no_install, js_obfuscate=js_obfuscate, ignore_patterns=ignore_patterns)

        contents = self.get_contents_dir()
        self.env.log(u'Copying tiboot to %s' % contents)
        self.executable_path = p.join(self.contents, self.name)
        effess.copy(p.join(self.sdk_dir, 'tiboot'), self.executable_path)

    def package(self, package_dir, bundle=False):
        longname = self.name + "-" + self.version
        def tar_callback(f, tar_file):
            print f
            # tar paths in <= 2.5 must be non unicode
            f = f.encode('ascii', 'ignore')
            tarname = longname + "/" + f.replace(self.stage_dir + os.sep, "")
            tarname = tarname.encode('ascii', 'ignore')
            tar_file.add(f, tarname)

        f = p.join(package_dir, longname + ".tgz")
        cmd = "cd \"" + self.stage_dir + "\" ;tar cvzf \"" + f + "\" \"./\""
        print cmd
        os.system(cmd)
