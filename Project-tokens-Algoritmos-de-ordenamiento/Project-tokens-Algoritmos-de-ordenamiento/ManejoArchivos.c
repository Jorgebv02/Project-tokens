#include <stdio.h>
#include <stdlib.h>
#include "AlgoritmoBusqueda.h"

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
         // Se crea la matriz que tendra la soluci�n al tablero que se est� analizando
                matriz Solucion = generarTablero(tamanoTablero);
                // Se agrega la ficha y se muestra el tablero en pantalla.
                agregarFicha(Tablero, tamanoTablero, fila, columna);
                printf("\n********************************\n");
                printf("**       NUEVO TABLERO        **\n");
                printf("********************************\n");
                mostrarTablero(Tablero, tamanoTablero);
                printf("\n\n Tablero Solucion: \n");
                Mejor_Opcion(Tablero,Solucion,tamanoTablero);
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
    for (contador = 0; contador < 2*N ; contador++){
        // Si encuentra un 0, entonces no cumpli�.
        printf("%d", arreglo[contador]);

        if (arreglo[contador] == 0){
            return 0;
        }
    }
    // Cuando sale del for, significa que no encontr� problemas.
    return 1;
}
