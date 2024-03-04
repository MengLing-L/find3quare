#!/bin/bash

rm librust_three_square.a rust_three_square.o
clang++ -std=c++11 -g -O0 -pthread -march=native -c rust_three_square.cpp -o rust_three_square.o $(pkg-config --cflags --libs gmp) -lstdc++ 
ar rcs librust_three_square.a rust_three_square.o
