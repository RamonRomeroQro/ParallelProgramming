#!/bin/bash
cd ./tbb
g++ -ltbb tbbsieve.cpp -o tbb.out
./tbb.out 99
