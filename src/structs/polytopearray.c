#include "polytopearray.h"

#include <stdlib.h>
#include <string.h>

PolytopeArray polytopeArray_create(unsigned int dimensions, unsigned int polytopeCount, PointArray *points)
{
    PolytopeArray polytopeArray;

    polytopeArray.points = points;
    polytopeArray.indexes = calloc(polytopeCount, sizeof(unsigned int*));
    polytopeArray.simplexCounts = calloc(polytopeCount, sizeof(unsigned int));
    polytopeArray.dimensions = dimensions;
    polytopeArray.polytopeCount = polytopeCount;

    return polytopeArray;
}

void polytopeArray_set_indexesAndSimplexCounts(PolytopeArray *polytopeArray, unsigned int **indexes, unsigned int *simplexCounts)
{
    memcpy(polytopeArray->simplexCounts, simplexCounts, sizeof(unsigned int) * polytopeArray->polytopeCount);

    for(unsigned int p = 0; p < polytopeArray->polytopeCount; p++)
    {
        if(*(polytopeArray->indexes + p) != 0) free(*(polytopeArray->indexes + p));

        *(polytopeArray->indexes + p) = malloc(sizeof(unsigned int *) * polytopeArray->polytopeCount);
        memcpy(*(polytopeArray->indexes + p), *(indexes + p), sizeof(unsigned int) * (polytopeArray->dimensions + 1) * *(polytopeArray->simplexCounts + p));
    }
}

void polytopeArray_set_polytope(PolytopeArray *polytopeArray, unsigned int polytopeIndex, Polytope polytope)
{
    *(polytopeArray->simplexCounts + polytopeIndex) = polytope.simplexes.simplexCount;

    realloc(*(polytopeArray->indexes + polytopeIndex), (polytope.simplexes.dimensions + 1) * polytope.simplexes.simplexCount * sizeof(unsigned int));
    memcpy(*(polytopeArray->indexes + polytopeIndex), polytope.simplexes.indexes, (polytope.simplexes.dimensions + 1) * polytope.simplexes.simplexCount * sizeof(unsigned int));
}

void polytopeArray_set_simplex(PolytopeArray *polytopeArray, unsigned int polytopeIndex, unsigned int simplexIndex, Simplex simplex)
{
    memcpy(*(polytopeArray->indexes + polytopeIndex) + (simplex.dimensions + 1) * simplexIndex, simplex.indexes, sizeof(unsigned int) * (simplex.dimensions + 1));
}

void polytopeArray_set_index(PolytopeArray *polytopeArray, unsigned int polytopeIndex, unsigned int simplexIndex, unsigned int indexIndex, unsigned int index)
{
    *(*(polytopeArray->indexes + polytopeIndex) + (polytopeArray->dimensions + 1) * simplexIndex + indexIndex) = index;
}

void polytopeArray_iterate_points(PolytopeArray *polytopeArray, void (*iterateFunction)(Point *))
{
    Point *point = malloc(sizeof(Point));
    point->dimensions = polytopeArray->dimensions;

    for(unsigned int p = 0; p < polytopeArray->polytopeCount; p++)
    {
        for(unsigned int po = 0; po < *(polytopeArray->simplexCounts + p) * (polytopeArray->dimensions + 1); po++)
        {
            point->data = polytopeArray->points->data + *(polytopeArray->indexes + p)[po];

            iterateFunction(point);
        }
    }

    free(point);
}

void polytopeArray_iterate_simplexes(PolytopeArray *polytopeArray, void (*iterateFunction)(Simplex *))
{
    Simplex *simplex  = malloc(sizeof(Simplex));
    simplex->dimensions = polytopeArray->dimensions;
    simplex->points = polytopeArray->points;

    for(unsigned int p = 0; p < polytopeArray->polytopeCount; p++)
    {
        for(unsigned int s = 0; s < *(polytopeArray->simplexCounts + p); s++)
        {
            simplex->indexes = *(polytopeArray->indexes + p) + s * (polytopeArray->dimensions + 1);

            iterateFunction(simplex);
        }
    }

    free(simplex);
}

void polytopeArray_iterate_polytopes(PolytopeArray *polytopeArray, void (*iterateFunction)(Polytope *))
{
    Polytope *polytope = malloc(sizeof(Polytope));
    polytope->simplexes.dimensions = polytopeArray->dimensions;
    polytope->simplexes.points = polytopeArray->points;

    for(unsigned int p = 0; p < polytopeArray->polytopeCount; p++)
    {
        polytope->simplexes.simplexCount = polytopeArray->simplexCounts[p];
        polytope->simplexes.indexes = polytopeArray->indexes[p];

        iterateFunction(polytope);
    }

    free(polytope);
}

void polytopeArray_add(PolytopeArray *polytopeArray, Polytope *polytope)
{
    unsigned int **newIndexes = realloc(polytopeArray->indexes, (polytopeArray->polytopeCount + 1) * sizeof(unsigned int *));
    unsigned int *newSimplexCounts = realloc(polytopeArray->simplexCounts, (polytopeArray->polytopeCount + 1) * sizeof(unsigned int *));

    if(newIndexes != NULL)
    {
        polytopeArray->indexes = newIndexes;

        polytopeArray->indexes[polytopeArray->polytopeCount] = malloc(polytope->simplexes.simplexCount * (polytopeArray->dimensions + 1) * sizeof(unsigned int));
        memcpy(polytopeArray->indexes + polytopeArray->polytopeCount, polytope->simplexes.indexes, polytope->simplexes.simplexCount * (polytopeArray->dimensions + 1) * sizeof(unsigned int));

        polytopeArray->simplexCounts = newSimplexCounts;
        polytopeArray->simplexCounts[polytopeArray->polytopeCount] = polytope->simplexes.simplexCount;

        polytopeArray->polytopeCount++;
    }
}

void polytopeArray_remove(PolytopeArray *polytopeArray, unsigned int index)
{
    unsigned int **newIndexes = malloc((polytopeArray->polytopeCount - 1) * sizeof(unsigned int *));

    memcpy(newIndexes, polytopeArray->indexes, index * sizeof(unsigned int *));
    memcpy(newIndexes + index, polytopeArray->indexes + index + 1, (polytopeArray->polytopeCount - 1 - index) * sizeof(unsigned int *));

    free(polytopeArray->indexes[index]);
    free(polytopeArray->indexes);
    polytopeArray->indexes = newIndexes;

    unsigned int *newSimplexCounts = malloc((polytopeArray->polytopeCount - 1) * sizeof(unsigned int));

    memcpy(newSimplexCounts, polytopeArray->simplexCounts, index * sizeof(unsigned int));
    memcpy(newSimplexCounts + index, polytopeArray->simplexCounts + index + 1, (polytopeArray->polytopeCount - 1 - index) * sizeof(unsigned int));

    free(polytopeArray->simplexCounts);
    polytopeArray->simplexCounts = newSimplexCounts;

    polytopeArray->polytopeCount--;
}

void polytopeArray_destroy(PolytopeArray *polytopeArray)
{
    for(unsigned int p = 0; p < polytopeArray->polytopeCount; p++)
    {
        free(polytopeArray->indexes[p]);
    }
    free(polytopeArray->indexes);
    free(polytopeArray->simplexCounts);
    polytopeArray->dimensions = 0;
    polytopeArray->polytopeCount = 0;
}
