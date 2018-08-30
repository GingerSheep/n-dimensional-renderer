#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

typedef struct
{
    double *data;
    unsigned int dimensions;
} Point;

Point point_create(unsigned int dimensions);

void point_set(Point *point, double *data);

void point_set_value(Point *point, unsigned int dimension, double value);

void point_destroy(Point *point);

#endif // POINT_H_INCLUDED
