#ifndef OPERATOR_RANDOM_REMOVE_H
#define OPERATOR_RANDOM_REMOVE_H

#include "Operator.h"

class OperatorRandomRemove:public Operator{
    private:
        double iterations;
        int random_path( Solution sol );
        Solution remove( Solution sol );
    public:
        OperatorRandomRemove( double iterations );
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );
};

#endif