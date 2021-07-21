#ifndef OPERATOR_WORST_REMOVE_H
#define OPERATOR_WORST_REMOVE_H

#include "Operator.h"

class OperatorWorstRemove: public Operator{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif