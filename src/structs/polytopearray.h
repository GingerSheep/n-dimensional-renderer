#ifndef POLYTOPEARRAY_H_INCLUDED
#define POLYTOPEARRAY_H_INCLUDED

#include "polytope.h"

typedef struct
{
    PointArray *points;
    unsigned int **indexes;
    unsigned int *simplexCounts;
    unsigned int dimensions;
    unsigned int polytopeCount;
} PolytopeArray;

PolytopeArray polytopeArray_create(unsigned int dimensions, unsigned int polytopeCount, PointArray *points);

void polytopeArray_set_indexesAndSimplexCounts(PolytopeArray *polytopeArray, unsigned int **indexes, unsigned int *simplexCounts);

void polytopeArray_set_polytope(PolytopeArray *polytopeArray, unsigned int polytopeIndex, Polytope polytope);

void polytopeArray_set_simplex(PolytopeArray *polytopeArray, unsigned int polytopeIndex, unsigned int simplexIndex, Simplex simplex);

void polytopeArray_set_index(PolytopeArray *polytopeArray, unsigned int polytopeIndex, unsigned int simplexIndex, unsigned int indexIndex, unsigned int index);

void polytopeArray_iterate_points(PolytopeArray *polytopeArray, void (*iterateFunction)(Point *));

void polytopeArray_iterate_simplexes(PolytopeArray *polytopeArray, void (*iterateFunction)(Simplex *));

void polytopeArray_iterate_polytopes(PolytopeArray *polytopeArray, void (*iterateFunction)(Polytope *));

void polytopeArray_add(PolytopeArray *polytopeArray, Polytope *polytope);

void polytopeArray_remove(PolytopeArray *polytopeArray, unsigned int index);

void polytopeArray_destroy(PolytopeArray *polytopeArray);

#endif // POLYTOPEARRAY_H_INCLUDED
