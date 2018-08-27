#ifndef SIMPLEX_H_INCLUDED
#define SIMPLEX_H_INCLUDED

typedef struct
{
    double *data;
    unsigned int dimensions;
} Simplex;

Simplex simplex_create(unsigned int dimensions);

void simplex_set_points(Simplex *simplex, double *data);

void simplex_set_point(Simplex *simplex, unsigned int index, double *data);

void simplex_iterate(Simplex *simplex, void (*iterateFunction)(double*, int));

void simplex_destroy(Simplex *simplex);

#endif // SIMPLEX_H_INCLUDED
