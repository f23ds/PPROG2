/* PRÁCTICA 2 EJERCICIO 1
  Grupo: 2102
  Número de grupo:4
  Nombres: Fabio Desio Suárez
           Silvia Jiménez Real
  Fecha entrega: TODO:
*/

/* Declaración de bibliotecas públicas */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* Declaración de bibliotecas privadas */

#include "map.h"
#include "point.h"

/* Declaración de macros */
#define MIN_NUM_POINTS 0
#define MAX_NUM_POINTS 100

int main(int argc, char **argv)
{
    int n;

    if (argc != 2)
        return 1;

    n = (int)argv[1];

    if (n < MIN_NUM_POINTS|| n > MAX_NUM_POINTS) return 1;
}