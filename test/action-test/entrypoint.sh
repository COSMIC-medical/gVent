#!/bin/sh -l

apt-get update --yes
apt-get install -y gcc-arm-none-eabi 
 
make clean 
make all 

make clean test
./ventilation_test


