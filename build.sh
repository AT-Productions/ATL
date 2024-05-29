#!/bin/bash
cd "$(dirname "$0")"
# rm -rf build
if [ ! -d "build" ]; then
  mkdir build
fi

cd build

cmake ..
cmake --build .
cd ..
./build/atl -i test2.atl -o test