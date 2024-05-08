#include <stdio.h>
#include <omp.h>

int main()
{
	// Beispiel von L02, S. 10
	#pragma omp parallel
	printf("Hello from thread %d of %d threads !\n", 
		omp_get_thread_num(), 
		omp_get_num_threads()
	);
}
