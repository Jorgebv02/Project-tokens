/*
**************************************************
C�digo fuente: fichas.c
Versi�n: 1.0
Fecha de creaci�n: 7 de marzo del 2018.
�ltima actualizaci�n: N/A.
Autores: Jorge Barquero Villalobos,
         Juan Diego Escobar S�ncehz,
         Yericka Lafuente Ovares,
         basados en la Prof. Ericka Solano Fern�ndez.
Descripci�n: c�digo que permite la manipulaci�n de fichas
en un tablero y realizar acciones sobre el mismo.
Notas:

Construido con: Gcc 4.9.
**************************************************
*/

#include <stdio.h>
#include <stdlib.h>

// Definimos una estructura de filas.
typedef struct{
    int N;      // Tama�o de la fila.
    int fila[]; // Las filas como tal.
} Fila;

// Esta ser�a la estructura del tablero.
typedef struct {
    int N;              // Tama�o del tablero.
    Fila dimension[];   // La matriz como tal.
} Tablero;

// Funci�n para asignarle el contenido a un tablero.
void asignaTamano(int T, Tablero elTablero){
    // Inicialmente, el tablero debe de estar lleno de 0.
    /*
    int contador;   // Variable para ir llenando la matriz de 0.
    int auxiliar;   // Para poder accesar dentro de la matriz.

    for (contador = 0; contador < T; contador++){
        for (auxiliar = 0; auxiliar < T; auxiliar++){
            elTablero.dimension[contador].fila = 0;

        }
    }
*/
}

// Funci�n para ver el contenido de un tablero.
void verTablero(Tablero elTablero){
    /*
    Aqu�, queremos que el tablero se imprima de la siguiente manera:

    ---1---2---3---4---5...
    1|___|___|___|___|_F_|
    2
    3       # Si una ficha se encuentra dentro
    4         de una posici�n de la matriz: representarla
    5         mediante alg�n s�mbolo.
    .
    .
    .


    // Contador para poder imprimir el tablero.
    int contador = elTablero.N;
    int borde;
    int contenido;


    // Primer ciclo para imprimir los n�meros del "techo".
    for (borde = 1; borde <= contador; borde++){
        // Para poder imprimir a la izquierda los n�meros tambi�n.
        if (borde == 1){
            printf("    %d  ", borde);
        } else if(borde >= 10){ // Si no, los n�meros se empiezan a ver raro.
            printf("%d  ", borde);

        } else{
            printf(" %d  ", borde);
        }
    }

    // Salto de l�nea com�n y corriente.
    printf("\n");

    // Segundo ciclo para imprimir el techo.
    for (borde = 1; borde <= contador; borde++){
        if (borde == 1){
            printf("   ----");
        } else{
            printf("----");
        }

    }

    // Salto de l�nea, de nuevo XD.

    // Ahora en este for, se va a imprimir el contenido del tablero.
    // for ()

    */
}

int main()
{
    // Peque�o ejemplo del constructor, pero igual hay que asignarle tama�o.
    // Tablero Ludo;
    // Ludo.N = 5;

    // asignaTamano(5, Ludo);

    // verTablero(Ludo);

/*
    FILE *archivo;      // Puntero de un archivo.
    char nombre[50];    // Donde almacenar el nombre del archivo.
    char caracter;

    printf("Por favor, indique el nombre del archivo: \n");
    scanf("%s", nombre);

    // Se intenta abrir.
    archivo = fopen(nombre, "r");

    if (archivo == NULL){
            printf("\nError al intentar abrir el archivo. \n\n");
        }
        else{
            printf("\nEl contenido del archivo de prueba es: \n\n");
            while((caracter = fgetc(archivo)) != EOF){
                printf("%c",caracter);
            }
        }
        fclose(archivo);
    */

    return 0;
}
