#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Tablero.h"

// Genera una matriz de nxn de manera dinámica.
matriz generarTablero(int n){
    matriz ptrAux; // Puntero auxiliar hacia una matriz.

    // Se le reserva memoria al puntero auxiliar y si es igual a null
    // eso implica que no se ha podido asignar memoria.
    if((ptrAux = (matriz)malloc(n*sizeof(ptrEntero))) == NULL){
        return;
    }
    int i, j;
    // Se itera sobre las filas (que son punteros a enteros).
    for(i = 0; i < n; i++){
        // Se le reserva memoria a cada puntero a entero y si es igual a null
        // eso implica que no se ha podido asignar la dirección.
        if((ptrAux[i] = (ptrEntero)malloc(n * sizeof(int))) == NULL){
            return;
        }
    }
    return ptrAux;
}

// Se libera la memoria de cada puntero del tablero.
void liberarTablero(matriz tablero, int n){
    int i;
    // Se libera la memoria del puntero de cada fila.
    for(i = 0; i < n; i++){
        free(tablero[i]);
    }
    free(tablero); // Se libera la memoria del puntero principal.
}

// Se rellenan de ceros cada una de las celdas del tablero.
void llenarTablero(matriz tablero, int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            tablero[i][j] = 0;  // Puesto que todavía no hay fichas sobre él.
        }
    }
}

// Muestra en pantalla el tablero creado.
void mostrarTablero(matriz tablero, int n){
    /*
    Aquí, el tablero se despliega de la siguiente manera:

       1   2   3   4   5...
    1|___|___|___|___|_F_|
    2
    3       # Si una ficha se encuentra dentro
    4         de una posición de la matriz: representarla
    5         mediante algún símbolo.
    .
    .
    .
    */

    // Contador para poder imprimir el tablero.
    int contador = n;
    // 3 contadores para poder iterar sobre la matriz.
    int borde, contenido, auxiliar;

    // Primer ciclo para imprimir los números del "techo".
    for (borde = 1; borde <= contador; borde++){
        // Para poder imprimir a la izquierda los números también.
        if (borde == 1){
            printf("     %d   ", borde);
        } else if(borde >= 10){         // Si no, los números se empiezan a ver raro.
            printf("%d   ", borde);

        } else{
            printf(" %d   ", borde);
        }
    }

    // Salto de línea.
    printf("\n");

    // Ahora en este for se imprime el contenido del tablero.
    for (contenido = 0; contenido < n; contenido++){
        // Los primeros 9 dígitos hay que imprimirlos de otra manera.
        if (contenido < 9){
                printf("  %d", (contenido + 1));
        }else{
                printf(" %d", (contenido + 1));
        }

        // Ya esto sería todo el contenido del tablero.
        for (auxiliar = 0; auxiliar < n; auxiliar++){
            printf("|_");
            if (tablero[contenido][auxiliar] == 1){
                printf("F_|");
            }
            else{
                printf("__|");
            }
        }
        printf("\n");
    }
}

// Método que indica en cual fila y columna poner una ficha.
void agregarFicha(matriz tablero, int n, int fila, int columna){
    // Por aquello de que quieran agregar una ficha en una posición afuera del tablero.
    if ((fila > n) || (columna > n)){
        printf("f: %i c: %i", fila, columna);
        printf("Esa posicion no existe en el tablero.\n");
    }

    if (tablero[fila - 1][columna - 1] == 1){
        printf("Ya hay una ficha en esta posición.");
    }
    // En caso de que las posiciones sean correctas.
    else{
        tablero[fila - 1][columna - 1] = 1;
    }
}

void copiar_matriz(matriz uno, matriz copia, int t){
    for(int i = 0 ; i < t ; i ++ ){
         for(int j = 0 ; j < t ; j ++){
             copia[i][j] = uno[i][j];
         }
    }
}

