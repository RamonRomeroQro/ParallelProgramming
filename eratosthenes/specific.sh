#!/bin/bash
rm -fdR sieves
mkdir sieves

if [ $2 -eq 1 ]
then
  #serial

  cd ./serial
  gcc serialsieve.c -o serial.out
  echo "Serial"
  ./serial.out $1 x > ./../sieves/serialsieve.txt
  rm ./serial.out
  cd ..

elif [ $2 -eq 2 ]
then
  #openmp
  cd ./openmp
  clang -Xpreprocessor -fopenmp -lomp openmpsieve.c -o openmp.out
  echo "OpenMP"
  ./openmp.out $1 x > ./../sieves/openmpsieve.txt
  rm ./openmp.out
  cd ..
elif [ $2 -eq  3 ]
then
  #tbb
  cd ./tbb
  g++ -ltbb tbbsieve.cpp -o tbb.out
  echo "TBB"
  ./tbb.out $1 x > ./../sieves/tbbsieve.txt
  rm ./tbb.out
  cd ..
elif [ $2 -eq  4 ]
then
  #threads
  cd ./threads
  javac Main.java
  echo "Threads"
  java Main $1 x > ./../sieves/threadsieve.txt
  rm -f *.class

elif [ $2 -eq  5 ]
then
  #fj
  cd ./forkjoin
  javac Main.java
  echo "ForkJoin"
  java Main $1 x > ./../sieves/forksieve.txt
  rm -f *.class
  cd ..


fi
