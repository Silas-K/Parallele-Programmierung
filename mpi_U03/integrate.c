#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

double integrate(double from, double to, double (*func)())
{
    double h = (to - from);
    double sum = 0.0, x;

    // Untersumme berechnen
    x = from;
    sum += func(x);
    printf("Incrementing %lf\n", func(x));
    printf("X: %lf\n", x);
    printf("Adding %lf\n", h * sum);
    return h * sum;
}

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);
    MPI_Status status;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello World! I am %d of %d\n", rank, size);

    // Integrationslimits
    double a = 0., b = 2., res = 0., tmp;

    // Limits für mich
    double mya = a + rank * (b - a) / size; // rank = 0,1,2,..., (Anzahl der Prozesse im Kommunikator - 1)
    double myb = mya + (b - a) / size;

    // f(x) über meinen eigenen Bereich integrieren
    double psum = integrate(mya, myb, sqrt);

    // rank 0 sammelt Teilergebnisse (Reduce-Schritt)
    if (rank == 0)
    {
        // lokales Ergebnis
        res = psum;

        // Teilergebnisse von anderen Prozessen empfangen
        for (int i = 1; i < size; ++i)
        {
            MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            res += tmp;
            // Empfangsbuffer
            // Länge
            // Datentyp
            // Rank des Senders
            // Tag
            // Status-Object
        }
        printf("Result: %.15lf\n", res);
    }
    else
    {                        // rank != 0 Teilergebnisse an Rank 0 schicken
        MPI_Send(&psum,      // Sendebuffer
                 1,          // Länge
                 MPI_DOUBLE, // Datentyp
                 0,          // Zielrank
                 0,          // Tag (muss übereinstimmen)
                 MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
