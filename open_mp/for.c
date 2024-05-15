#include <stdio.h>
#include <omp.h>

int main()
{
	int i, tid, numth, N = 1000;
	double a[N], b[N], c[N];

	// Initialize each element of the array with the value 5
	for (int i = 0; i < 1000; i++) {
		a[i] = 5;
		b[i] = 6;
	}

	// #pragma omp parallel
	// {
	// 	tid = omp_get_thread_num();
	// 	numth = omp_get_num_threads();
	// 	#pragma omp for
	// 	for(i=0; i<N; i++)
	// 	{
	// 		printf("Vektor Addition: working thread %d of %d threads ! \n",
	// 			tid,
	// 			numth);
	// 		c[i] = a[i] + b[i];
	// 	}
	// }
	
	#pragma omp parallel for 
	for(i=0; i<N; i++)
	{
		tid = omp_get_thread_num();
		numth = omp_get_num_threads();
		printf("Vektor Addition: working thread %d of %d threads ! \n",
	 tid,
		numth);
		c[i] = a[i] + b[i];
	}
	/* for(i=0; i<N; i++)
	{
		printf("Index %d - Wert %f", i, c[i]);
	} */
}
