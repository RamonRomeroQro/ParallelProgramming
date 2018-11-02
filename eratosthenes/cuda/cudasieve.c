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

void display_array(const char *text, int *array) {
	int i;

	printf("%s = [%4i", text, array[0]);
	for (i = 1; i < DISPLAY; i++) {
		printf(",%4i", array[i]);
	}
	printf(", ... ,]\n");
}



__global__ void add(int *a, int *b, int *c) {
	int i = threadIdx.x + (blockIdx.x * blockDim.x);
	if (i < SIZE) {
		c[i] = a[i] + b[i];
	}
}

__global__ void init(int *a, int *limit) {
	int i = threadIdx.x + (blockIdx.x * blockDim.x);
	if (i < *limit) {
		a[i] = 0;
	}
}



__global__ void sieve(int *arr, int *sqroot) {
  int i = threadIdx.x + (blockIdx.x * blockDim.x);
	if (i < *limit) {
		a[i] = 0;
	}
  int c;
  int m;
  for(c = 2; c <= *sqroot; c++) {
      if(arr[c] == 0) {
        ///
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
  int limit=1000;
  int sqroot = (int)sqrt(limit);

  cudaMalloc((void**) &p_array, limit * sizeof(int));
  cudaMalloc((void**) &p_limit, sizeof(int));
  cudaMalloc((void**) &p_sqroot, sizeof(int));
  cudaMemcpy(p_limit, &limit, sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(p_sqroot, &sqroot, sizeof(int), cudaMemcpyHostToDevice);
  //init<<<SIZE/THREADS, THREADS>>>(p_array, p_limit);
  //cudaMemset(p_array, 0, limit*sizeof(int));
  arr = (int*)malloc(limit * sizeof(int));
  sieve<<<SIZE/THREADS, THREADS>>>(p_array, p_sqroot);
  cudaMemcpy(arr, p_array, limit * sizeof(int), cudaMemcpyDeviceToHost);
  ///////////////
  printprimes(limit, arr);
  cudaFree(p_array);
  cudaFree(p_limit);
  cudaFree(p_sqroot);
	free(arr);


	return 0;
}




/*

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

void  printprimes(int limit, int *arr) {
  int c;
  //#pragma omp parallel for shared(arr, limit) private(c)
  for(c = 2; c <limit; c++) {
      if(arr[c] == 0) {
          fprintf(stdout,"%d ", c);
      }
  }
  fprintf(stdout,"\n");
}



int main(int argc, char **argv) {
  int N=1;
  int limit ;
  if (argc>3){
    fprintf(stderr, "Error: uso: %s [limite_superior_positivo]\n", argv[0]);
    return -1;

  }else if (argc==2 || argc==3) {
    int parsed=atoi(argv[1]);
    if (parsed<0){
      fprintf(stderr, "Error: uso: %s [limite_superior_positivo]\n", argv[0]);
      return -1;
    }else{
      limit=parsed;
    }
    if (argc==3) {
      N=1;
    }
  }else {
    limit=16;
  }

    int *arr;
    int *d_a;

    double ms;
    ms = 0;
    int i;
    for (i = 0; i < N; i++) {
      start_timer();
      //->
      int sqroot = (int)sqrt(limit);
      arr = (int*)malloc(limit * sizeof(int));
      cudaMalloc((void**) &d_a, limit * sizeof(int));
      init<<<SIZE/THREADS, THREADS>>>(d_a, d_b, d_c);


      int c;
      int m;
      for(c = 2; c <= sqroot; c++) {
          if(arr[c] == 0) {
            #pragma omp parallel for shared(arr, limit, c) private(m)
              for(m = c+1; m < limit; m++) {
                  if(m%c == 0) {
                      arr[m] = 1;
                  }
              }

          }
      }






      ms += stop_timer();
    }
    if (argc==2){
      printf("times %i - avg time = %.5lf ms\n",N,(ms / N));
    }





    printprimes(limit, arr);



    free(arr);

    return 0;
}

*/
