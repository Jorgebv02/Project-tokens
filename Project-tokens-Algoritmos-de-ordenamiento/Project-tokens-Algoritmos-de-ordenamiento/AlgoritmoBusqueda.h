#ifndef ALGORITMOBUSQUEDA_H
#define ALGORITMOBUSQUEDA_H
#include "Tablero.h"
void mejor_movimiento();
int mejor_Caso_Vertical(matriz P, int t,matriz Sol,int mov);
int mejor_Caso_Horizontal(matriz P, int t,matriz Sol,int mov);
int AnalisisCasos_Auxiliar(matriz mtemp, int t,int fila,int columna,int *mov_temp,int ind, int mov);
int mejor_caso_diagonal(matriz P, int t,matriz Sol);
void Mejor_Opcion(matriz tablero, matriz Solucion, int t);
#endif // ALGORITMOBUSQUEDA_H
