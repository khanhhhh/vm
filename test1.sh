#!/usr/bin/env sh
g++ -I./include -O3 test/fibonacci/fibonacci.cc -S -std=c++17
g++ -O3 fibonacci.s
./a.out
