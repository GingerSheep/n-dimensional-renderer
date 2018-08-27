#include "simplexarray.h"

#include <stdlib.h>
#include <string.h>

SimplexArray simplexArray_create(unsigned int dimensions, unsigned simplexCount)
{
    SimplexArray simplexArray;

    simplexArray.data = calloc(dimensions * (dimensions + 1) * simplexCount, sizeof(double));
    simplexArray.dimensions = dimensions;
    simplexArray.simplexCount = simplexCount;

    return simplexArray;
}

void simplexArray_set_points(SimplexArray *simplexArray, double *data)
{
    memcpy(simplexArray->data, data, sizeof(double) * simplexArray->dimensions * (simplexArray->dimensions + 1) * simplexArray->simplexCount);
}

void simplexArray_set_point(SimplexArray *simplexArray, unsigned int simplexIndex, unsigned int pointIndex, double *data)
{
    memcpy(simplexArray->data + simplexArray->dimensions * simplexIndex + pointIndex, data, sizeof(double) * simplexArray->dimensions);
}

void simplexArray_set_simplex(SimplexArray *simplexArray, unsigned int index, Simplex *simplex)
{
    memcpy(simplexArray-> data + simplexArray->dimensions * index, simplex->data, sizeof(double) * simplexArray->dimensions * (simplexArray->dimensions + 1));
}

void simplexArray_iterate_points(SimplexArray *simplexArray, void (*iterateFunction)(double*, int))
{
    for(unsigned int p = 0; p < (simplexArray->dimensions + 1) * simplexArray->simplexCount; p++)
    {
        iterateFunction(simplexArray->data + p * simplexArray->dimensions, simplexArray->dimensions);
    }
}

void simplexArray_iterate_simplexes(SimplexArray *simplexArray, void (*iterateFunction)(Simplex))
{
    Simplex *simplex = malloc(sizeof(Simplex));
    simplex->dimensions = simplexArray->dimensions;

    for(unsigned int s = 0; s < simplexArray->simplexCount; s++)
    {
        simplex->data = simplexArray->data + s * simplexArray->dimensions * (simplexArray->dimensions + 1);

        iterateFunction(*simplex);
    }

    free(simplex);
}

void simplexArray_destroy(SimplexArray *simplexArray)
{
    free(simplexArray->data);
    simplexArray->dimensions = 0;
    simplexArray->simplexCount = 0;
}
