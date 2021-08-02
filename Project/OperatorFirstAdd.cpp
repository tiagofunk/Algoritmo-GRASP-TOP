#include "OperatorFirstAdd.h"

#include "Utils.h"

Solution * OperatorFirstAdd::realize_add( Solution * sol ){
    this->is_added = false;
    Solution * best = new Solution( *sol );
    Solution * actual = new Solution( *sol );
    for( int i = 0; i < sol->get_number_paths(); i++){
        for (int j = 1; j < sol->get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                if( actual->add( i, j, this->unused_vertices[ k ] ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        this->is_added = true;
                        delete best;
                        best = new Solution( *actual );
                        this->unused_vertices.erase( this->unused_vertices.begin() + k );
                        delete actual;
                        return best;
                    }
                    delete actual;
                    actual = new Solution( *sol );
                }
            }
        }
    }
    delete sol;
    return best;
}

Solution * OperatorFirstAdd::execute( Solution * s, vector< Vertice * > uv ){
    this->unused_vertices = shuffle_vertices( uv );
    do{
        s = this->realize_add( s );
    }while( is_added );
    return s;
}
