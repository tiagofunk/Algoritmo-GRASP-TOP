#include "OperatorRandomRemove.h"
#include "main.h"

#include <vector>
using std::vector;

int OperatorRandomRemove::random_path( Solution sol ){
    int position = 0, aux = 0;
    vector< int > numbers;
    for( int i = 0; i < sol.get_number_paths(); i++ ){
        if( sol.is_empty( i ) ){
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

Solution OperatorRandomRemove::remove( Solution sol ){
    this->unused_vertices = unused_vertices;
    int path = this->random_path( sol );
    if( path == -1 ) return sol;
    Solution actual = sol;
    int position = rand() % ( actual.get_length_of_path( path )-2 ) + 1;
    Vertice * v = actual.get_vertice_in_path( path, position );
    actual.remove( path, position );
    this->unused_vertices.push_back( v );
    return actual;
}

OperatorRandomRemove::OperatorRandomRemove( double iterations ){
    this->iterations = iterations;
}

Solution OperatorRandomRemove::execute( Solution sol, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int n = sol.get_total_length_of_path();
    n = n - 2 * sol.get_number_paths();
    if( n != 0 ){
        n = n * this->iterations + 1;
        for( int i = 0; i < n; i++ ){
            sol = this->remove( sol );
        }
        show_log( "number of removes: " + std::to_string( n ) + "\n", 3 );   
    }
    return sol;
}