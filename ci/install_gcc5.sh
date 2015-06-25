#!/bin/sh

sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -qq

sudo apt-get install g++-5
sudo apt-get install gcc-5

export CC=gcc-5
export CXX=g++-5

sudo ln -sf /usr/bin/gcov-5 /usr/bin/gcov
