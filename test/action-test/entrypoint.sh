#!/bin/sh -l

apt-get update --yes
apt-get install --yes cmake
apt-get install --yes git
apt-get install --yes g++-8

mkdir lib
cd lib
git clone https://github.com/google/googletest/

cd ..
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=g++-8
make all

chmod +x ../../build/test/githubAction_test
./../../build/test/githubAction_test


