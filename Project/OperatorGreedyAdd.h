#ifndef OPERATOR_GREEDY_ADD_H
#define OPERATOR_GREEDY_ADD_H

#include "Operator.h"

class OperatorGreedyAdd: public Operator {
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif