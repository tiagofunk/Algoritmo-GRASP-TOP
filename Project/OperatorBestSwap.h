#ifndef OPERATOR_BEST_SWAP_H
#define OPERATOR_BEST_SWAP_H

#include "Operator.h"

class OperatorBestSwap: public Operator{
    private:
        bool is_added;
        Solution realize_add( Solution sol );
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );
};
#endif