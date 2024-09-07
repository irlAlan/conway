#!/usr/bin/bash

printf "Building...\n"
cmake -B build/;
cmake --build build/;
cd build; ./conway
printf "Done...\n"
