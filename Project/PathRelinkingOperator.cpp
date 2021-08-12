#include "PathRelinkingOperator.h"

#include <iostream>

PathRelinkingOperator::PathRelinkingOperator( bool start_to_end ):PathRelinking(){
    this->start_to_end = start_to_end;
}

Solution PathRelinkingOperator::execute( Solution start, Solution end ){
    Solution actual;
    Solution best;
    Solution destiny;
    if( this->start_to_end ){
        actual = start;
        best = start;
        destiny = end;
    }else{
        actual = end;
        best = end;
        destiny = start;
    }

    for( int i = 0; i < destiny.get_number_paths(); i++){
        for( int j = 1; j < destiny.get_length_of_path( i )-1; j++){
            Vertice * v = destiny.get_vertice_in_path( i, j );
            if( j < actual.get_length_of_path( i )-1 ){
                if( actual.rewrite( i, j, v ) ){
                    if( best.get_total_rewards() < actual.get_total_rewards() ){
                        best = actual;
                    }
                }
            }else{
                if( actual.add( i, v ) ){
                    if( best.get_total_rewards() < actual.get_total_rewards() ){
                        best = actual;
                    }
                }
            }
        }
    }
    return best;
}