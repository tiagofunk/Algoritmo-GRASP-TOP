#include "Operator2opt.h"

#include <iostream>
using std::cout;
using std::endl;

Solution * Operator2opt::execute( Solution * s, vector< Vertice * > unused_vertices ){
    int length_path = 0;
    Solution * actual = new Solution( *s );
    Solution * best = new Solution( *s );
    vector< Vertice * > vertices_in_solution;
    this->unused_vertices = unused_vertices;

    for( int i = 0; i < actual->get_number_paths(); i++ ){
        vertices_in_solution.clear();
        length_path = actual->get_length_of_path( i );
        if( length_path <= 3 ) continue;

        for( int j = 1; j < length_path-1; j++ ){
            for( int k = j+1; k < length_path-1; k++ ){
				vertices_in_solution.push_back( actual->get_vertice_in_path( i, j+1 ) );
                actual->remove( i, k );
			}
			for( int k = 1; k <= j; k++ ){
				vertices_in_solution.push_back( actual->get_vertice_in_path( i, 1 ) );
                actual->remove( i, k );
			}
            for( unsigned int k = 0; k < vertices_in_solution.size(); k++ ){
                actual->add_vertice( i, vertices_in_solution[ k ] );
            }
            if( actual->get_time_path( i ) < best->get_time_path( i ) ){
                delete best;
                best = new Solution( *actual );
            }
            delete actual;
            actual = new Solution( *s );
        }
    }

    return best;
}