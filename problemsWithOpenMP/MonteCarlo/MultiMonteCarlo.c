
#include <stdio.h>
#include <stdlib.h>
#include <time.h>






int main(int argc, char const *argv[]) {
  int number_in_circle = 0;
  srand ( time ( NULL));
  int toss;
  int number_of_tosses=1000000;

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




  printf("%Lf\n", pi);



  return 0;
}
