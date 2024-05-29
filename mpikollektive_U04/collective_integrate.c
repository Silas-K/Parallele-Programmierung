#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

double integrate(double from, double to, double (*func)())
{
    double h = (to - from);
    double sum = 0.0, x;

    // Untersumme berechnen
    for (x = from; x <= (to - h); x += h)
    {
        sum += func(x);
    }
    return h * sum;
}

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);
    MPI_Status status;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // printf("Hello World! I am %d of %d\n", rank, size);

    // Integrationslimits
    double a = 0., b = 2., res = 0., tmp;

    // Limits für mich
    double mya = a + rank * (b - a) / size; // rank = 0,1,2,..., (Anzahl der Prozesse im Kommunikator - 1)
    double myb = mya + (b - a) / size;

    // f(x) über meinen eigenen Bereich integrieren
    double psum = integrate(mya, myb, sqrt);

    // Reduce
    // rank 0 sammelt Teilergebnisse
    MPI_Reduce(&psum, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // print result in root (rank = 0)
    if (rank == 0)
    {
        printf("Result: %.15lf\n", res);
    }

    MPI_Finalize();
}
