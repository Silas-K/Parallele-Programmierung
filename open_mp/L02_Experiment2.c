#include <stdio.h>
#include <omp.h>

int main()
{
	int tid=0, numth=1;
	// Ergänzung von Folie L02, 12
	#pragma omp parallel private(tid, numth)
	{
		#ifdef _OPENMP
		tid=omp_get_thread_num();
		numth=omp_get_num_threads();
		#endif
		printf("Hello from thread %d of %d threads !\n", 
			tid, 
			numth
		);
	}
}
