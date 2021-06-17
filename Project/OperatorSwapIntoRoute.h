#ifndef OPERATOR_SWAP_INTO_ROUTE_H
#define OPERATOR_SWAP_INTO_ROUTE_H

#include "Operator.h"

class OperatorSwapIntoRoute: public Operator{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif