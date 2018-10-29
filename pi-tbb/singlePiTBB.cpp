/*

Pi - Single - TBB - Reporte
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
const int GRAIN = 100000;

class SinglePi {
public:
	int size;
	double result;

public:
	SinglePi(int s) : size(s){}

	long getResult() const {
		return result;
	}

	void calculate() {
		double mid, height,width;
		double sum  = 0;
		width = 1.0/size;

		for (double i = 0; i < size ; i++) {
				mid=(i+.5)*width;
				height = 4.0 / (1.0 + mid* mid);
				double a=sum;
				sum+= height;
		}

		result = width * sum;

	}
};


int main(int argc, char* argv[]) {
	Timer t;
	double ms;
	long result;
	int *a = new int[SIZE];
		SinglePi sa(SIZE);
		cout << "Starting..." << endl;
		ms = 0;
		for (int i = 0; i < N; i++) {
			t.start();
			sa.calculate();
			ms += t.stop();
		}
		cout << "\nPi: " << sa.result << " size: "<< SIZE << " Times "<< N << endl;
		cout << "avg time = " << (ms/N) << " ms\n" << endl;


		return 0;
	}
