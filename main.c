#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "APIG23.h"
#include"APIP2.h"

void analizeResult(char a){
    if (a == '1'){
        printf("Error en el ordenamiento\n");
        exit(EXIT_FAILURE);
    }
}


int main() {
    Grafo G = ConstruirGrafo();
    u32 N = NumeroDeVertices(G);
    u32 * Orden = calloc(N, sizeof(u32));
    u32 * Orden1 = calloc(N, sizeof(u32));
    u32 * Color = calloc(N, sizeof(u32));
    u32 * Color1 = calloc(N, sizeof(u32));
    double time_spent = 0.0;
    clock_t begin = clock();
    time_spent = 0.0;
    for (u32 i = 0; i < N; i++) {
        Orden[i] = i;
        Orden1[i] = i;
    }

    u32 color, iteraccionSeleccionada = 0, i = 0;
    char res;
    color = Greedy (G, Orden, Color);
    color = Greedy (G, Orden1, Color1);
    clock_t begin2 = clock();
    while (i < 500) {
        if (iteraccionSeleccionada < 16) {
            res = OrdenImparPar(N, Orden, Color);
            color = Greedy(G, Orden, Color);
            printf("OrdenImparPar pinto con %u colores \n" , color);

            res = OrdenJedi(G, Orden1, Color1);
            color = Greedy(G, Orden1, Color1);
            printf("OrdenJedi pinto con %u colores \n" , color);
            iteraccionSeleccionada++;
        } else {
            res = OrdenImparPar(N, Orden1, Color1);
            color = Greedy(G, Orden1, Color1);
            printf("OrdenImparPar pinto con %u colores \n", color);

            res = OrdenJedi(G, Orden, Color);
            color = Greedy(G, Orden, Color);
            printf("OrdenJedi pinto con %u colores \n" , color);
            iteraccionSeleccionada++;
            if (iteraccionSeleccionada == 32)
            {
                iteraccionSeleccionada = 0;
            }
        }
        analizeResult(res);

        i++;
        printf("IteracionGeneral numero : %d  \n\n" , i);
        clock_t end3 = clock();
        time_spent += (double)(end3 - begin2) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido %f \n\n", time_spent);
        time_spent = 0.0;

    }

    printf("Numero de colores: %u\n", color);

    DestruirGrafo(G);

    free(Orden);
    free(Color);
    free(Orden1);
    free(Color1);
    return 0;
}

