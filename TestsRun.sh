#!/bin/bash

if [ -e /build/Debug/TESTURNNER ] ; then
    ./build/Debug/TESTRUNNER

else
    ./Build.sh Debug
    cd build/Debug
    ./TESTRUNNER
fi

