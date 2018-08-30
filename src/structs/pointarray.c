#include "pointarray.h"

#include <stdlib.h>
#include <string.h>

PointArray pointArray_create(unsigned int dimensions, unsigned int pointCount)
{
    PointArray pointArray;

    pointArray.data = calloc(dimensions * pointCount, sizeof(double));
    pointArray.dimensions = dimensions;
    pointArray.pointCount = pointCount;

    return pointArray;
}

void pointArray_set_points(PointArray *pointArray, double *data)
{
    memcpy(pointArray->data, data, sizeof(double) * pointArray->dimensions * pointArray->pointCount);
}

void pointArray_set_point(PointArray *pointArray, unsigned int index, Point *point)
{
    memcpy(pointArray->data + index, point->data, sizeof(double) * pointArray->dimensions);
}

void pointArray_iterate(PointArray *pointArray, void (*iterateFunction)(Point *))
{
    Point *point = malloc(sizeof(Point));

    point->dimensions = pointArray->dimensions;

    for(unsigned int p = 0; p < pointArray->pointCount; p++)
    {
        point->data = pointArray->data + p * pointArray->dimensions;

        iterateFunction(point);
    }

    free(point);
}

void pointArray_destroy(PointArray  *pointArray)
{
    free(pointArray->data);
    pointArray->dimensions = 0;
    pointArray->pointCount = 0;
}
