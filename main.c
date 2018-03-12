/*
**************************************************
Código fuente: fichas.c
Versión: 1.0
Fecha de creación: 7 de marzo del 2018.
Última actualización: N/A.
Autores: Jorge Barquero Villalobos,
         Juan Diego Escobar Sáncehz,
         Yericka Lafuente Ovares,
         basados en la Prof. Ericka Solano Fernández.
Descripción: código que permite la manipulación de fichas
en un tablero y realizar acciones sobre el mismo.
Notas:

Construido con: Gcc 4.9.
**************************************************
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ** matriz;   // Se define un puntero que apunta a punteros que a su vez apuntan a enteros.
typedef int * ptrEntero; // Puntero que apunta a un valor entero.

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
        for (auxiliar = 1; auxiliar <= n; auxiliar++){
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
    if ((fila >= n) || (columna >= n)){
        printf("Esa posición no existe en el tablero.");
    }
    else{
        printf("Ak7.");
    }
}

int main()
{
    int tamTablero = 5;
    matriz tablero = generarTablero(tamTablero);
    llenarTablero(tablero, tamTablero);

    mostrarTablero(tablero, tamTablero);
    return 0;
}
