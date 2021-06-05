#include "PathRelinkingOperator.h"

PathRelinkingOperator::PathRelinkingOperator( bool start_to_end ):PathRelinking(){
    this->start_to_end = start_to_end;
}

Solution * PathRelinkingOperator::execute( Solution * start, Solution * end ){
    if( start == NULL && end != NULL ) return end;
    if( start != NULL && end == NULL ) return start;
    if( start == NULL && end == NULL ) return 0; 

    Solution * actual = 0;
    Solution * best = 0;
    Solution * destiny = 0;
    if( this->start_to_end ){
        actual = new Solution( *start );
        best = new Solution( *start );
        destiny = new Solution( *end );
    }else{
        actual = new Solution( *end );
        best = new Solution( *end );
        destiny = new Solution( *start );
    }

    for( int i = 0; i < destiny->get_number_paths(); i++){
        for( int j = 1; j < destiny->get_length_of_path( i )-1; j++){
            if( j < actual->get_length_of_path( i )-1 ){
                if( actual->rewrite_vertice( i, j, destiny->get_vertice_in_path( i, j ) ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        delete best;
                        best = new Solution( *actual );
                    }
                }
            }else{
                if( actual->add_vertice_in_position( i, j, destiny->get_vertice_in_path( i, j ) ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        delete best;
                        best = new Solution( *actual );
                    }
                }
            }
        }
    }
    delete actual;

    return best;
}