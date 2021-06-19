#include "OperatorSwapIntoRoute.h"

Solution * OperatorSwapIntoRoute::execute( Solution * s, vector< Vertice * > unused_vertices ){
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    this->unused_vertices = unused_vertices;

    for( int i = 0; i < s->get_number_paths(); i++){
        for (int j = 1; j < s->get_length_of_path( i )-1; j++){
            for(int k = j+1; k < s->get_length_of_path( i )-1; k++ ){
                actual->swap( i, j, k );
                if( actual->get_time_path( i ) < best->get_time_path( i ) ){
                    delete best;
                    best = new Solution( *actual );
                }
                delete actual;
                actual = new Solution( *s );
            }
        }
    }
    delete s;
    return best;
}