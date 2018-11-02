#include <stdio.h>
#include <stdlib.h>

#define SIZE 	1e6
#define THREADS 128
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#define N 			10
#define DISPLAY		100
#define MAX_VALUE	10000

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>


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


__global__ void init(int *a, int *limit) {
	int i = threadIdx.x + (blockIdx.x * blockDim.x);
	if (i < *limit) {
		a[i] = 0;
	}
}



__global__ void sieve(int *arr, int *sqroot, int *limit) {
  int c;
  for(c = 2; c <= *sqroot; c++) {
      if(arr[c] == 0) {
        ///
	arr[c]=0;
        int i = threadIdx.x + (blockIdx.x * blockDim.x);
        if (i < *limit) {
          if(i%c == 0) {
              arr[i] = 1;
          }

        }
        ///

        ///

      }
  }


}


void  printprimes(int limit, int *arr) {
  int c;
  //#pragma omp parallel for shared(arr, limit) private(c)
  for(c = 2; c <limit; c++) {
      if(arr[c] == 0) {
          fprintf(stdout,"%d ", c);
      }
  }
  fprintf(stdout,"\n");
  /* code */
}





int main(int argc, char* argv[]) {
  //////////INICIALIZACION
  int *p_array, *p_limit, *p_sqroot, *arr;
int limit=atoi(argv[1]);


//////////////////
double ms;
ms = 0;
int i;
for (i = 0; i < 10; i++) {
	start_timer();
	//->
	int sqroot = (int)sqrt(limit);
  cudaMalloc((void**) &p_array, limit * sizeof(int));
  cudaMalloc((void**) &p_limit, sizeof(int));
  cudaMalloc((void**) &p_sqroot, sizeof(int));
  cudaMemcpy(p_limit, &limit, sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(p_sqroot, &sqroot, sizeof(int), cudaMemcpyHostToDevice);
  //init<<<SIZE/THREADS, THREADS>>>(p_array, p_limit);
  cudaMemset(p_array, 0, limit*sizeof(int));
  arr = (int*)malloc(limit * sizeof(int));
  sieve<<<SIZE/THREADS, THREADS>>>(p_array, p_sqroot, p_limit);
  cudaMemcpy(arr, p_array, limit * sizeof(int), cudaMemcpyDeviceToHost);
	//
	cudaFree(p_array);
  cudaFree(p_limit);
  cudaFree(p_sqroot);
	free(arr);
	ms += stop_timer();

}
	printf("times %i - avg time = %.5lf ms\n",N,(ms / N));





  ///////////////







  printprimes(limit, arr);



	return 0;
}
