
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#define N 			1


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

long double montecarlo(int number_of_tosses){
  int number_in_circle = 0;
  int toss;


    #pragma omp parallel for shared(number_of_tosses) reduction(+:number_in_circle) private(toss)
      for (toss = 0; toss < number_of_tosses; toss++) {
        double x= (double)rand()/RAND_MAX*2.0-1.0;//float in range -1 to 1
        double y=(double)rand()/RAND_MAX*2.0-1.0;//float in range -1 to 1
        double distance_squared= (x*x) + (y*y);
        //printf("%f - %f\n", x,y);
        if (distance_squared<=1){
          number_in_circle++;
        }
      }

      long double pi= 4*number_in_circle/((double)number_of_tosses);
      return pi;


}



int main(int argc, char const *argv[]) {
  srand ( time ( NULL));
  int number_of_tosses=10000000;
  ///
  int i=0;
   double ms;

   printf("starting...\n");
   ms = 0;
   long double pi=0;
   for (i = 0; i < N; i++) {
     start_timer();
     pi=montecarlo(number_of_tosses);
     ms += stop_timer();
   }
   printf("%Lf\n", pi);
   printf("avg time = %.5lf ms\n", (ms / N));

  return 0;
}
