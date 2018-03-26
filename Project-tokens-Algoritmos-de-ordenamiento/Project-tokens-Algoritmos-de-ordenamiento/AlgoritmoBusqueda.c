#include <stdio.h>
#include <stdlib.h>
#include "Tablero.h"
#include <math.h>
//********************************************************************************************
// Método: mejor_Movimiento
//
// Dada  una matriz (tablero) evalua cuales son las posisiciones de la ficha
// que mejor se adapta a las posiciones que se requieren.
// el parámetro ind se utiliza para indicar que ordenamiento se está realizando,
//                   ind = 0 ==> Caso Horizontal
//                   ind = 1 ==> Caso Vertical
//                   ind = 2 ==> Caso Diagonal Izquierda
//                   ind = 3 ==> Caso Diagonal Derecha
// posC y posF, son las posiciones en las que se desea colocar la ficha
// posi y posj, son las posiciones donde se encuentra la ficha que será colocada
// t es el tamaño de la matriz
//********************************************************************************************

void mejor_movimiento(matriz P,int *posi,int *posj,int t, int posC,int posF,int ind){
    int tempi,tempj,temps,i,j;     // tempi :: almacena la posición i de la posible ficha que se va a colocar
                               // tempj :: almacena la posición j de la posible ficha que se va a colocar
                               // temps :: almacena la cantidad de movimientos que requiere una determinada
                               //          ficha para moverse a las posiciones requeridas
    int sum = 99999;           // almacena el número mínimo de movimientos que requiere una ficha
    temps = 0;
    int xi,xj;                // Se utilizan para el caso de la diagonal derecha
    xi = 0; xj = t-1;         // se inicia en la posicion (0,t-1), que es la primera posicion de derecha a izquierda

    //Se recorre el tablero para buscar las fichas que esten disponibles
    for(i = 0; i < t; i++){
        for(j = 0; j <t; j++){

            if(((i != posF && ind == 0) // En el caso Horizontal, se verifica que la ficha no sea una que ya esté acomodada en la fila.
                || (j != posC && ind == 1) || // En el caso Vertical, se verifica que la ficha no sea una que ya esté acomodada en la columna.
            ((i != j && ind == 2) || ((i != xi || j !=xj) && ind==3))) // En el caso de las esDiagonal, se verifica que la ficha no sea una que ya esté
                                                                       //acomodada en ninguna de las posiciones de la diagonal(ya sea si se trabaja en diagonal izquierda o derecha).
               && P[i][j] == 1){
                temps += fabs(i-posF);     //Se calcula la distancia de la ficha con las posiciones requeridas.
                temps += fabs(j-posC);
                if(temps < sum){          // Si esa distancia es menor que él minimo, entonces se actualizan los datos
                    tempi = i;            // Posicion i de la posible ficha a colocar
                    tempj = j;            // Posicion j de la posible ficha a colocar
                    sum = temps;
                }
                temps = 0;         //Se reinicia la variable que guarda la distancia de la ficha con la posicion requerida.
            }
            if(i == xi && j ==xj && ind==3){   //En el caso de la diagonal derecha, si las posiciones analizadas son parte de la
                                            // diagonal se actualizan para el correcto análisis del caso.
                xi++;
                xj--;
            }
        }
        //Al terminar de analizar una columna, verifica los resultados para guardar las posiciones con menor
        //cantidad de movimientos
        if(ind == 1){  //Caso vertical
           if(tempi == posF){        // Prioridad si la ficha se encuentre en la misma fila
                (*posi) = tempi;    //Actualiza las posiciones de la ficha que se va colocar
                (*posj) = tempj;
           }
           else if(tempi < posF){   // En caso de que no este en la misma fila, toma el que se se encuentre más arriba en
               (*posi) = tempi;     // en el tablero
               (*posj) = tempj;     //Actualiza las posiciones de la ficha que se va colocar
           }
           else{
               (*posi) = tempi;
               (*posj) = tempj;
           }
        }

        else if(ind == 0){   // Caso Horizontal
            if(tempj <= (*posj)){      // Si la ficha se encuentra en la misma columna en alguna fila anterior con respecto
                 (*posi) = tempi;      // a la que ya está almacenada como mejor posicion( es decir,busca
                 (*posj) = tempj;      // la ficha que se encuentre más a la izquierda).
            }
        }
       else{                 //Caso Diagonal
            if(tempi == posF || tempj == posC){      // Prioridad si se encuentra en la misma fila o la misma columna
                  (*posi) = tempi;
                  (*posj) = tempj;
            }
            else if(tempj < (*posj) || tempi < (*posi)){   // Si la posicion i o la posicion j de la ficha que se va a guardar
                  (*posi) = tempi;                         // es menor que las posiciones de la ficha que ya se tiene almacenada
                  (*posj) = tempj;                         // como mejor.
            }
       }
    }
}

//********************************************************************************************
// Método: mejor_Caso_Vertical
//
// Dada  una matriz (tablero) devuelve la menor de cantidad de movimientos
// para colocar las fichas en alineación vertical.
// La matriz resultante se almacena en Sol(variable que ingresa inicialmente como parámetro).
//********************************************************************************************

int mejor_Caso_Vertical(matriz P, int t,matriz Sol,int mov){
    int columna = 0;                    // Inicializa la columna
    matriz mtemp = generarTablero(t);   // Matriz temporal que se utilizara para cada iteración nueva(cada vez que
                                        // se analiza una columna nueva)
    do{
       int fila=0;
       // Al iniciar el analisis de cada columna la matriz temporal va a tener las fichas en las mismas posiciones
       // que el tablero inicial.
       copiar_matriz(P, mtemp,t);

       int mov_temp = 0;    // Guarda los movimientos requeridos en la columna que se está analizando
       while(fila < t){        //Se mueve por las filas de la columna que se está analizando
            if(P[fila][columna] == 1){      // Si alguna posicion de esa columna ya tiene ficha
                fila ++;                   // incrementa la fila, para analizar la siguiente posicion.
             }
            else{
                int val = AnalisisCasos_Auxiliar(mtemp,t,fila,columna,&mov_temp,1, mov); // Retorna 1 si los movimientos
                                                                                         // que lleva acumulados la columna son menores que el mínimo de movimientos en general.
                if(val == 0){     //Si los movimientos de la colummna son mayores que el mínimo de movimientos
                    columna++;break;      // entonces pasa a la siguiente columna.
                }
                fila++;         // Si los movimientos son menores que el minimo, entonces avanza a la siguiente posicion de la columna.
            }
       }
       // Cuando termina de analizar una columna verifica si el numero de movimientos realizados
       // para acomodar esa columna es menor que el mínimo.
       if((mov_temp <= mov)){     // Si es menor, entonces actualiza la matriz solucion(parámetro)
                                 // con la matriz acomodada en la columna que acumula menor cantidad de movimientos.
               copiar_matriz(mtemp, Sol,t);
               mov = mov_temp;        // Actualiza el valor mínimo de movimientos, con el valor de movimientos de esa columna
               columna++;             //avanza a la siguiente columna.
       }
       // Si no es menor, entonces pasa a la siguiente columna( el incremento se da en la linea 87)
    }while(columna < t);
    return mov;    //Retorna el numero mínimo de movimientos
}


//********************************************************************************************
// Método: mejor_Caso_Horizontal
//
// Dada  una matriz (tablero) devuelve la menor de cantidad de movimientos
// para colocar las fichas en alineación horizontal.
// La matriz resultante se almacena en Sol(variable que ingresa inicialmente como parámetro).
//********************************************************************************************

int mejor_Caso_Horizontal(matriz P, int t,matriz Sol,int mov){
    int fila = 0;                    // Inicializa la fila
    matriz mtemp = generarTablero(t); // Matriz temporal que se utilizara para cada iteración nueva(cada vez que
    do{                               // se analiza una fila nueva)
        int columna = 0;

       // Al iniciar el analisis de cada fila la matriz temporal va a tener las fichas en las mismas posiciones
       // que el tablero inicial.
        copiar_matriz(P, mtemp,t);
        int mov_temp=0;   // Guarda los movimientos requeridos en la fila que se está analizando

        while(columna < t){           //Se mueve por las columnas de la fila que se está analizando
            if(P[fila][columna] == 1){  // Si alguna posicion de esa columna ya tiene ficha
                columna++;       // incrementa la columna, para analizar la siguiente posicion.
            }
            else{
                int val = AnalisisCasos_Auxiliar(mtemp,t,fila,columna,&mov_temp,0, mov); // Retorna 1 si los movimientos
                                                                                         // que lleva acumulados la fila son menores que el mínimo de movimientos en general.
                if(val == 0){   //Si los movimientos de la fila son mayores que el mínimo de movimientos
                    fila++;break; // entonces pasa a la siguiente fila.
                }
                columna++; // Si los movimientos son menores que el minimo, entonces avanza a la siguiente posicion de la fila
            }
        }
       // Cuando termina de analizar una fila verifica si el numero de movimientos realizados
       // para acomodar esa fila es menor que el mínimo.
       if((mov_temp <= mov)){     // Si es menor, entonces actualiza la matriz solucion(parámetro)
                                 // con la matriz acomodada en la fila que acumula menor cantidad de movimientos.
               copiar_matriz(mtemp, Sol,t);
               mov = mov_temp;        // Actualiza el valor mínimo de movimientos, con el valor de movimientos de esa fila
               fila++;             //avanza a la siguiente fila
       }
       // Si no es menor, entonces pasa a la siguiente columna( el incremento se da en la linea 133)
    }while(fila < t);
    return mov; //Retorna el numero mínimo de movimientos
}


//********************************************************************************************
// Método: AnalisisCasos_Auxiliar
//
// Se utiliza como función auxiliar en los método mejor_caso_Horizontal y mejor_caso_Vertical
// Retorna  1 si al sumar la posicion de una nueva ficha al acumulado del analisis que se está
// realizando(sea vertical u horizontal) es menor que la cantidad mínima de movimientos( parámetro mov)
//*****************************************************************************************************
int AnalisisCasos_Auxiliar(matriz mtemp, int t,int fila,int columna,int *mov_temp,int ind, int mov){
    int posj = t;      //Posicion i de la ficha que se va a colocar
    int posi =t;       // Posicion j de la ficha que se va a colocar
    mejor_movimiento(mtemp,&posi,&posj,t,columna,fila,ind);   // Actualiza las posiciones de la mejor oppcion de ficha a colocar
    (*mov_temp) += fabs(posi-fila);          // Se actualiza la variable que acumula los movimientos de la columna o fila que se
    (*mov_temp) += fabs(posj-columna);      // esta analizando

    if((*mov_temp) > mov){       //Si ese acumulado es mayor que el mínimo de movimientos, retorna 0
            return 0;
    }
    // sino, entonces actualiza el tablero que se está analizando y retorna1
    mtemp[posi][posj] = 0;
    mtemp[fila][columna] = 1;
    return 1;
}

//********************************************************************************************
// Método:  mejor_caso_diagonal
// Dada  una matriz (tablero) devuelve la menor de cantidad de movimientos
// para colocar las fichas en alineación diagonal.
// La matriz resultante se almacena en Sol(variable que ingresa inicialmente como parámetro).
//*****************************************************************************************************
int mejor_caso_diagonal(matriz P, int t,matriz Sol){
    int temp,temp1,posi,posj,xi,xj,i,j;
    temp = 0;        // Guarda los movimientos requeridos en la diagonal izquierda.
    temp1 = 0;       // Guarda los movimientos requeridos en la diagonal derecha.
    xi = 0;
    xj = t-1;      // Se utilizan para el caso de la diagonal derecha
    matriz mtemp = generarTablero(t);       // Matriz temporal para el analisis de la diagonal izquierda
    matriz mtemp2 = generarTablero(t);      // Matriz temporal para el análisis de la diagonal derecha
    copiar_matriz(P, mtemp,t);              //Inicialmente ambas matrices son iguales a la matriz principal.
    copiar_matriz(P, mtemp2,t);

    //Se recorre el tablero
    for(i = 0; i < t; i++){
        for(j = 0; j < t; j++){
            posi = t;        //Posicion temporal i de la ficha que se va a colocar
            posj = t;        //Posicion temporal j de la ficha que se va a colocar
            if(i == j && P[i][j] != 1){   //CASO DIAGONAL IZQUIERDA
                mejor_movimiento(mtemp,&posi,&posj,t,j,i,2); //buscar mejor opcion para esa posicion i,j

                temp += fabs(posi-i);  // Actualiza la cantidad de movimientos
                temp += fabs(posj-j);

                mtemp[posi][posj] = 0;    //Actualiza el tablero
                mtemp[i][j] = 1;
            }
            if(i == xi && j == xj){    //CASO DIAGONAL DERECHA
                if(mtemp2[i][j] != 1){
                 mejor_movimiento(mtemp,&posi,&posj,t,j,i,3); //buscar mejor opcion para esa posicion xi,xj

                temp1 += fabs(posi-i);     //Actualiza la cantidad de movimientos
                temp1 += fabs(posj-j);

                mtemp2[posi][posj] = 0;     // Actualiza el tablero
                mtemp2[i][j] = 1;
                }
                xi++;        //Actualiza las posiciones de la diagonal derecha que se requieren completar
                xj--;
            }
        }
    }
    if(temp < temp1){  // Si el número de movimiento de la diagonal izquierda es menor entonces
        copiar_matriz(mtemp, Sol,t); // Actualizo la matriz Solucion con la matriz temporal que almacena la diagonal izquierda
        return temp; // Se retorna el número de movimientos requeridos
    }
    else{
        copiar_matriz(mtemp2, Sol,t);// Actualizo la matriz Solucion con la matriz temporal que almacena la diagonal izquierda
        return temp1; // Se retorna el número de movimientos requeridos
    }
}


//********************************************************************************************
// Método:  Mejor_Opcion
// Dada  una matriz (tablero) muestra en pantalla la matriz solucion, con la alineacion
// que requirió menor cantidad de movimientos
//*****************************************************************************************************
void Mejor_Opcion(matriz tablero, matriz Solucion, int t){
    matriz s = generarTablero(t); // Matriz Solucion temporal
    int mov = 999999; int movt = 999999;   // Mov: cantidad menor de movimientos  ||||||||  movt: cantidad menor de movimientos temporal
    int count = 0;
    do{
        switch(count){
         case 0: movt = mejor_Caso_Vertical(tablero,t,s,mov); break;   // Guarda la menor cantidad e movimientos
                                                                       //requeridos para acomodar el tablero de manera vertical, y guarda el posible tablero en s.
         case 1: movt = mejor_Caso_Horizontal(tablero,t,s,mov); break;// Guarda la menor cantidad e movimientos
                                                                       //requeridos para acomodar el tablero de manera horizontal, y guarda el posible tablero en s.
         case 2: movt = mejor_caso_diagonal(tablero,t,s); break;// Guarda la menor cantidad e movimientos
                                                                       //requeridos para acomodar el tablero de manera diagonal, y guarda el posible tablero en s.
        }
        if(movt < mov){  //Si la cantidad de movimientos temporal(apartir del último analisis registrado) es menor
                         // que la cantidad menor de movimientos general entonces
            mov = movt; // Se actualiza la cantidad menor de movimientos
            copiar_matriz(s, Solucion,t); // Se actualiza la matriz Solucion
        }
        count++;
    }while(count < 3);

    printf("Solucion: \n");
    mostrarTablero(Solucion,t);
    printf("\n Cantidad de movimientos: %d \n\n", mov);
}
