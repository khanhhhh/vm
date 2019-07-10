#!/usr/bin/env sh
clang++ -I./include -O3 test/fibonacci/fibonacci.cc -S
clang++ -O3 fibonacci.s
./a.out
rm fibonacci.s
