#include "OperatorRelocate.h"

Solution * OperatorRelocate::execute( Solution * s, vector< Vertice * > unused_vertices ){
    Solution * actual = new Solution( *s );
    Solution * best   = new Solution( *s );
    this->unused_vertices = unused_vertices;

    for( int i = 0; i < actual->get_number_paths(); i++ ){
        for( int j = 1; j < actual->get_length_of_path( i ) - 1; j++ ){
            for( int k = 0; k < actual->get_number_paths(); k++ ){
                if( i != k ){
                    for( int l = 1; l < actual->get_length_of_path( k )-1; l++ ){
                        actual->move( i, j, k, l );
                        if( actual->get_total_time() < best->get_total_time() ){
                            delete best;
                            best = new Solution( *actual );
                        }
                        delete actual;
                        actual = new Solution( *s );
                    }
                }
            }    
        }
    }
    delete s;
    return best;
}