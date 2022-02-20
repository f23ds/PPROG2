#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"
#include "types.h"

#define MAX_NCOLS 64  /* Maximum map cols*/
#define MAX_NROWS 64  /* Maximum map rows*/
#define MAX_BUFFER 64 /* Maximum file line size*/

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

Map *map_new(unsigned int nrows, unsigned int ncols)
{
    Map *map;

    if (nrows > MAX_NROWS || ncols > MAX_NCOLS)
    {
        return NULL;
    }

    /* Reservamos memoria para el mapa*/
    map = (Map *)calloc(1, sizeof(Map));

    map->nrows = nrows;
    map->ncols = ncols;
    
    for(i=0, ; i<nrows; i++){
       for( j=0; j<ncols; j++){
           map->array[j][i] = point_new(j, i, BARRIER);
       }
    }
    
    map->input = point_new(0, 0, INPUT);
    map->output = point_new(0, 0, OUTPUT);

    return map;
}


   void map_free(Map *mp){
 
    int i, j;
    
    for(i=0, ; i<nrows; i++){
       for( j=0; j<ncols; j++){
            point_free(mp->array[i][j]);
       }
    }
    point_free(output);
    point_free(input);
    free(mp);
}

Point *map_insertPoint(Map *mp, Point *p)
{
    if (mp == NULL || p == NULL)
    {
        Map *map_readFromFile(FILE * pf);

        return NULL;
    }

    /* Insertamos el punto en el mapa a partir de sus coordenadas*/
    mp->array[p->y][p->x] = p;

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
        return mp->array[p->y + 1][p->x];

    case LEFT:
        return mp->array[p->y][p->x - 1];

    case DOWN:
        return mp->array[p->y - 1][p->x];

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

    mp->input = p

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

Map *map_readFromFIle(FILE *pf)
{
    Map *map;
    if (pf == NULL)
    {
        return NULL;
    }

   
    return map;
}

Bool map_equal(const void *_mp1, const void *_mp2)
{
    int nrows1, nrows2, ncols1, ncols2, i, j;
    Map * mp1 = (Map *) _mp1;
    Map * mp2 = (Map *) _mp2;

    if (mp1 == NULL || mp2 == NULL)
    {
        return FALSE;
    }

    nrows1 = mp1.nrows;
    nrows2 = mp2.nrows;
    ncols1 = mp1.ncols;
    ncols2 = mp2.ncols;

    /* Si el número de filas y columnas no es idéntico, entonces los mapas no son iguales*/
    
    if (nrows1 != nrows2 || ncols1 != ncols2)
    {
        return FALSE;
    }

    if (point_equal(mp1->input, mp2->input)==FALSE || point_equal(mp1->output, mp2->output)==FALSE)
    {
        return FALSE;
    }

    
    for (i = 0; i < nrows1; i++)
    {
        for (j = 0; j < ncols1; j++)
        {
            if (point_equal(mp1->array[i][j], mp2->array[i][j])==FALSE)
            {
            
                  return FALSE;
            }
        }
    }
    return TRUE;
}

int map_print(FILE *pf, Map *mp) {
   
    int i, j;   
    
    
    if (pf == NULL || mp == NULL) {
        return -1;
    }
     
   
    for(i=0; i < ncols; i++)
    {
       for(j=0; j < nrows; j++)
       {
          
          return point_print(stdout, mp->array[i][j]);
}
