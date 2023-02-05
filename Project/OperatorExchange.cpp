#include "OperatorExchange.h"
#include "main.h"
#include "Utils.h"

Solution OperatorExchange::realize_operation( Solution sol ){
    this->is_swaped = false;
    Solution actual = sol;
    Solution best = sol;
    for( int i = 0; i < actual.get_number_paths(); i++ ){
        for( int j = i+1; j < actual.get_number_paths(); j++ ){
            for( int k = 1; k < actual.get_length_of_path( i )-1; k++ ){
                for( int l = 1; l < actual.get_length_of_path( j )-1; l++ ){
                    if( actual.swap( i,k, j, l ) ){
                        if( truncate( actual.get_total_time(), 2 ) < truncate( best.get_total_time(), 2 ) ){
                            best = actual;
                            this->is_swaped = true;
                        }else{
                            actual = sol;
                        }
                    }
                }
            }
        }
    }
    return best;
}

Solution OperatorExchange::execute( Solution s, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int count = 0;
    do{
        s = this->realize_operation( s );
        count++;
    }while( this->is_swaped );
    show_log( "number of exchanges: " + std::to_string( count ) + "\n", 3 );
    return s;
}