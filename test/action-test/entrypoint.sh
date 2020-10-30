#!/bin/sh -l

apt-get update -y
apt-get install -y gcc-arm-none-eabi 
apt-get install make -y

make clean 
make all 

make clean test
./ventilation_test


