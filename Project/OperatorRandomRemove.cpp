#include "OperatorRandomRemove.h"

#include <iostream>

Solution * OperatorRandomRemove::execute( Solution * sol, vector< Vertice * > unused_vertices ){
    Solution * actual = new Solution( *sol );
    this->unused_vertices = unused_vertices;
    int path = rand() % actual->get_number_paths();
    if( actual->get_length_of_path( path ) != 2 ){
        int position = rand() % ( actual->get_length_of_path( path )-2 ) + 1;
        Vertice * v = actual->get_vertice_in_path( path, position );
        actual->remove( path, position );
        this->unused_vertices.push_back( v );
    }
    delete sol;
    return actual;
}