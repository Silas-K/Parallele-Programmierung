#include <stdio.h>
#include <omp.h>

int main (int argc, char* argv[])
{
	int N=12;
	double a[N][N],b[N][N];
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				a[i][j] = b[i][j] * 0.25;
			}
		} // sync
		#pragma omp for
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				b[i][j]=4*a[i][j];
			}
		} // sync
	} // sync
}
