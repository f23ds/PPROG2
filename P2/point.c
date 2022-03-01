#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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
    Point * point1 = (Point *) p1;
    Point * point2 = (Point *) p2;

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
    Point * point;
    if (p == NULL)
    {
        return -1;
    }

    point = (Point *)p;

    return fprintf(pf, "[(%d, %d): %c]", point->x, point->y, point->symbol);
}

/**
* @brief Calculate the euclidean distance betweeen two points.
*
* The euclidean distance is defined as sqrt ((x1-x2)^2 + (y1-y2)^2)
* where (x1, y1) and (x2, y2) are the coordinate of both points
*
* @code
* // Example of use
* const Point *p1, *p2;
* double d;
* p1 = point_new (x1, y1, BARRIER);
* p2 = point_new (x2, y2, SPACE);
* point_euDistance (p1, p2, &d);
* printf ("%lf", d);
* // .... additional code ....
* @endcode
*
* @param p1 pointer to point
* @param p2 pointer to point
* @param distance addresss
*
* @return Returns OK or ERROR in case of invalid parameters
*/
Status point_euDistance (const Point *p1, const Point *p2, double *
distance);
/**
* @brief Compares two points using their euclidean distances to the
point (0,0).
*
*
* @param p1,p2 Points to compare.
*
* @return It returns an integer less than, equal to, or greater than
zero if
* the euclidean distance of p1 to the origin of coordinates is found
,
* respectively, to be less than, to match or be greater
* than the euclidean distance of p2. In case of error, returns
INT_MIN.
*/
int point_cmpEuDistance (const void *p1, const void *p2);


