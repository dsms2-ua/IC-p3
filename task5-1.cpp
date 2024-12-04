#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double calculate_pi(int n) {
    double step = 1.0 / n; // Ancho de cada bloque
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        double x = (i + 0.5) * step; // Punto medio del bloque
        sum += 1.0 / (1.0 + x * x);
    }

    return 4.0 * sum * step; // Multiplica por 4 y el ancho del bloque
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número de bloques>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Número de bloques ingresado por el usuario
    if (n <= 0) {
        printf("El número de bloques debe ser un entero positivo.\n");
        return 1;
    }

    printf("Número de bloques: %d\n", n);

    for (int threads = 1; threads <= 4; threads++) { // Probar con 1 a 8 hilos
        omp_set_num_threads(threads); // Establece el número de hilos

        double start = omp_get_wtime(); // Tiempo inicial
        double pi = calculate_pi(n);   // Cálculo de π
        double end = omp_get_wtime();  // Tiempo final

        printf("Threads: %d, π: %.15f, Time: %f (s)\n", threads, pi, end - start);
    }

    return 0;
}
