#include "polytope.h"

#include <stdlib.h>
#include <string.h>

Polytope polytope_create(SimplexArray simplexes)
{
    Polytope polytope;

    polytope.simplexes = simplexes;

    polytope.simplexes.indexes = malloc((simplexes.dimensions + 1) * simplexes.simplexCount * sizeof(unsigned int));

    memcpy(polytope.simplexes.indexes, simplexes.indexes, (simplexes.dimensions + 1) * simplexes.simplexCount * sizeof(unsigned int));

    return polytope;
}

void polytope_destroy(Polytope *polytope)
{
    simplexArray_destroy(&polytope->simplexes);
}
