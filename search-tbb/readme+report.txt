Search - TBB - Reporte

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


Compilacion:
Single: $ g++ searchlinear.cpp -o single.out
Multi:  $ g++ searchtbb.c -o multi.out

Ejecucion:
Single:	$ ./single.out
Multi:	$ ./multi.out

Resultados y Observaciones:

./single.out:

  10 was found 999926 times in an array of 100000000 elements
  avg time = 581.377 ms (10 iterations)

./multi.out:

  10 was found 187017 times in an array of 100000000 elements
  avg time = 488.685 ms (10 iterations)



SpeedUp: 581.377 ms / 488.685 ms -> +1.18

Conclusiones:

Como hemos podido observar en ejercicios previos, para compensar el overhead de
la creación y llamada de los hilos, es necesario que el arreglo sea de una
dimension considerable y con ello sera posible identificar la mejora (SpeedUp) de paralizar
