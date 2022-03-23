/* Bibliotecas públicas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Bibliotecas privadas */
#include "sorted_queue.h"
#include "queue.h"
#include "point.h"
#include "types.h"

/* Como la función de comparación utilizaremos la función string_cmp para que 
coincida el prototipo con lo que espera squeue_push */

int string_cmp (const void *s1, const void *s2) {
    return strcmp((char *) s1, (char *) s2);
}

int main() {
    /* Tenemos que probar la funcionalidad del TAD SortedQueue usando 
    números enteros, puntos y cadenas de texto */

    

}