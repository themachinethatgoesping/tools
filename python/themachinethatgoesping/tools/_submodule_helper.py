# SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

"""
Helper to expose C++ submodules in Python wrapper packages.

This enables both import styles:
  - from themachinethatgoesping.module import submodule
  - import themachinethatgoesping.module.submodule
"""

import sys
import types


def expose_submodules(cpp_module, package_name):
    """
    Dynamically expose all submodules from a C++ binding module.
    
    Args:
        cpp_module: The C++ binding module (e.g., algorithms_nanopy)
        package_name: Full package name (e.g., 'themachinethatgoesping.algorithms')
    
    Returns:
        dict: Dictionary of submodule names to submodule objects to add to globals()
    """
    submodules = {}
    
    # Iterate through all attributes in the C++ module
    for attr_name in dir(cpp_module):
        if attr_name.startswith('_'):  # Skip private attributes
            continue
            
        attr = getattr(cpp_module, attr_name)
        
        # Check if it's a module (submodule)
        if isinstance(attr, types.ModuleType):
            # Add to return dict so caller can add to globals()
            submodules[attr_name] = attr
            
            # Also ensure it's in sys.modules with the full path for direct imports
            full_name = f'{package_name}.{attr_name}'
            if full_name not in sys.modules:
                sys.modules[full_name] = attr
    
    return submodules
