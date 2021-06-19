#ifndef OPERATOR_INTER_ROUTE_H
#define OPERATOR_INTER_ROUTE_H

#include "Operator.h"

class OperatorSwapInterRoute: public Operator{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif