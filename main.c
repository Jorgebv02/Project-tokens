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
#include <ctype.h>
#include <string.h>

typedef int ** matriz;   // Se define un puntero que apunta a punteros que a su vez apuntan a enteros.
typedef int * ptrEntero; // Puntero que apunta a un valor entero.

// Genera una matriz de nxn de manera din�mica.
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
        // eso implica que no se ha podido asignar la direcci�n.
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
            tablero[i][j] = 0;  // Puesto que todav�a no hay fichas sobre �l.
        }
    }
}

// Muestra en pantalla el tablero creado.
void mostrarTablero(matriz tablero, int n){
    /*
    Aqu�, el tablero se despliega de la siguiente manera:

       1   2   3   4   5...
    1|___|___|___|___|_F_|
    2
    3       # Si una ficha se encuentra dentro
    4         de una posici�n de la matriz: representarla
    5         mediante alg�n s�mbolo.
    .
    .
    .
    */

    // Contador para poder imprimir el tablero.
    int contador = n;
    // 3 contadores para poder iterar sobre la matriz.
    int borde, contenido, auxiliar;

    // Primer ciclo para imprimir los n�meros del "techo".
    for (borde = 1; borde <= contador; borde++){
        // Para poder imprimir a la izquierda los n�meros tambi�n.
        if (borde == 1){
            printf("     %d   ", borde);
        } else if(borde >= 10){         // Si no, los n�meros se empiezan a ver raro.
            printf("%d   ", borde);

        } else{
            printf(" %d   ", borde);
        }
    }

    // Salto de l�nea.
    printf("\n");

    // Ahora en este for se imprime el contenido del tablero.
    for (contenido = 0; contenido < n; contenido++){
        // Los primeros 9 d�gitos hay que imprimirlos de otra manera.
        if (contenido < 9){
                printf("  %d", (contenido + 1));
        }else{
                printf(" %d", (contenido + 1));
        }

        // Ya esto ser�a todo el contenido del tablero.
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

// M�todo que indica en cual fila y columna poner una ficha.
void agregarFicha(matriz tablero, int n, int fila, int columna){
    // Por aquello de que quieran agregar una ficha en una posici�n afuera del tablero.
    if ((fila > n) || (columna > n)){
        printf("f: %i c: %i", fila, columna);
        printf("Esa posicion no existe en el tablero.\n");
    }

    if (tablero[fila - 1][columna - 1] == 1){
        printf("Ya hay una ficha en esta posici�n.");
    }
    // En caso de que las posiciones sean correctas.
    else{
        tablero[fila - 1][columna - 1] = 1;
    }
}

// M�todo para poder abrir un archivo.
void abrirArchivo(){
    // Variables importantes:
    char nombreArchivo[50];  // Donde guardar el nombre del archivo.
    char contenido[1024];    // Para almacenar la informaci�n del archivo.
    int tamanoTablero;       // Un tama�o para el tablero.
    int contadorLinea = 0;   // Para contar el n�mero de l�nea.
    matriz Tablero;          // Un tablero a utilizar.
    char auxiliar;           // Auxiliar de copiado.
    char numero[2];          // Para guardar cada n�mero del archivo (uno a la vez).
    int tableroCreado = 0;   // 1 si el tablero ha sido creado, 0 en caso contrario.
    int contador = 0;        // Para las posiciones del arreglo numero.
    int fila_columna = 0;    // Contador para verificar los pares (fila, columna).
    int fila, columna;       // Para almacenar cada fila y columna que vengan en el archivo.

    // Se abre el archivo para lectura.
    FILE* archivo = fopen("PruebasGrupo1.txt", "r");

    // Si archivo es NULL entonces hubo un error al tratar de abrir el archivo.
    if(archivo == NULL){
        printf("Hubo un error con la apertura del archivo.\n\n");
        return;
    }

    // Se lee el archivo caracter por caracter.
    while(feof(archivo) == 0){

        // Si lee el tama�o de la matriz.
        if ((contadorLinea % 2) == 0){
            // Obtenemos el N.
            auxiliar = fgetc(archivo);
            numero[0] = auxiliar;
            // Se obtiene el resto de valores.
            auxiliar = fgetc(archivo);
            numero[1] = auxiliar;

            // En caso de que el tama�o de la matriz sea mayor o igual a 10 (2 d�gitos).
            if(numero[1] != '\n'){
                auxiliar = fgetc(archivo);
            }

            tamanoTablero = atoi(numero); // Obtenemos el N entero.
            numero[1] = ' ';

            // Se libera el espacio del tablero para proximamente crear otro.
            if(tableroCreado == 1){
                liberarTablero(Tablero, tamanoTablero);
            }

            // Se crea el tablero.
            Tablero = generarTablero(tamanoTablero);
            llenarTablero(Tablero, tamanoTablero);
            tableroCreado = 1;
            contadorLinea++;
        }

        // Son posiciones Fila y Columna.
        else{
            auxiliar = fgetc(archivo);

            // Si a�n no ha llegado al final de una l�nea del archivo.
            if(auxiliar != '\n'){
                // Si el caracter actual es un espacio.
                if(auxiliar == ' '){
                    // Si el contador fila_columna es par entonces quiere
                    // decir que ley� una fila.
                    if((fila_columna % 2) == 0){
                        fila = atoi(numero);
                    }
                    // Si el contador fila_columna es impar entonces quiere
                    // decir que ley� una columna.
                    else if((fila_columna % 2) != 0){
                        columna = atoi(numero);
                        agregarFicha(Tablero, tamanoTablero, fila, columna);
                    }
                    numero[contador-1] = auxiliar; // Se le asigna un espacio a numero[1].
                    contador = 0;
                    fila_columna++;
                }
                // Se lee otro n�mero.
                else{
                    numero[contador] = auxiliar;
                    contador++;
                }
            }
            // Si ya llego al final de una l�nea del archivo.
            else{
                contadorLinea++;
                columna = atoi(numero);
                // Se agrega la ficha y se muestra el tablero en pantalla.
                agregarFicha(Tablero, tamanoTablero, fila, columna);
                mostrarTablero(Tablero, tamanoTablero);
                printf("\n\n");
                // Se reinician los contadores.
                contador = 0;
                fila_columna = 0;
            }
        }
    }

    fclose(archivo); // Se cierra el archivo.
}

// M�todo que revisa el archivo.
// Revisa si las dimnesiones de las fichas son las mismas que
// vienen en el archivo, es decir, si el archivo brindase una
// matriz de tama�o 5, deber�an de venir 5 posiciones en filas.
int revisaArchivo(FILE* archivo){

}


// M�todo que dado un array y un N, indica si la cantidad de valores
// dentro del array coincide a: 2*N. Ejemplo: revisaArray(2, [1, 2, 3
// 4]) = True.
int revisaArray(int N, int arreglo[]){
    int contador;
    int limite = 2 * N;
    for (contador = 0; contador < limite; contador++){
        // Si encuentra un 0, entonces no cumpli�.
        printf("%d", arreglo[contador]);

        if (arreglo[contador] == 0){
            return 0;
        }
    }
    // Cuando sale del for, significa que no encontr� problemas.
    return 1;
}


int main()
{
      abrirArchivo();
//    int tamTablero = 5;
//    matriz tablero = generarTablero(tamTablero);
//    llenarTablero(tablero, tamTablero);
//    agregarFicha(tablero, 5, (5 - 1), (5 - 1));
////    mostrarTablero(tablero, tamTablero);

// int ar[2] = {1};
// revisaArray(1, ar);

    return 0;
}
