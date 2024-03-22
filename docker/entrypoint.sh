#!/bin/bash
rm -r /usr/src//build/*
cmake -S /usr/src/ -B /usr/src//build -DCMAKE_PREFIX_PATH=/usr/local/
cmake --build /usr/src//build 