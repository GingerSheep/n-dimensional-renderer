#include "simplexarray.h"

#include <stdlib.h>
#include <string.h>

SimplexArray simplexArray_create(unsigned int dimensions, unsigned int simplexCount, PointArray *points)
{
    SimplexArray simplexArray;

    simplexArray.points = points;
    simplexArray.indexes = calloc((dimensions + 1) * simplexCount, sizeof(unsigned int));
    simplexArray.dimensions = dimensions;
    simplexArray.simplexCount = simplexCount;

    return simplexArray;
}

void simplexArray_set_indexes(SimplexArray *simplexArray, unsigned int *indexes)
{
    memcpy(simplexArray->indexes, indexes, sizeof(unsigned int) * (simplexArray->dimensions + 1) * simplexArray->simplexCount);
}

void simplexArray_set_index(SimplexArray *simplexArray, unsigned int simplexIndex, unsigned int indexIndex, unsigned int index)
{
    *(simplexArray->indexes + simplexIndex * (simplexArray->dimensions + 1) + indexIndex) = index;
}

void simplexArray_set_simplex(SimplexArray *simplexArray, unsigned int index, Simplex *simplex)
{
    memcpy(simplexArray->indexes + (simplexArray->dimensions + 1) * index, simplex->indexes, sizeof(unsigned int) *  (simplexArray->dimensions + 1));
}

void simplexArray_iterate_points(SimplexArray *simplexArray, void (*iterateFunction)(Point *))
{
    Point *point = malloc(sizeof(Point));

    point->dimensions = simplexArray->points->dimensions;

    for(unsigned int p = 0; p < (simplexArray->dimensions + 1) * simplexArray->simplexCount; p++)
    {
        point->data = simplexArray->points->data + simplexArray->indexes[p];

        iterateFunction(point);
    }
}

void simplexArray_iterate_simplexes(SimplexArray *simplexArray, void (*iterateFunction)(Simplex *))
{
    Simplex *simplex = malloc(sizeof(Simplex));

    simplex->dimensions = simplexArray->dimensions;

    simplex->points = simplexArray->points;

    for(unsigned int s = 0; s < simplexArray->simplexCount; s++)
    {

        simplex->indexes = simplexArray->indexes + s * (simplexArray->dimensions + 1);

        iterateFunction(simplex);
    }

    free(simplex);
}

void simplexArray_destroy(SimplexArray *simplexArray)
{
    free(simplexArray->indexes);
    simplexArray->dimensions = 0;
    simplexArray->simplexCount = 0;
}
