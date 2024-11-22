#!/bin/bash

clang++ -std=c++17 src/noises.cpp -o build/noises \
-I./raylib-5.0_linux_amd64/include \
./raylib-5.0_linux_amd64/lib/libraylib.a -lm 

if [ $? -ne 0 ]; then
    echo "Compile failed."
    exit 1
fi

./build/noises

