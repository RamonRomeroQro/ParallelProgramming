
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>

using namespace std;
using namespace tbb;

const int SIZE = 100000000;
const int GRAIN = 100000;

class ParallelSieve {

public:
	int *myArray;
	int c;

	ParallelSieve(int *array, int cm) : myArray(array), c(cm) {}

	ParallelSieve(ParallelSieve &x, split)
		: myArray(x.myArray), c(x.c)  {}
	void operator() (const blocked_range<int> &r) {
		for (int i = r.begin()+1; i != r.end(); i++) {
			myArray[c] = 0;
			if(i%c == 0) {
					myArray[i] = 1;

			}


		}
	}

	void join(const ParallelSieve &x) {
		myArray = x.myArray;
	}
};


void initarr(int limit,int *a) {
  int c;
  for(c = 2; c < limit; c++) {
      a[c] = 0;
  }
}

void  printprimes(int limit, int *arr) {
  int c;

  for(c = 2; c <limit; c++) {
      if(arr[c] == 0) {
          fprintf(stdout,"%d ", c);
      }
  }
  fprintf(stdout,"\n");
  /* code */
}



int main(int argc, char **argv) {

  int limit ;
  if (argc>2){
    fprintf(stderr, "Error: uso: %s [limite_superior_positivo]\n", argv[0]);
    return -1;

  }else if (argc==2) {
    int parsed=atoi(argv[1]);
    if (parsed<0){
      fprintf(stderr, "Error: uso: %s [limite_superior_positivo]\n", argv[0]);
      return -1;
    }else{
      limit=parsed;
    }
  }else {
    limit=16;
  }


    int sqroot = (int)sqrt(limit);
    int *arr = (int*)malloc(limit * sizeof(int));
    if(arr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for arr.\n");
        return -1;
    }

    initarr(limit, arr);

		int c;
		int m;
		for(c = 2; c <= sqroot; c++) {
				if(arr[c] == 0) {

					ParallelSieve obj(arr, c);

					parallel_reduce( blocked_range<int>(0, limit, limit+1),obj );
					arr = obj.myArray;

				}
		}


    printprimes(limit, arr);



    free(arr);

    return 0;
}
