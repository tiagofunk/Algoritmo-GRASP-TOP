#ifndef LOCAL_SEARCH_WITH_OPERATORS_H
#define LOCAL_SEARCH_WITH_OPERATORS_H

#include "LocalSearch.h"

class LocalSearchWithOperators: public LocalSearch {
    private:
        Solution * generate_neighborhood_and_select( Solution * s, vector< Vertice * > vertices );

    public:
        LocalSearchWithOperators();
        ~LocalSearchWithOperators();

        Solution * execute( Solution * sol, vector< Vertice * > vertices );
};

#endif