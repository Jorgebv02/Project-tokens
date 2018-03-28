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

    abrir:
        printf("Ingrese el nombre del archivo que desea abrir: \n>> ");
        scanf("%s", &nombreArchivo);

        // Se abre el archivo para lectura.
        FILE* archivo = fopen(nombreArchivo, "r");

    // Si archivo es NULL entonces hubo un error al tratar de abrir el archivo.
    if(archivo == NULL){
        printf("\nHubo un error con la apertura del archivo.\nPor favor, verifique el nombre y vuelva a intentarlo.\n\n");
        goto abrir;
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

            // Si la dimensi�n que viene en el archivo est� entre 1 y 15
            if(revisaDimension(tamanoTablero) == 1){
                // Se crea el tablero.
                Tablero = generarTablero(tamanoTablero);
                llenarTablero(Tablero, tamanoTablero);
                tableroCreado = 1;
                contadorLinea++;
            }
            else if(tamanoTablero == 0){
                printf("\n********************************\n");
                printf("**        FIN ARCHIVO         **\n");
                printf("********************************\n");
                break;
            }
            else{
                printf("Hay un error en la dimension del tablero en la linea %i del archivo.\n", contadorLinea+1);
                printf("Por favor, escriba una dimension entre 1 y 15 y vuelva a intentarlo.\n\n");
                fclose(archivo);
                goto abrir;
            }
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

                // Verifica que la cantidad de posiciones que el archivo posee para
                // un tablero de dimensi�n: N, corresponda a 2 * N.
                if((tamanoTablero * 2) != (fila_columna + 1)){
                    printf("\nHay un error en la linea %i del archivo!\n", contadorLinea);
                    printf("Por favor, verifique esa linea y vuelva a intentarlo.\n\n");
                    goto abrir;
                    break;
                }

                // Se crea la matriz que tendra la soluci�n al tablero que se est� analizando
                matriz Solucion = generarTablero(tamanoTablero);
                // Se agrega la ficha y se muestra el tablero en pantalla.
                agregarFicha(Tablero, tamanoTablero, fila, columna);
                printf("\n********************************\n");
                printf("**       TABLERO CREADO       **\n");
                printf("********************************\n");
                mostrarTablero(Tablero, tamanoTablero);
                printf("\n********************************\n");
                printf("**          SOLUCION          **\n");
                printf("********************************\n");
                Mejor_Opcion(Tablero,Solucion,tamanoTablero);
                // Se reinician los contadores.
                contador = 0;
                fila_columna = 0;
            }
        }
    }

    fclose(archivo); // Se cierra el archivo.
}

// M�todo que recibe un valor entero, si est� entre 1 a 15 retorna True,
// si recibe un 0 entonces termina la ejecuci�n del programa y si no retorna
// False.
int revisaDimension(int dimension){
    if ((dimension >= 1) && (dimension <= 15)){
        return 1;
    }
    else{
        return 0;
    }
}


