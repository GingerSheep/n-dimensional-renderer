#include "simplex.h"

#include <stdlib.h>
#include <string.h>

Simplex simplex_create(unsigned int dimensions)
{
    Simplex simplex;

    simplex.data = calloc(dimensions * (dimensions + 1), sizeof(double));
    simplex.dimensions = dimensions;

    return simplex;
}

void simplex_set_points(Simplex *simplex, double *data)
{
    memcpy(simplex->data, data, sizeof(double) * simplex->dimensions * (simplex->dimensions + 1));
}

void simplex_set_point(Simplex *simplex, unsigned int index, double *data)
{
    memcpy(simplex->data + index, data, sizeof(double) * simplex->dimensions);
}

void simplex_iterate(Simplex *simplex, void (*iterateFunction)(double*, int))
{
    for(unsigned int p = 0; p < simplex->dimensions + 1; p++)
    {
        iterateFunction(simplex->data + p * simplex->dimensions, simplex->dimensions);
    }
}

void simplex_destroy(Simplex *simplex)
{
    free(simplex->data);
    simplex->dimensions = 0;
}
