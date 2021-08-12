#ifndef OPERATOR_FIRST_ADD_H
#define OPERATOR_FIRST_ADD_H

#include "Operator.h"

class OperatorFirstAdd: public Operator {
    private:
        bool is_added;
        Solution realize_add( Solution sol );
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );
};

#endif