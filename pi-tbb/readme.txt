Pi - TBB - ReadMe

Jose Ramon Romero Chavez
A01700318


Device:

MacBook Pro (Retina, 13-inch, Early 2015)
  o macOS Mojave 10.14 (18A391)
  o Processor Name: Intel Core i5 o Processor Speed: 2.7 GHz
  o Number of Processors: 1
  o Total Number of Cores: 2 with hyperthreading
  o L2 Cache (per Core): 256 KB
  o L3 Cache: 3 MB
  o Memory: 8 GB 1867 MHz DDR3
  o Apple LLVM version 10.0.0 (clang-1000.11.45.2)
  o Target: x86_64-apple-darwin18.0.0
  o Thread model: posix


Compilacion:
Single: $ g++ searchlinear.cpp -o single.out
Multi:  $ g++ -ltbb searchtbb.c -o multi.out

Ejecucion:
Single:	$ ./single.out
Multi:	$ ./multi.out

Resultados y Observaciones:

MacBook-Pro-de-Ramon-2:pi-tbb ramonromero$ g++ singlePiTBB.cpp  -o single.out
MacBook-Pro-de-Ramon-2:pi-tbb ramonromero$ g++ -ltbb multiPiTBB.cpp -o multi.out
MacBook-Pro-de-Ramon-2:pi-tbb ramonromero$ ./single.out
Starting...

Pi: 3.14159 size: 100000000 Times 10
avg time = 457.504 ms

MacBook-Pro-de-Ramon-2:pi-tbb ramonromero$ ./multi.out
Starting...

Pi: 3.14159 size: 100000000 Times 10
avg time = 273.718 ms
