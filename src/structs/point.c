#include "point.h"

#include <stdlib.h>
#include <string.h>

Point point_create(unsigned int dimensions)
{
    Point point;

    point.data = calloc(dimensions, sizeof(double));
    point.dimensions = dimensions;

    return point;
}

void point_set(Point *point, double *data)
{
    memcpy(point->data, data, sizeof(double) * point->dimensions);
}

void point_set_value(Point *point, unsigned int dimension, double value)
{
    *(point->data + dimension) = value;
}

void point_destroy(Point *point)
{
    free(point->data);

    point->dimensions = 0;
}
