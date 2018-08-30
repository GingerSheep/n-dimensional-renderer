#include "simplex.h"

#include <stdlib.h>
#include <string.h>

Simplex simplex_create(unsigned int dimensions, PointArray *points)
{
    Simplex simplex;

    simplex.points = points;
    simplex.indexes = calloc((dimensions + 1), sizeof(unsigned int));
    simplex.dimensions = dimensions;

    return simplex;
}

void simplex_set_indexes(Simplex *simplex, unsigned int *indexes)
{
    memcpy(simplex->indexes, indexes, sizeof(unsigned int) * (simplex->dimensions + 1));
}

void simplex_set_index(Simplex *simplex, unsigned int index, unsigned int pointIndex)
{
    *(simplex->indexes + index) = pointIndex;
}

void simplex_iterate(Simplex *simplex, void (*iterateFunction)(Point *))
{
    Point *point = malloc(sizeof(Point));

    point->dimensions = simplex->points->dimensions;

    for(unsigned int p = 0; p < simplex->dimensions + 1; p++)
    {
        point->data = simplex->points->data + simplex->indexes[p];

        iterateFunction(point);
    }

    free(point);
}

void simplex_destroy(Simplex *simplex)
{
    free(simplex->indexes);
    simplex->dimensions = 0;
}
