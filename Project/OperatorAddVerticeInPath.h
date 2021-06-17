#ifndef OPERATOR_ADD_VERTICE_IN_PATH_H
#define OPERATOR_ADD_VERTICE_IN_PATH_H

#include "Operator.h"

class OperatorAddVerticeInPath: public Operator {
    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
        virtual vector< Vertice * > get_unused_vertice();
};

#endif