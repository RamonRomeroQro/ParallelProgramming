/*

Pi - Multi - TBB - Reporte
Jose Ramon Romero Chavez
A01700318

*/

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
const int GRAIN =  10*1000;

class ParallelPi {

public:
	double size;
	double suma;

	ParallelPi(double s) : suma(0.0),  size(s) {}

	ParallelPi(ParallelPi &x, split)
		: suma(0.0), size(x.size) {}

	void operator() (const blocked_range<int> &r) {
    double mid, height;
		for (int i = r.begin(); i < r.end(); i++) {
			mid = (double)(i + 0.5)* size;
      height = 4.0 / (1.0 + (mid * mid));
      suma += height;

		}
	}

	void join(const ParallelPi &x) {
		suma += x.suma;
	}
};

int main(int argc, char* argv[]) {
	Timer t;
	double ms;
	double result;

	cout << "Starting..." << endl;
	ms = 0;
  double w = 1.0 /(double) SIZE;
	for (int i = 0; i < N; i++) {
		t.start();
		ParallelPi obj(w);
		parallel_reduce( blocked_range<int>(0,SIZE, GRAIN),obj );
		result = obj.suma;
		result = result*w;
		ms += t.stop();
	}
	cout << "\nPi: " << result << " size: "<< SIZE << " Times "<< N << endl;
	cout << "avg time = " << (ms/N) << " ms\n" << endl;

	return 0;
}
