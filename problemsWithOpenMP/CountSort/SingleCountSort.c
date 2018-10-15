/*
    José Ramón Fernando Romero Chávez
    A01700318

*/
/* This code implements the known sort algorithm "Bubble sort Multithread" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#define SIZE 100
#define N 			1
#define DISPLAY		100
#define MAX_VALUE	100

struct timeval startTime, stopTime;
int started = 0;

void start_timer() {
 started = 1;
 gettimeofday(&startTime, NULL);
}

double stop_timer() {
 long seconds, useconds;
 double duration = -1;

 if (started) {
   gettimeofday(&stopTime, NULL);
   seconds  = stopTime.tv_sec  - startTime.tv_sec;
   useconds = stopTime.tv_usec - startTime.tv_usec;
   duration = (seconds * 1000.0) + (useconds / 1000.0);
   started = 0;
 }
 return duration;
}

void random_array(int *array, int size) {
 int i;

 srand(time(0));
 for (i = 0; i < size; i++) {
   array[i] = (rand() % 100) + 1;
 }
}

void fill_array(int *array, int size) {
 int i;

 for (i = 0; i < size; i++) {
   array[i] = (i % MAX_VALUE) + 1;
 }
}

void display_array(char *text, int *array) {
 int i;

 printf("%s = [%4i", text, array[0]);
 for (i = 1; i < DISPLAY; i++) {
   printf(",%4i", array[i]);
 }
 printf(", ... ]\n");
}



// A function to implement bubble sort

void CountSort(int a[], int n) {
  int i, j, count;
  int * temp = malloc(n * sizeof(int));
  for (i = 0; i < n; i++) {
    count = 0;
    for (j = 0; j < n; j++){
      if (a[j] < a[i]){
        count++;
      }
      else if (a[i] == a[j] && j < i){
        count++;
      }
    }
    temp[count] = a[i];
  }
  memcpy(a, temp, n * sizeof(int));
  free(temp);
}



int main(int argc, char* argv[]) {
 int i, *array;
 double ms;

 array = (int*) malloc(sizeof(int) * SIZE);
 random_array(array, SIZE);
 display_array("before", array);

 printf("starting...\n");
 ms = 0;
 for (i = 0; i < N; i++) {
   start_timer();
   CountSort(array, SIZE);
   ms += stop_timer();
 }
 display_array("after", array);
 printf("avg time = %.5lf ms\n", (ms / N));

 free(array);
 return 0;
}
