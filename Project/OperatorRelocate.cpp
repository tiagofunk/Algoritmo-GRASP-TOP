#include "OperatorRelocate.h"
#include "main.h"

Solution OperatorRelocate::realize_operation( Solution sol ){
    this->is_swaped = false;
    Solution actual = sol;
    Solution best   = sol;
    for( int i = 0; i < actual.get_number_paths(); i++ ){
        for( int j = 1; j < actual.get_length_of_path( i ) - 1; j++ ){
            for( int k = 0; k < actual.get_number_paths(); k++ ){
                if( i != k ){
                    for( int l = 1; l < actual.get_length_of_path( k )-1; l++ ){
                        actual.move( i, j, k, l );
                        if( actual.get_total_time() < best.get_total_time() ){
                            best = actual;
                            this->is_swaped = true;
                        }
                        actual = sol;
                    }
                }
            }    
        }
    }
    return best;
}

Solution OperatorRelocate::execute( Solution s, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int count = 0;
    do{
        s = this->realize_operation( s );
        count++;
    }while( this->is_swaped );
    show_log( "number of relocates: " + std::to_string( count ) + "\n", 3 );
    return s;
}