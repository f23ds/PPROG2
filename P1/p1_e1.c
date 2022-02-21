/* PRACTICA 1 EJERCICIO 1
  Grupo: 1102
  Número de grupo:4
  Nombres: Fabio Desio Suárez
           Silvia Jiménez Real 
  Fecha entrega: 14/02/2022
  */
  
  
/* Declaración bibliotecas públicas*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declaración bibliotecas privadas*/

#include "point.h"

/* Declación constantes*/

#define TAM 4

int main()
{
    Bool cmp;
    /* Declarar un array de 4 punteros a punto de nombre p*/
    
    Point *p[TAM];
    int i;
    
    /* Inicializar los elementos del array p[0] y p[1]*/
    
   
     p[0] = point_new(0, 0, BARRIER);
     p[1] = point_new(0, 1, BARRIER);
    
   


    /*Imprimir ambos puntos en la salida estándar*/
    
    point_print(stdout, p[0]);
    point_print(stdout, p[1]);
    

    /* Salto de línea*/
    
    printf("\n");

    /* Comparar ambos ambos puntos e imprimir el resultado*/
    
    
    cmp = point_equal(p[0], p[1]);

  
    if (cmp == TRUE)
    {
        printf("Equal points p[0] and p[1]? Yes\n");
    }
    else
    {
        printf("Equal points p[0] and p[1]? No\n");
    }

    /* Asignar al tecer elemento del array p una copia del primer punto*/
    
    p[2] = point_hardcpy(p[0]);
   
    /* Imprimir el tercer punto en la salida estándar*/
    
    printf("Creating p[2]: ");
    point_print(stdout, p[2]);
    printf("\n");

    /* Comparamos el primer y el tercer punto e imprimimos el resultado*/
    
    cmp = point_equal(p[0], p[2]);

   
    if (cmp == TRUE)
    {
        printf("Equal points p[0] and p[2]? Yes\n");
    }
    else
    {
        printf("Equal points p[0] and p[2]? No\n");
    }

    /* Asignamos el valor SPACE al tercer puntero*/
    
    if(point_setSymbol(p[2], SPACE)==OK){
    
    printf("Modifying p[2]: ");
    point_print(stdout, p[2]);
    printf("\n");
    
    }else
        return 1;

    /* Comparamos otra vez el primer y el tercer puntero e imprimimos el resultado*/
    
    cmp = point_equal(p[0], p[2]);
    
    
    if (cmp == TRUE)
    {
        printf("Equal points p[0] and p[2]? Yes\n");
    }
    else
    {
        printf("Equal points p[0] and p[2]? No\n");
    }

    /* Asignar a p[3] el primer punto*/
    
    printf("Assign p[3] = p[0]\n");
    p[3] = p[0];
    

    

    /* Modificar el campo symbol de p[3] y asignamos el valor OUTPUT*/
    
    if(point_setSymbol(p[3], OUTPUT)==OK){
        
        printf("Modifying p[3]: ");
        point_print(stdout, p[3]);
        printf("\n");

    }else 
        return 1;
    
    
    /* Imprimimos y liberamos los cuatro puntos*/
    
    for(i=0; i<4; i++){
    
    	point_print(stdout, p[i]);
    }
    
    for (i=0; i<3; i++) {
        point_free(p[i]);
    }
    
    return 0;
   }
