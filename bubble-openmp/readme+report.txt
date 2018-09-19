Bubble Sort - OpenMP - Reporte

Jose Ramon Romero Chavez
A01700318


Device:

MacBook Pro (Retina, 13-inch, Early 2015)
o macOS High Sierra 10.13.6 (17G65)
o Processor Name: Intel Core i5 o Processor Speed: 2.7 GHz
o Number of Processors: 1
o Total Number of Cores: 2 with hyperthreading
o L2 Cache (per Core): 256 KB
o L3 Cache: 3 MB
o Memory: 8 GB 1867 MHz DDR3


Compilacion:
Single:	$ gcc bubble.c -o single.out
Multi: macOS: $ clang -Xpreprocessor -fopenmp -lomp bubbleopenmp.c -o multi.out

Ejecucion:
Single:	$ ./single.out
Multi:	$ ./multi.out

Caso 1:

10 iteraciones
10000 longitud de arreglo

Resultados y Observaciones:

./single.out	->	avg time = 144.15230 ms
./multi.out	->	avg time = 97.06660 ms

SpeedUp 	->	144.15230 ms/ 97.06660 ms = 1.4850  	++

Caso 2:
 
10 iteraciones
100 longitud de arreglo


./single.out	->	avg time = 0.01640 ms
./multi.out	->	avg time = 0.07100 ms

SpeedUp 	->	0.01640 ms / 0.07100 ms = .2309		--


Conclusiones:

Como hemos podido observar en ejercicios previos, para compensar el overhead de la creación de los hilos, es necesario que el arreglo sea de una dimension considerable

Adicionalmente, se pudo observar la mejora del uso de apuntadores (por referencia) al realizar el swap ante la opción de hacer asignaciones por copia.







