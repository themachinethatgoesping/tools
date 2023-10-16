# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- python sources --
sources = [
    'themachinethatgoesping/tools/__init__.py',
    'themachinethatgoesping/tools/timeconv.py',

    'themachinethatgoesping/scripts/oceanographic.py',
    'themachinethatgoesping/scripts/plot_tools.py',
    'themachinethatgoesping/scripts/read_xcf.py',
    'themachinethatgoesping/scripts/sbes.py',
    'themachinethatgoesping/scripts/mbes.py',
]

if get_option('build_pythonmodule').enabled()
    
    if get_option('pydev_install').disabled() #don't install if pydev_install is activated
        foreach source : sources
            #create install path for file
            fields = []
            foreach field : source.split('/')
                if not field.endswith('.py')
                    fields += [field]
                endif
            endforeach
            pth = '/'.join(fields)

            pymod.install_sources(source, subdir: pth, install_tag: 'python-runtime')
        endforeach

    endif
endif
