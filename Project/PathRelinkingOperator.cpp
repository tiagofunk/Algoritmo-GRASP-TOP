#include "PathRelinkingOperator.h"

PathRelinkingOperator::PathRelinkingOperator():PathRelinking(){}

Solution * PathRelinkingOperator::execute( Solution * start, Solution * end ){
    if( start == NULL && end != NULL ) return end;
    if( start != NULL && end == NULL ) return start;
    if( start == NULL && end == NULL ) return 0; 

    Solution * actual = new Solution( *start );
    Solution * best = new Solution( *start );

    int a = end->get_number_paths();
    int b = -1;
    for( int i = 0; i < a; i++){
        b = end->get_length_of_path( i );
        for( int j = 1; j < b-1; j++){
            if( actual->rewrite_vertice( i, j, end->get_vertice_in_path( i, j ) ) ){
                if( best->get_total_rewards() < actual->get_total_rewards() ){
                    delete best;
                    best = new Solution( *actual );
                }
            }
        }
    }
    delete actual;

    return best;
}