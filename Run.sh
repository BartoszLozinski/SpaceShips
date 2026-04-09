#!/bin/bash

if [ -d build ]; then
    ./build/Debug/SpaceShips

else
    ./Build.sh
    cd build/Debug
    ./SpaceShips
fi

