#ifndef OPERATOR_EXCHANGE_H
#define OPERATOR_EXCHANGE_H

#include "Operator.h"

class OperatorExchange: public Operator{
    private:
        bool is_swaped;
        Solution realize_operation( Solution sol );
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );
};

#endif