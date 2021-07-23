#ifndef OPERATOR_RANDOM_REMOVE_H
#define OPERATOR_RANDOM_REMOVE_H

#include "Operator.h"

class OperatorRandomRemove:public Operator{
    private:
        int random_path( Solution * sol );
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif