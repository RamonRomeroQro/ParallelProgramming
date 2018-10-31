
#include <math.h>
#include <stdio.h>
#include <stdlib.h>




void initarr(int limit,int *a) {
  int c;
  for(c = 2; c < limit; c++) {
      a[c] = 0;
  }
}

void sieve(int sqroot, int limit, int * arr){
  int c;
  int m;
  for(c = 2; c <= sqroot; c++) {
      if(arr[c] == 0) {
          for(m = c+1; m < limit; m++) {
              if(m%c == 0) {
                  arr[m] = 1;
              }
          }
      }
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
  }

    int sqroot = (int)sqrt(limit);
    int *arr = (int*)malloc(limit * sizeof(int));
    if(arr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for arr.\n");
        exit(-1);
    }

    initarr(limit, arr);
    sieve(sqroot, limit, arr);
    printprimes(limit, arr);



    free(arr);

    return 0;
}
