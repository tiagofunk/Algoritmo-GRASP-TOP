#ifndef LOCAL_SEARCH_WITH_OPERATORS_H
#define LOCAL_SEARCH_WITH_OPERATORS_H

#include "LocalSearch.h"

class LocalSearchWithOperators: public LocalSearch {
    private:
        vector< Vertice * > unused_vertices;

        Solution * add_vertice_in_path( Solution * s );
        Solution * swap_between_path_and_unused_vertices( Solution * s );

    public:
        LocalSearchWithOperators();
        ~LocalSearchWithOperators();

        Solution * execute( Solution * sol, vector< Vertice * > vertices );
        vector< Vertice * > get_unused_vertices();
};

#endif