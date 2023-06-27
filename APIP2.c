
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "APIG23.h"
#include"APIP2.h"
#include"assert.h"

#define MAX_COLOR __UINT32_MAX__

// IVAN EZEQUIEL PONZIO ivan.ponzio@mi.unc.edu.ar
// FERNANDO ALVARADO    fernando.alvarado@mi.unc.edu.ar
// ARMANDO CARRAL    armando.carral@mi.unc.edu.ar   




struct información_de_coloreado {
  u32 cantidad;       
  u32 **mismocolor;  
  u32 *cantidades;  
};




//ACA EMPIEZA EL GREEDY
void MarcarColoresVecinos(u32 vertice, Grafo G, u32 *Colores, u32 *ColoresUsados, u32 iteracion) {
for (u32 j = 0; j < Grado(vertice, G); j++) {
u32 vecino = IndiceVecino(j, vertice, G);
if (Colores[vecino] != MAX_COLOR) {
ColoresUsados[Colores[vecino]] = iteracion + 1;
}
}
}

void ReiniciarColoresNoUsados(u32 vertice, Grafo G, u32 *Colores, u32 *ColoresUsados) {
  for (u32 j = 0; j < Grado(vertice, G); j++) {
        u32 vecino = IndiceVecino(j, vertice, G);
          if (Colores[vecino] != MAX_COLOR) {
              ColoresUsados[Colores[vecino]] = 0;
                                           }
                                               }
}




u32 Greedy(Grafo G, u32 *Orden, u32 *Colores) {
const u32 numVertices = NumeroDeVertices(G);


  for (u32 i = 0; i < numVertices; i++) {
          Colores[i] = MAX_COLOR;
  }

  u32 maxColores = 0;
  u32 *ColoresUsados = calloc(numVertices, sizeof(u32));

  for (u32 i = 0; i < numVertices; i++) {
        u32 vertice = Orden[i];
        Colores[vertice] = 0;

        MarcarColoresVecinos(vertice, G, Colores, ColoresUsados, i);


        u32 color = 0;
        while (ColoresUsados[color] == i + 1) {
              color++;
              }


      Colores[vertice] = color;
      if (color > maxColores) {
          maxColores = color;
          }


      ReiniciarColoresNoUsados(vertice, G, Colores, ColoresUsados);
  }
  free(ColoresUsados);
  return maxColores + 1; 
}
//ACA TERMINA GREEDY



//FUNCIONESAUXILIARES
void inicializar_cantidades(u32 n, u32 *Color, struct información_de_coloreado *colorInfo) {
  for (u32 i = 0; i < n; ++i) {
    ++(colorInfo->cantidades[Color[i]]);
  }
}

void crear_mismocolor(u32 n, u32 *Color, struct información_de_coloreado *colorInfo) {
  for (u32 i = 0; i < colorInfo->cantidad; ++i) {
    colorInfo->mismocolor[i] = malloc(colorInfo->cantidades[i] * sizeof(u32));
  }
  u32 *posiciones = calloc(colorInfo->cantidad, sizeof(u32));
  for (u32 i = 0; i < n; ++i) {
    colorInfo->mismocolor[Color[i]][posiciones[Color[i]]] = i;
    ++posiciones[Color[i]];
  }
  free(posiciones);
}

struct información_de_coloreado *infodecoloreo(u32 n, u32 *Color) {
  struct información_de_coloreado *colorInfo = malloc(sizeof(struct información_de_coloreado));
  if (colorInfo == NULL){
    return NULL;
  }
  colorInfo->cantidad = 0;
  for (u32 i = 0; i < n; ++i) {
    if (Color[i] > colorInfo->cantidad)
      colorInfo->cantidad = Color[i];
  }
  ++(colorInfo->cantidad);
  colorInfo->mismocolor = malloc(colorInfo->cantidad * sizeof(u32 *));
  if (colorInfo->mismocolor == NULL){
    free(colorInfo);
    colorInfo = NULL;
    return NULL;
  }
  colorInfo->cantidades = calloc(colorInfo->cantidad, sizeof(u32));
  if (colorInfo->cantidades == NULL){
    free(colorInfo);
    free(colorInfo->mismocolor);
    colorInfo->mismocolor = NULL;
    colorInfo = NULL;
    return NULL;
  }
  inicializar_cantidades(n, Color, colorInfo);
  crear_mismocolor(n, Color, colorInfo);
  return colorInfo;
}



void destroy_colores(struct información_de_coloreado *color) {
  for (u32 i = 0; i < color->cantidad; ++i) {
    free(color->mismocolor[i]);
  }
  free(color->cantidades);
  free(color->mismocolor);
}
//



//ACA EMPIEZA EL ORDENAMIENTO IMPARPAR
u32 encontrar_maximo_color(u32* Color, u32 n) {
  u32 maximo_color = 0;
  for (u32 i = 0; i < n; ++i) {
    if (Color[i] > maximo_color) {
      maximo_color = Color[i];
    }
  }
  return maximo_color;
}


void calcular_cantidades(u32* Color, u32 n, u32* cantidades, u32 cantidad_colores) {
  for (u32 i = 0; i < n; ++i) {
    ++cantidades[Color[i]];
  }
}


void agregarVerticeAConjuntoColor(u32** conjuntos_colores, u32* elementos_por_color, u32* Color, u32 i, u32 vertice) {
  conjuntos_colores[Color[i]][elementos_por_color[Color[i]]] = vertice;
  ++elementos_por_color[Color[i]];
}


void crearYllenarConjuntosDeVerticesPorColor(u32** conjuntos_colores, u32* Color, u32 n, u32* cantidades, u32 cantidad_colores) {
  u32* elementos_por_color = calloc(cantidad_colores, sizeof(u32));
  for (u32 i = 0; i < n; ++i) {
    agregarVerticeAConjuntoColor(conjuntos_colores, elementos_por_color, Color, i, i);
  }
  free(elementos_por_color);
}


void ordenar_impar_par(u32** V, u32* Orden, u32* cantidades, u32 cantidad_colores) {
  u32 k = 0;
  u32 mayorImpar;
  u32 mayorPar;
  if (cantidad_colores % 2 == 0) {
    mayorImpar = cantidad_colores - 1;
    mayorPar = cantidad_colores - 2;
  } else {
    mayorPar = cantidad_colores - 1;
    mayorImpar = cantidad_colores - 2;
  }
  
  for (u32 j = mayorImpar; 0 <= j && j < cantidad_colores; j -= 2) {
    for (u32 i = 0; i < cantidades[j]; ++i) {
      Orden[k] = V[j][i];
      ++k;
    }
  }

 
  for (u32 j = mayorPar; 0 <= j && j < cantidad_colores; j -= 2) {
    for (u32 i = 0; i < cantidades[j]; ++i) {
      Orden[k] = V[j][i];
      ++k;
    }
  }
}

char OrdenImparPar(u32 n, u32* Orden, u32* Color) {
 
  u32 cantidad_colores = encontrar_maximo_color(Color, n) + 1;

    
  u32** conjuntos_colores = malloc(cantidad_colores * sizeof(u32*));
  if (conjuntos_colores == NULL){
    return 1;
  }
  for (u32 i = 0; i < cantidad_colores; ++i) {
      conjuntos_colores[i] = calloc(n, sizeof(u32));
  }

  u32* cantidades = calloc(cantidad_colores, sizeof(u32));
  if (cantidades == NULL){
    return 1;
  }
  calcular_cantidades(Color, n, cantidades, cantidad_colores);


  crearYllenarConjuntosDeVerticesPorColor(conjuntos_colores, Color, n, cantidades, cantidad_colores);


  ordenar_impar_par(conjuntos_colores, Orden, cantidades, cantidad_colores);


  for (u32 i = 0; i < cantidad_colores; ++i) {
  free(conjuntos_colores[i]);
  }
  free(conjuntos_colores);
  free(cantidades);


return 0;
}
//ACA TERMINA EL ORDENAMIENTO IMPARPAR


//ACA EMPIEZA EL ORDENAMIENTO JEDI

static u32 *F;


static int cmpJedi(const void *a, const void *b) {
  u32 primero = *((u32 *)a);
  u32 segundo = *((u32 *)b);
  if (F[primero] < F[segundo]) {
    return -1;
  } else if (F[primero] == F[segundo]) {
    return 0;
  } else
    return 1;
}

static void calcular_F(Grafo G, u32* Color, u32* F, u32 cantidad_colores) {
  for (u32 i = 0; i < NumeroDeVertices(G); ++i) {
    F[Color[i]] += Grado(i, G);
  }
  for (u32 i = 0; i < cantidad_colores; ++i) {
    F[i] *= i;
  }
}



static void ordenar_V(struct información_de_coloreado *colorInfo, u32 *ordenColores) {
  qsort(ordenColores, colorInfo->cantidad, sizeof(u32), cmpJedi);
}


static void generar_orden_jedi(u32 *Orden, struct información_de_coloreado *colorInfo, u32 *ordenColores) {
  for (u32 j = 0, k = 0; j < colorInfo->cantidad; ++j) {
    for (u32 i = 0; i < colorInfo->cantidades[ordenColores[j]]; ++i) {
      Orden[k] = colorInfo->mismocolor[ordenColores[j]][i];
      ++k;
    }
  }
}


char OrdenJedi(Grafo G, u32 *Orden, u32 *Color) {
  assert(F == NULL);

  
  struct información_de_coloreado *colorInfo = infodecoloreo(NumeroDeVertices(G), Color);
  if (colorInfo == NULL){
    return 1;
  }
  
  u32 *ordenColores = malloc((colorInfo->cantidad) * sizeof(u32));
  if (ordenColores == NULL){
    return 1;
  }
  
  F = calloc(colorInfo->cantidad, sizeof(u32));
  if (F == NULL){
    return 1;
  }
    // Computamos las sumatorias de F
  for (u32 i = 0; i < NumeroDeVertices(G); ++i) {
    F[Color[i]] += Grado(i, G);
  }
  // Computamos el x * sumatoria
  for (u32 i = 0; i < colorInfo->cantidad; ++i) {
    F[i] *= i;
  }

  // inicializo ordenColores
  for (u32 i = 0; i < colorInfo->cantidad; ++i) {
    ordenColores[i] = i;
  }

  // Ordeno los V_i's segun F
  qsort(ordenColores, colorInfo->cantidad, sizeof(u32), cmpJedi);

  // Usando ordenColores y cantidades, aplano V para obtener el Orden Jedi
  for (u32 j = 0, k = 0; j < colorInfo->cantidad; ++j) {
    for (u32 i = 0; i < colorInfo->cantidades[ordenColores[j]]; ++i) {
      Orden[k] = colorInfo->mismocolor[ordenColores[j]][i];
      ++k;
    }
  }


  // calcular_F(G, Color, F, colorInfo->cantidad);

  // for (u32 i = 0; i < colorInfo->cantidad; ++i) {
  //   ordenColores[i] = i;
  // }

  // ordenar_V(colorInfo, ordenColores);
  // generar_orden_jedi(Orden, colorInfo, ordenColores);

  
  destroy_colores(colorInfo);
  free(F);
  F = NULL;

  return 0;
}

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "APIG23.h"

// Escribe aquí las definiciones y código de las funciones auxiliares

int main() {
    Grafo G = ConstruirGrafo();
    if (G == NULL) {
        printf("Error al construir el grafo.\n");
        return 1;
    }

    // Obtener el orden Jedi
    u32 numVertices = NumeroDeVertices(G);
    u32 *Color = malloc(numVertices * sizeof(u32));
    u32 *Orden = malloc(numVertices * sizeof(u32));
    if (Color == NULL || Orden == NULL) {
        printf("Error al asignar memoria.\n");
        DestruirGrafo(G);
        return 1;
    }

    // Asignar colores al azar
    for (u32 i = 0; i < numVertices; i++) {
        Color[i] = rand() % numVertices;
    }

    // Obtener el orden Jedi
    char resultado = OrdenJedi(G, Orden, Color);
    if (resultado == 0) {
        printf("Orden Jedi:\n");
        for (u32 i = 0; i < numVertices; i++) {
            printf("%u ", Orden[i]);
        }
        printf("\n");
    } else {
        printf("Error al calcular el orden Jedi.\n");
    }

    free(Color);
    free(Orden);
    DestruirGrafo(G);

    return 0;
}

