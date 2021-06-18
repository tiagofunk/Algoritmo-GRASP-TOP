#ifndef OPERATOR_2_OPT_H
#define OPERATOR_2_OPT_H

#include "Operator.h"

class Operator2opt:public Operator{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif