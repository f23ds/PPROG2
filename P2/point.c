#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "types.h"
#include "point.h"

struct _Point
{
    int x, y;
    char symbol;

    Bool visited;
};

Point *point_new(int x, int y, char symbol)
{
    Point *point;

    point = (Point *)malloc(sizeof(Point));

    if (point == NULL)
    {
        return NULL;
    }
    else
    {
        point->x = x;
        point->y = y;
        point->symbol = symbol;
    }

    return point;
}

void point_free(Point *p)
{
    free(p);
}

int point_getCoordinateX(const Point *p)
{
    int x;

    if (p == NULL)
    {
        return INT_MAX;
    }

    x = p->x;

    return x;
}

int point_getCoordinateY(const Point *p)
{
    int y;

    if (p == NULL)
    {
        return INT_MAX;
    }

    y = p->y;

    return y;
}

char point_getSymbol(const Point *p)
{
    char symbol;

    if (p == NULL)
    {
        return ERRORCHAR;
    }

    symbol = p->symbol;

    return symbol;
}

Status point_setCoordinateX(Point *p, int x)
{
    if (p == NULL)
    {
        return ERROR;
    }

    /* x debe ser mayor o igual que cero*/
    if (x >= 0)
    {
        p->x = x;
    }
    else
    {
        return ERROR;
    }

    return OK;
}

Status point_setCoordinateY(Point *p, int y)
{
    if (p == NULL)
    {
        return ERROR;
    }

    /* y debe ser igual o mayor que cero*/
    if (y >= 0)
    {
        p->y = y;
    }
    else
    {
        return ERROR;
    }

    return OK;
}

Status point_setSymbol(Point *p, char c)
{
    if (p == NULL)
    {
        return ERROR;
    }

    if (c == 'E' || c == 'i' || c == 'o' || c == '+' || c == '.')
    {
        p->symbol = c;
    }
    else
    {
        return ERROR;
    }

    return OK;
}

Point *point_hardcpy(const Point *src)
{
    Point *trg;

    trg = (Point *)malloc(sizeof(Point));

    if (trg == NULL)
    {
        return NULL;
    }

    trg->x = src->x;
    trg->y = src->y;
    trg->symbol = src->symbol;

    return trg;
}

Bool point_equal(const void *p1, const void *p2)
{
    Point *point1 = (Point *)p1;
    Point *point2 = (Point *)p2;

    if (point1 == NULL || point2 == NULL)
    {
        return FALSE;
    }

    if (point1->x == point2->x)
    {
        if (point1->y == point2->y)
        {
            if (point1->symbol == point2->symbol)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int point_print(FILE *pf, const void *p)
{
    Point *point;
    if (p == NULL)
    {
        return -1;
    }

    point = (Point *)p;

    return fprintf(pf, "[(%d, %d): %c]", point->x, point->y, point->symbol);
}

Status point_euDistance(const Point *p1, const Point *p2, double *distance)
{
    int x1, x2, y1, y2, x, y;

    /* Checkeamos los punteros */
    if (!p1 || !p2 || !distance)
        return ERROR;

    x1 = p1->x;
    x2 = p2->x;
    y1 = p1->y;
    y2 = p2->y;

    x = x1 - x2;
    y = y1 - y2;

    /* Calculamos la distancia euclídea entre los puntos */
    *distance = sqrt(x * x + y * y);

    return OK;
}

int point_cmpEuDistance(const void *p1, const void *p2)
{
    Point *point1, *point2, *origen;
    double dist1, dist2 = 0.0;
    
    /* Comprobamos los punteros */
    if (p1 == NULL || p2 == NULL)
    {
        return INT_MIN;
    }

    /* Extraemos los puntos con los que vamos a trabajar */
    point1 = (Point *)p1;
    point2 = (Point *)p2;

    origen = point_new(0, 0, BARRIER);

    point_euDistance(point1, origen, &dist1);
    point_euDistance(point2, origen, &dist2);

    if (dist1 == dist2)
    {
        return 0;
    }
    else if (dist1 > dist2)
    {
        return 1;
    }
    else
        return -1;

    point_free(origen);

}

Bool point_getVisited(const Point *p){
    if (!p) return FALSE;
  return p->visited;
}      

Status point_setVisited(Point *p, Bool bol){
  if (!p) return ERROR;
  
    p->visited = bol;
    return OK;
}
