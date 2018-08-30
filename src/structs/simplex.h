#ifndef SIMPLEX_H_INCLUDED
#define SIMPLEX_H_INCLUDED

#include "pointarray.h"

typedef struct
{
    PointArray *points;
    unsigned int *indexes;
    unsigned int dimensions;
} Simplex;

Simplex simplex_create(unsigned int dimensions, PointArray *points);

void simplex_set_indexes(Simplex *simplex, unsigned int *indexes);

void simplex_set_index(Simplex *simplex, unsigned int index, unsigned int pointIndex);

void simplex_iterate(Simplex *simplex, void (*iterateFunction)(Point *));

void simplex_destroy(Simplex *simplex);

#endif // SIMPLEX_H_INCLUDED
