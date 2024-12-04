#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Monte Carlo function
double monteCarlo(int numPoints) {
    int circle = 0; // Variable para almacenar los puntos dentro del círculo

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num(); // Semilla única por hilo
        int local_circle = 0; // Variable local para evitar condiciones de carrera

        #pragma omp for
        for (int i = 0; i < numPoints; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (x * x + y * y <= 1) {
                local_circle++;
            }
        }

        #pragma omp atomic
        circle += local_circle; // Actualización segura de la variable global
    }

    return 4.0 * circle / numPoints; // Devolvemos el valor de PI
}

int main(int argc, char *argv[]) {
    int numPoints;
    printf("Enter the number of points: ");
    scanf("%d", &numPoints);

    // Calculamos el tiempo para diferentes números de hilos
    for (int threads = 1; threads <= 8; threads++) {
        omp_set_num_threads(threads); // Establecemos el número de hilos

        double start = omp_get_wtime(); // Tiempo inicial
        double pi = monteCarlo(numPoints); // Cálculo de PI
        double end = omp_get_wtime(); // Tiempo final

        printf("Threads: %d, PI: %.10f, Time: %f (s)\n", threads, pi, end - start);
    }

    return 0;
}
