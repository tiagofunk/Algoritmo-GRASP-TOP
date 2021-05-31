#include "LocalSearchWithOperators.h"

LocalSearchWithOperators::LocalSearchWithOperators():LocalSearch(){
}

LocalSearchWithOperators::~LocalSearchWithOperators(){
}

Solution * LocalSearchWithOperators::execute( Solution * s, vector< Vertice * > vertices ){
    bool is_moved = false;
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    this->unused_vertices = vertices;

    do{
        is_moved = false;
        actual = this->swap_between_path_and_unused_vertices( actual );
        if( best->get_total_rewards() < actual->get_total_rewards() ){
            delete best;
            best = new Solution( *actual );
            is_moved = true;
        }

    }while( is_moved );
    delete actual;
    return best;
}

vector< Vertice * > LocalSearchWithOperators::get_unused_vertices(){
    return this->unused_vertices;
}

Solution * LocalSearchWithOperators::swap_between_path_and_unused_vertices( Solution * s ){
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    for( int i = 0; i < s->get_number_paths(); i++){
        for (int j = 1; j < s->get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                if( actual->rewrite_vertice( i, j, this->unused_vertices[ k ] ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        delete best;
                        best = new Solution( *actual );
                        this->unused_vertices.erase( this->unused_vertices.begin() + k );
                    }
                    delete actual;
                    actual = new Solution( *s );
                }
            }
        }
    }
    
    return best;
}