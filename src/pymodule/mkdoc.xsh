#!/bin/xonsh

import os

# does not work because pybind11_mkdoc only provides a module script
#from pybind11_mkdoc import mkdoc
ignore_files = [
    # 'classhelper.hpp'
]

headers = []
for r, d, f in os.walk('../themachinethatgoesping/'):
    for file in f:
        if file.endswith('.hpp'):
            if file not in ignore_files:
                headers.append(r + '/' + file)
headers.sort()

# this only works using the xonsh shell which can call bash commands from python
# echo running python3 -m pybind11_mkdoc -o docstrings.hpp @(headers)
python3 -m pybind11_mkdoc -o docstrings.hpp @(headers)
