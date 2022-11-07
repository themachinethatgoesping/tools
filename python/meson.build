# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- python sources --
sources = [
    'themachinethatgoesping/tools_ext/__init__.py',
    'themachinethatgoesping/tools_ext/timeconv_ext.py',
]

if get_option('build_pythonmodule').enabled()
    
    if get_option('pydev_install').disabled() #don't install if pydev_install is activated
        foreach source : sources
            #create install path for file
            fields = [pymod.get_install_dir()]
            foreach field : source.split('/')
                if not field.endswith('.py')
                    fields += [field]
                endif
            endforeach
            pth = '/'.join(fields)

            install_data(source, install_dir: pth, install_tag: 'python-runtime')
        endforeach

    endif
endif
