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

class ParallelCount {
private:
	int *myArray;


public:
  int count;
  int instance;

	ParallelCount(int *array, int k) : myArray(array), count(0), instance(k) {}

	ParallelCount(ParallelCount &x, split)
		: myArray(x.myArray), count(0) {}

	void operator() (const blocked_range<int> &r) {
		for (int i = r.begin(); i != r.end(); i++) {
			if (instance == myArray[i]) {
				count++;
			}
		}
	}

	void join(const ParallelCount &x) {
		count += x.count;
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
	/*
	int ins;
	printf("which is the number we are looking for?\n");
	scanf("%i", &ins);
	printf("%i\n", ins);
	*/
	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 0; i < N; i++) {
		t.start();
		ParallelCount obj(a, ins);
		parallel_reduce( blocked_range<int>(0, SIZE, GRAIN),
	                 obj );
	    result = obj.count;
		ms += t.stop();
	}
	printf("%i was found %li times in an array of %i elements\n", ins, result, SIZE);
	cout << "avg time = " << (ms/N) << " ms" << endl;

	delete [] a;

	return 0;
}
