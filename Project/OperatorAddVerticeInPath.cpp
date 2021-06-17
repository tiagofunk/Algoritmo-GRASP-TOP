#include "OperatorAddVerticeInPath.h"

Solution * OperatorAddVerticeInPath::execute( Solution * s, vector< Vertice * > uv ){
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    this->unused_vertices = uv;
    for( int i = 0; i < s->get_number_paths(); i++){
        for (int j = 1; j < s->get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                if( actual->add_vertice_in_position( i, j, this->unused_vertices[ k ] ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        delete best;
                        best = new Solution( *actual );
                        this->unused_vertices.erase( this->unused_vertices.begin() + k );
                        delete actual;
                        return best;
                    }
                    delete actual;
                    actual = new Solution( *s );
                }
            }
        }
    }
    return best;
}

vector< Vertice * > OperatorAddVerticeInPath::get_unused_vertice(){
    return this->unused_vertices;
}