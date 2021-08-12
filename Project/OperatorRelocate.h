#ifndef OPERATOR_RELOCATE_H
#define OPERATOR_RELOCATE_H

#include "Operator.h"

class OperatorRelocate : public Operator{
    private:
        bool is_swaped;
        Solution realize_operation( Solution sol );
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices );

};

#endif