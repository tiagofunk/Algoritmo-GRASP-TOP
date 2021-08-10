#ifndef LOCAL_SEARCH_WITH_OPERATORS_H
#define LOCAL_SEARCH_WITH_OPERATORS_H

#include "LocalSearch.h"
#include "Operator.h"

class LocalSearchWithOperators: public LocalSearch {
    private:
        vector< Operator * > operators;
        vector< Vertice * > unused_vertices;

        bool is_better( Solution actual, Solution best );
        bool is_bigger( Solution sol );
        bool is_shorter( Solution actual, Solution best );

    public:
        LocalSearchWithOperators( vector< Operator * > operators );

        virtual Solution execute( Solution sol, vector< Vertice * > vertices );
        virtual vector< Vertice * > get_unused_vertices();
};

#endif