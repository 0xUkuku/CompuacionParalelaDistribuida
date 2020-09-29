// Source code from:
// https://waxworksmath.com/Authors/N_Z/Pacheco/problems/chap04/prob_4.6.1.c
#include <stdlib.h>
#include <stdio.h>
#include </usr/local/include/mpi.h>

int main(int argc, char** argv) {
    int         my_rank;   /* Rango de mi proceso */
    int         p;         /* El número de procesos */
    float       a = 0.0;   /* Endpoint izquierdo */
    float       b = 1.0;   /* Endpoint derecho */
    int         n = 4096;  /* Número de trapezoides */
    float       h;         /* Longitud de la base del trapecio*/
    float       local_a;   /* Endpoint izquierdo de mi proceso */
    float       local_b;   /* Endpoint derecho de mi proces */
    int         local_n;   /* Número de trapezoides para el calculo  */
    float       integral;  /* Integral sobre el intervalo */
    float       total;     /* Integral total */
    int         source;    /* Proceso de envío integral  */
    int         dest = 0;  /* Todos los mensajes van a 0 */
    int         tag = 0;
    MPI_Status  status;

    float Trap(float local_a, float local_b, int local_n,
              float h);    /* Calcula la integral local */

    MPI_Init(&argc, &argv);

    /* Obtener el rango de mi proceso */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Obtiene cuántos procesos se están utilizando */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    h = (b-a)/n;    /* h es igual para todos los procesos */
    local_n = n/p;  /* También lo es el número de trapezoides */

    /* integración = local_n*h */
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    integral = Trap(local_a, local_b, local_n, h);

    /* Suma las integrales calculadas por cada proceso */
    if (my_rank == 0) {
        total = integral;
        for (source = 1; source < p; source++) {
            MPI_Recv(&integral, 1, MPI_FLOAT, source, tag,
                MPI_COMM_WORLD, &status);
            total = total + integral;
        }
    } else {
        MPI_Send(&integral, 1, MPI_FLOAT, dest,
            tag, MPI_COMM_WORLD);
    }

    if (my_rank == 0) {
        printf("Con n = %d trapezoides, nuestra estimación\n",n);
        printf("con una la integral de %f a %f = %f\n",
            a, b, total);
    }

    /* Shut down MPI */
    MPI_Finalize();
} /*  main  */


float Trap(
          float  local_a   /* in */,
          float  local_b   /* in */,
          int    local_n   /* in */,
          float  h         /* in */) {

    float integral;   /* Almacena los resultados de la integral  */
    float x;
    int i;

    float f(float x); /* función de integración */

    integral = (f(local_a) + f(local_b))/2.0;
    x = local_a;
    for (i = 1; i <= local_n-1; i++) {
        x = x + h;
        integral = integral + f(x);
    }
    integral = integral*h;
    return integral;
} /*  Trap  */


float f(float x) {
    float return_val;
    /* Calcula f(x). */
    /* Almacena el resultado en return_val. */
    return_val = x*x;
    return return_val;
} /* f */
