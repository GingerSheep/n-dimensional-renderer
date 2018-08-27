#ifndef SIMPLEXARRAY_H_INCLUDED
#define SIMPLEXARRAY_H_INCLUDED

#include "simplex.h"

typedef struct
{
    double *data;
    unsigned int dimensions;
    unsigned int simplexCount;
} SimplexArray;

SimplexArray simplexArray_create(unsigned int dimensions, unsigned simplexCount);

void simplexArray_set_points(SimplexArray *simplexArray, double *data);

void simplexArray_set_point(SimplexArray *simplexArray, unsigned int simplexIndex, unsigned int pointIndex, double *data);

void simplexArray_set_simplex(SimplexArray *simplexArray, unsigned int index, Simplex *simplex);

void simplexArray_iterate_points(SimplexArray *simplexArray, void (*iterateFunction)(double*, int));

void simplexArray_iterate_simplexes(SimplexArray *simplexArray, void (*iterateFunction)(Simplex));

void simplexArray_destroy(SimplexArray *simplexArray);

#endif // SIMPLEXARRAY_H_INCLUDED
