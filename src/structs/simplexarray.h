#ifndef SIMPLEXARRAY_H_INCLUDED
#define SIMPLEXARRAY_H_INCLUDED

#include "simplex.h"

typedef struct
{
    PointArray *points;
    unsigned int *indexes;
    unsigned int dimensions;
    unsigned int simplexCount;
} SimplexArray;

SimplexArray simplexArray_create(unsigned int dimensions, unsigned int simplexCount, PointArray *points);

void simplexArray_set_indexes(SimplexArray *simplexArray, unsigned int *indexes);

void simplexArray_set_index(SimplexArray *simplexArray, unsigned int simplexIndex, unsigned int indexIndex, unsigned int index);

void simplexArray_set_simplex(SimplexArray *simplexArray, unsigned int index, Simplex *simplex);

void simplexArray_iterate_points(SimplexArray *simplexArray, void (*iterateFunction)(Point *));

void simplexArray_iterate_simplexes(SimplexArray *simplexArray, void (*iterateFunction)(Simplex *));

void simplexArray_add(SimplexArray *simplexArray, Simplex *simplex);

void simplexArray_remove(SimplexArray *simplexArray, unsigned int index);

void simplexArray_destroy(SimplexArray *simplexArray);

#endif // SIMPLEXARRAY_H_INCLUDED
