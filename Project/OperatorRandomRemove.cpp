#include "OperatorRandomRemove.h"

#include <vector>
using std::vector;

int OperatorRandomRemove::random_path( Solution * sol ){
    int position = 0, aux = 0;
    vector< int > numbers;
    for( int i = 0; i < sol->get_number_paths(); i++ ){
        if( sol->path_is_empty( i ) ){
            numbers.push_back( i );
        }
    }
    for( unsigned int i = 0; i < numbers.size(); i++ ){
        position = rand() % numbers.size();
        aux = numbers[ position ];
        numbers[ position ] = numbers[ i ];
        numbers[ i ] = aux;
    }
    if( numbers.empty() ) return -1;
    return numbers[ 0 ];
}

Solution * OperatorRandomRemove::execute( Solution * sol, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int path = this->random_path( sol );
    if( path == -1 ) return sol;
    Solution * actual = new Solution( *sol );
    int position = rand() % ( actual->get_length_of_path( path )-2 ) + 1;
    Vertice * v = actual->get_vertice_in_path( path, position );
    actual->remove( path, position );
    this->unused_vertices.push_back( v );
    delete sol;
    return actual;
}