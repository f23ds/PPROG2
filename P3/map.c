#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"
#include "types.h"
#include "queue.h"
#include "sorted_queue.h"

#define MAX_NCOLS 64           /* Maximum map cols*/
#define MAX_NROWS 64           /* Maximum map rows*/
#define MAX_BUFFER 64          /* Maximum file line size*/
#define MAX_STACK_SIZE 64 * 64 /* Maximum stack size */
#define NUM_NEIGHBORS 4        /* Ignoramos la posición STAY */

struct _Map
{
    unsigned int nrows, ncols;
    Point *array[MAX_NROWS][MAX_NCOLS]; /* array with the Map points*/
    Point *input, *output;              /* points input/output*/
};

struct _Point
{
    int x, y;
    char symbol;
    Bool visited; /* for DFS*/
};

struct _Stack
{
    void *data[MAX_STACK_SIZE];
    int top;
};

Map *map_new(unsigned int nrows, unsigned int ncols)
{
    Map *map;
    int i, j;

    /* Comprobamos que los valores de las filas y las columnas es correcto */
    if (nrows > MAX_NROWS || ncols > MAX_NCOLS)
    {
        return NULL;
    }

    /* Reservamos memoria para el mapa*/
    map = (Map *)calloc(1, sizeof(Map));

    map->nrows = nrows;
    map->ncols = ncols;

    /* Inicializamos el mapa con un símbolo cualquiera */
    for (i = 0; i < nrows; i++)
    {
        for (j = 0; j < ncols; j++)
        {
            map->array[i][j] = point_new(j, i, BARRIER);
        }
    }

    /* Inicializamos los valores del input y del output */
    map->input = point_new(0, 0, INPUT);
    map->output = point_new(0, 1, OUTPUT);

    return map;
}

void map_free(Map *mp)
{
    int i, j;
    unsigned int nrows, ncols;

    nrows = mp->nrows;
    ncols = mp->ncols;

    /* Liberamos cada punto del mapa */
    for (i = 0; i < nrows; i++)
    {
        for (j = 0; j < ncols; j++)
        {
            point_free(mp->array[i][j]);
        }
    }

    point_free(mp->output);
    point_free(mp->input);
    free(mp);
}

Point *map_insertPoint(Map *mp, Point *p)
{
    if (mp == NULL || p == NULL)
    {
        return NULL;
    }

    /* Insertamos el punto en el mapa a partir de sus coordenadas*/
    mp->array[p->y][p->x] = p;

    /* Devolvemos el punto */
    return mp->array[p->y][p->x];
}

int map_getNcols(const Map *mp)
{
    if (mp == NULL)
    {
        return -1;
    }

    return mp->ncols;
}

int map_getNrows(const Map *mp)
{
    if (mp == NULL)
    {
        return -1;
    }

    return mp->nrows;
}

Point *map_getInput(const Map *mp)
{
    if (mp == NULL)
    {
        return NULL;
    }

    return mp->input;
}

Point *map_getOutput(const Map *mp)
{
    if (mp == NULL)
    {
        return NULL;
    }

    return mp->output;
}

Point *map_getPoint(const Map *mp, const Point *p)
{
    if (mp == NULL || p == NULL)
    {
        return NULL;
    }

    /* Return el punto con las mismas coordenadas que p*/
    return mp->array[p->y][p->x];
}

Point *map_getNeighbor(const Map *mp, const Point *p, Position pos)
{
    if (mp == NULL || p == NULL)
    {
        return NULL;
    }

    /* Hacemos return del vecino según la posición*/
    switch (pos)
    {
    case RIGHT:
        return mp->array[p->y][p->x + 1];

    case UP:
        return mp->array[p->y - 1][p->x];

    case LEFT:
        return mp->array[p->y][p->x - 1];

    case DOWN:
        return mp->array[p->y + 1][p->x];

    case STAY:
        return mp->array[p->y][p->x];

    default:
        return NULL;
        break;
    }
}

Status map_setInput(Map *mp, Point *p)
{
    if (mp == NULL || p == NULL)
    {
        return ERROR;
    }

    mp->input = p;

    return OK;
}

Status map_setOutput(Map *mp, Point *p)
{
    if (mp == NULL || p == NULL)
    {
        return ERROR;
    }

    mp->output = p;

    return OK;
}

Map *map_readFromFile(FILE *pf)
{
    Map *map;
    unsigned int nrows, ncols;
    char symbol;
    int i, j;

    if (pf == NULL)
    {
        return NULL;
    }

    /*Reserva y crea mapa*/
    map = (Map *)calloc(1, sizeof(Map));

    fscanf(pf, "%u %u\n", &nrows, &ncols);

    map->nrows = nrows;
    map->ncols = ncols;

    for (i = 0; i < nrows; i++)
    {
        /* Consideramos el salto de línea para utilizar correctamente la función fscanf */
        if (i > 0)
        {
            fscanf(pf, "\n");
        }

        for (j = 0; j < ncols; j++)
        {

            fscanf(pf, "%c", &symbol);

            map->array[i][j] = point_new(j, i, symbol);

            /* Especificamos los valores del input y del output */
            if (symbol == INPUT)
            {
                map->input = point_new(j, i, INPUT);
            }
            else if (symbol == OUTPUT)
            {
                map->output = point_new(j, i, OUTPUT);
            }
        }
    }

    return map;
}

Bool map_equal(const void *_mp1, const void *_mp2)
{
    int nrows1, nrows2, ncols1, ncols2, i, j;

    /* Casteamos el tipo void * para transformarlo en un tipo Map * */
    Map *mp1 = (Map *)_mp1;
    Map *mp2 = (Map *)_mp2;

    if (mp1 == NULL || mp2 == NULL)
    {
        return FALSE;
    }

    ncols1 = mp1->ncols;
    nrows1 = mp1->nrows;
    ncols2 = mp2->ncols;
    nrows2 = mp2->nrows;

    /* Si el número de filas y columnas no es idéntico, entonces los mapas no son iguales*/
    if (nrows1 != nrows2 || ncols1 != ncols2)
    {
        return FALSE;
    }

    if (point_equal(mp1->input, mp2->input) == FALSE || point_equal(mp1->output, mp2->output) == FALSE)
    {
        return FALSE;
    }

    /* Si hay un solo punto que sea distinto return FALSE */
    for (i = 0; i < nrows1; i++)
    {
        for (j = 0; j < ncols1; j++)
        {
            if (point_equal(mp1->array[i][j], mp2->array[i][j]) == FALSE)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int map_print(FILE *pf, Map *mp)
{
    int i, j, c;

    if (pf == NULL || mp == NULL)
    {
        return -1;
    }

    printf("%u, %u\n", mp->nrows, mp->ncols);

    for (i = 0; i < mp->nrows; i++)
    {
        for (j = 0; j < mp->ncols; j++)
        {
            /* Utilizamos += porque el return de la función si todo se ha ejecutado correctamente es el número de caracteres impresos */
            c += point_print(stdout, mp->array[i][j]);
        }
    }
    return c;
}

/**
* @brief: Makes a search from the origin point to the output point
* of a map using the breadth-first search algorithm and the ADT
Queue
*
* The function prints each visited point while traversing the map
*   1. Inicializar una cola auxiliar.
    2. Insertar el punto de inicio en la cola auxiliar.
    3. Mientras la cola no este vacia:
    3.1. Extraer un punto de la cola y marcarlo como visitado.
    3.2. Si el punto extraido es el punto de llegada, salir del bucle.
    3.3. Si el punto extraido no es el punto de llegada y no ha sido
    visitado, explorar sus vecinos:
    3.3.1. Si el vecino explorado no ha sido visitado, insertarlo en
    la cola.
    4. Liberar recursos
* @param pf, File descriptor
* @param mp, Pointer to map
*
* @return The function returns the output map point o NULL otherwise
**/
Point *map_bfs(FILE *pf, Map *mp)
{
    Queue *q = NULL;
    Point *input = NULL, *output = NULL, *ele = NULL, *aux=NULL;
    Status st = OK;
    Position pos;

    if (!pf || !mp)
        return NULL;

    /* 1. Inicializamos una cola auxiliar */
    q = queue_new();

    if (!q)
        return NULL;

    /* insertamos el punto de inicio en la cola auxiliar */
    input = map_getInput(mp);
    st = queue_push(q, input); 
    
    if (!st){
        queue_free(q);
        return NULL;
    }

    /* Hallamos el output */
    output = map_getOutput(mp);

    /* Mientras la cola no esté vacía */
    while (queue_isEmpty(q) == FALSE)
    {
        /* Extraer el punto de la cola y marcarlo como visitado */
        ele = (Point *)queue_pop(q);
        
        /* Si el punto extraído es el punto de llegada, salir del bucle */
        if (point_cmp(ele, output) == 1) {
         break;   
        }

        /* Si el punto extraido no es el punto de llegada y no ha sido
    visitado, explorar sus vecinos */
        
        for (pos = 0; pos < NUM_VECINOS; pos++)
  {

    aux = map_getNeighbor(map, ele, pos);
    
    if(point_getVisited(aux)==FALSE){
    point_setVisited(aux, TRUE);
    sta=queue_push(q, aux);
    point_print(stdout, aux);
        
     if (!st){
        queue_free(q);
        return NULL;
    }
        
    if (point_cmp(aux, output) == 1) {
        queue_free(q);
        return output;   
     }
    }
    
    
  }    
        
    }
}

int point_cmp(const Point *p1, const Point *p2)
{
    int x1, x2, y1, y2;

    if (!p1 || !p2)
        return -1;

    x1 = point_getCoordinateX(p1);
    x2 = point_getCoordinateX(p2);
    y1 = point_getCoordinateY(p1);
    y2 = point_getCoordinateY(p2);

    if (x1 == x2 && y1 == y2)
        return 1;

    return 0;
}
