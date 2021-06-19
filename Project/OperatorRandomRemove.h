#ifndef OPERATOR_RANDOM_REMOVE_H
#define OPERATOR_RANDOM_REMOVE_H

#include "Operator.h"

class OperatorRandomRemove:public Operator{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif