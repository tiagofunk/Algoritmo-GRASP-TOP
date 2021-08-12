#include "OperatorBestSwap.h"

#include "Utils.h"
#include "main.h"

Solution OperatorBestSwap::realize_add( Solution sol ){
    this->is_added = false;
    Solution best = sol;
    Solution actual = sol;
    for( int i = 0; i < actual.get_number_paths(); i++){
        for (int j = 1; j < actual.get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                Vertice * old_vertice = actual.get_vertice_in_path( i, j );
                Vertice * new_vertice = this->unused_vertices[ k ];
                if( actual.rewrite( i, j, new_vertice ) ){
                    if( best.get_total_rewards() < actual.get_total_rewards() ){
                        best = actual;
                        this->unused_vertices[ k ] = old_vertice;
                        this->is_added = true;
                    }
                    actual = sol;
                }
            }
        }
    }
    return best;
}

Solution OperatorBestSwap::execute( Solution s, vector< Vertice * > uv ){
    this->unused_vertices = shuffle_vertices( uv );
    int count = 0;
    do{
        s = this->realize_add( s );
        count++;
    }while( this->is_added );
    show_log( "number of swaps: " + std::to_string( count ) + "\n", 3 );
    return s;
}