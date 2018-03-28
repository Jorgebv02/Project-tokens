#ifndef TABLERO_H
#define TABLERO_H

typedef int ** matriz;   // Se define un puntero que apunta a punteros que a su vez apuntan a enteros.
typedef int * ptrEntero; // Puntero que apunta a un valor entero.

matriz generarTablero(int n);
void liberarTablero(matriz tablero, int n);
void llenarTablero(matriz tablero, int n);
void mostrarTablero(matriz tablero, int n);
void agregarFicha(matriz tablero, int n, int fila, int columna);
void copiar_matriz(matriz uno, matriz copia, int t);
#endif // TABLERO_H
