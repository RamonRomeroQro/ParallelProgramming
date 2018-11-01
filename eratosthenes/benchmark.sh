#!/bin/bash

if [ $# -eq 2 ]
then
mkdir sieves
cd ./tbb
g++ -ltbb tbbsieve.cpp -o tbb.out
echo "TBB"
./tbb.out $1 x > ./../sieves/tbbsieve.txt
rm ./tbb.out
cd ..


cd ./serial
gcc serialsieve.c -o serial.out
echo "Serial"
./serial.out $1 x > ./../sieves/serialsieve.txt
rm ./serial.out
cd ..


cd ./openmp
clang -Xpreprocessor -fopenmp -lomp openmpsieve.c -o openmp.out
echo "OpenMP"
./openmp.out $1 x > ./../sieves/openmpsieve.txt
rm ./openmp.out

cd ..
cd ./forkjoin
javac Main.java
echo "ForkJoin"
java Main $1 x > ./../sieves/forksieve.txt
rm -f *.class

cd ..
cd ./threads
javac Main.java
echo "Threads"
java Main $1 x > ./../sieves/threadsieve.txt
rm -f *.class

else

  cd ./tbb
  g++ -ltbb tbbsieve.cpp -o tbb.out
  echo "TBB"
  ./tbb.out $1
  rm ./tbb.out
  cd ..


  cd ./serial
  gcc serialsieve.c -o serial.out
  echo "Serial"
  ./serial.out $1
  rm ./serial.out
  cd ..


  cd ./openmp
  clang -Xpreprocessor -fopenmp -lomp openmpsieve.c -o openmp.out
  echo "OpenMP"
  ./openmp.out $1
  rm ./openmp.out

  cd ..
  cd ./forkjoin
  javac Main.java
  echo "ForkJoin"
  java Main $1
  rm -f *.class

  cd ..
  cd ./threads
  javac Main.java
  echo "Threads"
  java Main $1
  rm -f *.class
fi
