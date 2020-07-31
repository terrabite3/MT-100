#!/bin/bash

set -o errexit
set -o nounset

cd `dirname "$0"`

mkdir -p build
cd build
conan install .. --build=missing
cmake ..