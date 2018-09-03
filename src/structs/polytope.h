#ifndef POLYTOPE_H_INCLUDED
#define POLYTOPE_H_INCLUDED

#include "simplexarray.h"

typedef struct
{
    SimplexArray simplexes;
} Polytope;

Polytope polytope_create(SimplexArray simplexes);

void polytope_destroy(Polytope *polytope);

#endif // POLYTOPE_H_INCLUDED
