#ifndef OPERATOR_H
#define OPERATOR_H

#include "Solution.h"
#include "Vertice.h"

class Operator{
    protected:
        vector< Vertice * > unused_vertices;
    
    public:
        virtual Solution execute( Solution sol, vector< Vertice * > unused_vertices ) = 0;
        
        vector< Vertice * > get_unused_vertice(){
            return this->unused_vertices;
        };
};

#endif