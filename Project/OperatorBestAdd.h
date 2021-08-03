#ifndef OPERATOR_BEST_ADD_H
#define OPERATOR_BEST_ADD_H

#include "Operator.h"

class OperatorBestAdd: public Operator{
    private:
        bool is_added;
        Solution realize_add( Solution sol );
        
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );
};

#endif