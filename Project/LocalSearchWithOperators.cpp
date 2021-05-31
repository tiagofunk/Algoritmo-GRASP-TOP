#include "LocalSearchWithOperators.h"

LocalSearchWithOperators::LocalSearchWithOperators():LocalSearch(){
}

LocalSearchWithOperators::~LocalSearchWithOperators(){
}

Solution * LocalSearchWithOperators::execute( Solution * s, vector< Vertice * > vertices ){
    bool is_moved = false;
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );

    do{
        is_moved = false;
        actual = this->generate_neighborhood_and_select( actual, vertices );
        if( best->get_total_rewards() < actual->get_total_rewards() ){
            delete best;
            best = new Solution( *actual );
            is_moved = true;
        }

    }while( is_moved );
    delete actual;
    return best;
}

Solution * LocalSearchWithOperators::generate_neighborhood_and_select( Solution * s, vector< Vertice * > vertices ){
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    for( int i = 0; i < s->get_number_paths(); i++){
        for (int j = 1; j < s->get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < vertices.size(); k++ ){
                if( actual->rewrite_vertice( i, j, vertices[ k ] ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        delete best;
                        best = new Solution( *actual );
                    }
                    delete actual;
                    actual = new Solution( *s );
                }
            }
        }
    }
    
    return best;
}