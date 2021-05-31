#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "Solution.h"
#include "Vertice.h"

class LocalSearch{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > vertices ) = 0;

};

#endif