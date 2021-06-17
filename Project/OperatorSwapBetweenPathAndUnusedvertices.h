#ifndef OPERATOR_SWAP_BETWEEN_PATH_AND_UNUSED_VERTICES_H
#define OPERATOR_SWAP_BETWEEN_PATH_AND_UNUSED_VERTICES_H

#include "Operator.h"

class OperatorSwapBetweenPathAndUnusedvertices: public Operator{
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};
#endif