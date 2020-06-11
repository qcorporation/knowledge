#!/bin/sh

# Development stack for C++
# Visual Code + Clang latest (10) + LLVM

apt-get update
apt-get install build-essential cmake -y
bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

## Optional, setup your configuration
# sudo update-alternatives --install /usr/bin/cc cc /usr/bin/clang-10 100
# sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-1.0 100

