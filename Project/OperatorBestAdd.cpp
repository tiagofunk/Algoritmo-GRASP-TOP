#include "OperatorBestAdd.h"

#include "Utils.h"
#include "main.h"

Solution OperatorBestAdd::realize_add( Solution sol ){
    this->is_added = false;
    int vertice_position = -1;
    Solution best( sol );
    Solution actual( sol );
    for( int i = 0; i < sol.get_number_paths(); i++){
        for (int j = 1; j < sol.get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                if( actual.add( i, j, this->unused_vertices[ k ] ) ){
                    if( best.get_total_rewards() < actual.get_total_rewards() ){
                        this->is_added = true;
                        vertice_position = k;
                        best = actual;
                    }
                    actual = sol;
                }
            }
        }
    }
    if( vertice_position != -1 ){
        this->unused_vertices.erase( this->unused_vertices.begin() + vertice_position );
    }
    return best;
}

Solution OperatorBestAdd::execute( Solution sol, vector< Vertice * > uv ){
    this->unused_vertices = shuffle_vertices( uv );
    int count = 0;
    do{
        sol = this->realize_add( sol );
        count++;
    }while( is_added );
    show_log( "number of insertions: " + std::to_string( count ) + "\n", 3 );
    return sol;
}
