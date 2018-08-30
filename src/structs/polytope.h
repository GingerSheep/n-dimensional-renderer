#ifndef POLYTOPE_H_INCLUDED
#define POLYTOPE_H_INCLUDED

#include "simplexarray.h"

typedef struct
{
    PolytopeArray simplexes;
    SimplexArray sharedSurfaceSimplexes;
} PolytopeBase;

#endif // POLYTOPE_H_INCLUDED
