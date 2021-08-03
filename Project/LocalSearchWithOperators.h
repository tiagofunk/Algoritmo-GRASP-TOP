#ifndef LOCAL_SEARCH_WITH_OPERATORS_H
#define LOCAL_SEARCH_WITH_OPERATORS_H

#include "LocalSearch.h"
#include "Operator.h"

class LocalSearchWithOperators: public LocalSearch {
    private:
        vector< Operator * > operators;
        vector< Vertice * > unused_vertices;

    public:
        LocalSearchWithOperators( vector< Operator * > operators );
        ~LocalSearchWithOperators();

        virtual Solution execute( Solution sol, vector< Vertice * > vertices );
        virtual vector< Vertice * > get_unused_vertices();
};

#endif