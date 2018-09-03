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

void pointArray_add(PointArray *pointArray, Point *point)
{
    double *newData = realloc(pointArray->data, pointArray->dimensions * (pointArray->pointCount + 1) * sizeof(double));

    if(newData != NULL)
    {
        pointArray->data = newData;

        memcpy(newData + pointArray->dimensions * pointArray->pointCount, point, sizeof(double) * point->dimensions);

        pointArray->pointCount = pointArray->pointCount + 1;
    }
}

void pointArray_remove(PointArray *pointArray, unsigned int index)
{
    double *newData = malloc(pointArray->dimensions * (pointArray->pointCount - 1) * sizeof(double));

    memcpy(newData, pointArray->data, pointArray->dimensions * index * sizeof(double));

    memcpy(newData + pointArray->dimensions * index, pointArray->data + pointArray->dimensions * (index + 1), pointArray->dimensions * (pointArray->pointCount - 1 - index) * sizeof(double));

    free(pointArray->data);

    pointArray->pointCount = pointArray->pointCount - 1;

    pointArray->data = newData;
}

void pointArray_destroy(PointArray  *pointArray)
{
    free(pointArray->data);
    pointArray->dimensions = 0;
    pointArray->pointCount = 0;
}
