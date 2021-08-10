#include "OperatorEmpty.h"


Solution OperatorEmpty::execute( Solution sol, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    return sol;
}