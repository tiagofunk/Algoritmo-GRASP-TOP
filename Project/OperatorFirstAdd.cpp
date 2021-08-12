#include "OperatorFirstAdd.h"

#include "Utils.h"
#include "main.h"

Solution OperatorFirstAdd::realize_add( Solution sol ){
    this->is_added = false;
    Solution best = sol;
    Solution actual = sol;
    for( int i = 0; i < sol.get_number_paths(); i++){
        for (int j = 1; j < sol.get_length_of_path( i )-1; j++){
            for(unsigned int k = 0; k < this->unused_vertices.size(); k++ ){
                if( actual.add( i, j, this->unused_vertices[ k ] ) ){
                    if( best.get_total_rewards() < actual.get_total_rewards() ){
                        this->is_added = true;
                        best = actual;
                        this->unused_vertices.erase( this->unused_vertices.begin() + k );
                        return best;
                    }
                    actual = sol;
                }
            }
        }
    }
    return best;
}

Solution OperatorFirstAdd::execute( Solution s, vector< Vertice * > uv ){
    this->unused_vertices = shuffle_vertices( uv );
    int count = 0;
    do{
        s = this->realize_add( s );
        count++;
    }while( is_added );
    show_log( "number of insertions: " + std::to_string( count ) + "\n", 3 );
    return s;
}
