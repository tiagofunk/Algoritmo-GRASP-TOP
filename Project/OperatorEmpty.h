#ifndef OPERATOR_EMPTY_H
#define OPERATOR_EMPTY_H

#include "Operator.h"
#include "Solution.h"
#include "Vertice.h"

class OperatorEmpty: public Operator{
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );
};

#endif