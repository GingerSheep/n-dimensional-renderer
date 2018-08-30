#ifndef POINT_ARRAY_H_INCLUDED
#define POINT_ARRAY_H_INCLUDED

#include "point.h"

typedef struct
{
    double *data;
    unsigned int dimensions;
    unsigned int pointCount;
} PointArray;

PointArray pointArray_create(unsigned int dimensions, unsigned int pointCount);

void pointArray_set_points(PointArray *pointArray, double *data);

void pointArray_set_point(PointArray *pointArray, unsigned int index, Point *point);

void pointArray_iterate(PointArray *pointArray, void (*iterateFunction)(Point *));

void pointArray_destroy(PointArray *pointArray);

#endif // POINT_ARRAY_H_INCLUDED
