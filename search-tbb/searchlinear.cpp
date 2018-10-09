#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include "utils/cppheader.h"

using namespace std;
using namespace tbb;

const int SIZE = 100000000;
const int GRAIN = 100000;

class SumArray {
public:
	int *array;
	int size;
	long result;
	long instance;

public:
	SumArray(int *a, int s, int k) : array(a), size(s), instance(k){}

	long getResult() const {
		return result;
	}

	void calculate() {
		result = 0;
		for (int i = 0; i < size; i++) {
			if (array[i]==instance){
				result=result+1;

			}

		}

	}
};


int main(int argc, char* argv[]) {
	Timer t;
	double ms;
	long result;
	int *a = new int[SIZE];

	random_array(a, SIZE);
	display_array("a", a);
	int ins=10;

		SumArray sa(a, SIZE, ins);
		cout << "Starting..." << endl;
		ms = 0;
		for (int i = 0; i < N; i++) {
			t.start();
			sa.calculate();
			ms += t.stop();
		}
		printf("%i was found %li times in an array of %i elements\n", ins, sa.result, SIZE);
		cout << "avg time = " << (ms/N) << " ms" << endl;

		delete [] a;

		return 0;
	}
