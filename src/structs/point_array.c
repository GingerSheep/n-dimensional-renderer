#include "pointarray.h"

#include <stdlib.h>
#include <string.h>

PointArray pointArray_create(unsigned int dimensions, unsigned int pointCount)
{
    PointArray pointArray;

    pointArray.data = calloc(dimensions * pointCount, sizeof(dimensions));
    pointArray.dimensions = dimensions;
    pointArray.pointCount = pointCount;

    return pointArray;
}

void pointArray_set_points(PointArray *pointArray, double *data)
{
    memcpy(pointArray->data, data, sizeof(double) * pointArray->dimensions * pointArray->pointCount);
}

void pointArray_set_point(PointArray *pointArray, unsigned int index, double *data)
{
    memcpy(pointArray->data + index, data, sizeof(double) * pointArray->dimensions);
}

void pointArray_iterate(PointArray *pointArray, void (*iterateFunction)(double*, int))
{
    for(unsigned int p = 0; p < pointArray->pointCount; p++)
    {
        iterateFunction(pointArray->data + p, pointArray->dimensions);
    }
}

void pointArray_destroy(PointArray  *pointArray)
{
    free(pointArray->data);
    pointArray->dimensions = 0;
    pointArray->pointCount = 0;
}
