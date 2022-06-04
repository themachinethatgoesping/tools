#!/bin/xonsh

import os

#does not work because pybind11_mkdoc only provides a module script
#from pybind11_mkdoc import mkdoc

headers = []
for r,d,f in os.walk('../tools'):
    for file in f:
        if file.endswith('.h'):
            headers.append(r + '/' + file)
headers.sort()

#this only works using the xonsh shell which can call bash commands from python
echo running python3 -m pybind11_mkdoc -o docstrings.h @(headers)
python3 -m pybind11_mkdoc -o docstrings.h @(headers)