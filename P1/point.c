#include <stdio.h>
#include <limits.h>
#include "point.h"
#include "types.h"

struct _Point {
    int x, y;
    char symbol;
    Bool visited; /* for DFS*/
};

Point * point_new (int x, int y, char symbol) {
    Point *p1;

    p1 = (Point *) malloc (1 * sizeof(Point));

    if (p1 == NULL) {
        return NULL;
    } else {
        p1->x = x;
        p1->y = y;
        p1->symbol = symbol;
    }
    
    return p1;
}


void point_free (Point *p) {
    free(p);
}

int point_getCoordinateX (const Point *p) {
    
    if (p == NULL) {
        return INT_MAX;
    }

    return p->x;
}

int point_getCoordinateY (const Point *p) {
    
    if (p == NULL) {
        return INT_MAX;
    }

    return p->y;
}

char point_getSymbol (const Point *p) {
    
    if (p == NULL) {
        return ERRORCHAR;
    }

    return p->symbol;
}


Status point_setCoordinateX (Point *p, int x) {

    if (p == NULL) {
        return ERROR;
    }
    
    if (x>=0) {
        p->x = x;
    }else{
        return ERROR;
    }

    return OK;
}


Status point_setCoordinateY (Point *p, int y) {

    if (p == NULL) {
        return ERROR;
    }
    
    if (y>=0) {
        p->y = y;
    } else {
        return ERROR;
    }

    return OK;
}

Status  point_setSymbol (Point *p, char c) {
    
    if (p == NULL) {
        return ERROR;
    }
    
    if (c == ERRORCHAR || c == INPUT || c == OUTPUT || c == BARRIER || c == SPACE) {
        p->symbol = c;
    } else {
        return ERROR;
    }

    return OK;
}

Point *point_hardcpy (const Point *src) {
    Point *trg;
    int x1, y1;
    char c;

    if (src==NULL) {
        return NULL; 
    }

    x1 = point_getCoordinateX(src);
    y1 = point_getCoordinateY(src);
    c = point_getSymbol(src);

    trg = point_new(x1, y1, c);
    
    if (trg == NULL) {
        return NULL;
    }
    
    return trg;
}

Bool point_equal (const void *p1, const void *p2) {

    if (p1==NULL || p2==NULL) {
        return FALSE;
    }

    if (point_getCoordinateX(p1) == point_getCoordinateX(p2)) {
        if (point_getCoordinateY(p1) == point_getCoordinateY(p2)) {
            if (point_getSymbol(p1)==point_getSymbol(p2)) {
                return TRUE;
            }else{
                return FALSE;
            }
        } else{
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

int point_print (FILE *pf, const void *p) {
    int x, y;
    char s;
    
    if (pf == NULL || p == NULL) {
        return -1;
    }

    x = point_getCoordinateX(p);
    y = point_getCoordinateY(p);
    s = point_getSymbol(p);
    
    return fprintf(pf, "[(%d, %d): %c]", x, y, s);
}
