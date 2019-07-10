#!/usr/bin/env sh
clang++ -I./include -O3 test/fibonacci/fibonacci.cc -S -emit-llvm
clang++ -O3 fibonacci.ll
./a.out
rm fibonacci.ll
