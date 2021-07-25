#include "Operator2opt.h"


Solution * Operator2opt::execute( Solution * s, vector< Vertice * > unused_vertices ){
    bool is_ok;
    int length_path = 0;
    Solution * actual = new Solution( *s );
    Solution * best = new Solution( *s );
    vector< Vertice * > vertices_in_solution;
    this->unused_vertices = unused_vertices;

    for( int i = 0; i < actual->get_number_paths(); i++ ){
        length_path = actual->get_length_of_path( i );
        if( length_path <= 3 ) continue;

        for( int j = 1; j < length_path-1; j++ ){
            vertices_in_solution.clear();
            is_ok = false;
            for( int k = j+1; k < length_path-1; k++ ){
				vertices_in_solution.push_back( actual->get_vertice_in_path( i, j+1 ) );
                actual->remove( i, j+1 );
			}
			for( int k = 1; k <= j; k++ ){
				vertices_in_solution.push_back( actual->get_vertice_in_path( i, 1 ) );
                actual->remove( i, 1 );
			}
            for( unsigned int k = 0; k < vertices_in_solution.size(); k++ ){
                if( !actual->add( i, vertices_in_solution[ k ] ) ){
                    is_ok = false;
                }
            }
            if( is_ok && actual->get_time_path( i ) < best->get_time_path( i ) ){
                delete best;
                best = new Solution( *actual );
            }
            delete actual;
            actual = new Solution( *s );
        }
    }
    delete s;
    return best;
}