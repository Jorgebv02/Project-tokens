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

// Definimos una estructura de filas.
typedef struct{
    int N;      // Tamaño de la fila.
    int fila[]; // Las filas como tal.
} Fila;

// Esta sería la estructura del tablero.
typedef struct {
    int N;              // Tamaño del tablero.
    Fila dimension[];   // La matriz como tal.
} Tablero;

// Función para asignarle el contenido a un tablero.
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

// Función para ver el contenido de un tablero.
void verTablero(Tablero elTablero){
    /*
    Aquí, queremos que el tablero se imprima de la siguiente manera:

    ---1---2---3---4---5...
    1|___|___|___|___|_F_|
    2
    3       # Si una ficha se encuentra dentro
    4         de una posición de la matriz: representarla
    5         mediante algún símbolo.
    .
    .
    .


    // Contador para poder imprimir el tablero.
    int contador = elTablero.N;
    int borde;
    int contenido;


    // Primer ciclo para imprimir los números del "techo".
    for (borde = 1; borde <= contador; borde++){
        // Para poder imprimir a la izquierda los números también.
        if (borde == 1){
            printf("    %d  ", borde);
        } else if(borde >= 10){ // Si no, los números se empiezan a ver raro.
            printf("%d  ", borde);

        } else{
            printf(" %d  ", borde);
        }
    }

    // Salto de línea común y corriente.
    printf("\n");

    // Segundo ciclo para imprimir el techo.
    for (borde = 1; borde <= contador; borde++){
        if (borde == 1){
            printf("   ----");
        } else{
            printf("----");
        }

    }

    // Salto de línea, de nuevo XD.

    // Ahora en este for, se va a imprimir el contenido del tablero.
    // for ()

    */
}

int main()
{
    // Pequeño ejemplo del constructor, pero igual hay que asignarle tamaño.
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
