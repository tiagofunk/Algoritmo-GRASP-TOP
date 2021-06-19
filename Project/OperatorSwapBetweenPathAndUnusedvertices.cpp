#include "OperatorSwapBetweenPathAndUnusedvertices.h"

Solution * OperatorSwapBetweenPathAndUnusedvertices::execute( Solution * s, vector< Vertice * > uv ){
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    this->unused_vertices = uv;
    for( int i = 0; i < s->get_number_paths(); i++){
        for (int j = 1; j < s->get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                Vertice * old_v = actual->get_vertice_in_path( i, j );
                Vertice * new_v = this->unused_vertices[ k ];
                if( actual->rewrite_vertice( i, j, new_v ) ){
                    if( best->get_total_rewards() < actual->get_total_rewards() ){
                        delete best;
                        best = new Solution( *actual );
                        this->unused_vertices[ k ] = old_v;
                        delete actual;
                        return best;
                    }
                    delete actual;
                    actual = new Solution( *s );
                }
            }
        }
    }
    delete s;
    return best;
}