#include "LocalSearchWithOperators.h"

LocalSearchWithOperators::LocalSearchWithOperators( vector< Operator * > operators ):LocalSearch(){
    this->operators = operators;
}

LocalSearchWithOperators::~LocalSearchWithOperators(){
}

Solution * LocalSearchWithOperators::execute( Solution * s, vector< Vertice * > vertices ){
    bool is_moved = false;
    bool is_bigger = false;
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    this->unused_vertices = vertices;

    do{
        is_moved = false;
        for( unsigned int i = 0; i < this->operators.size(); i++ ){
            actual = this->operators[ i ]->execute( actual, this->unused_vertices );
            this->unused_vertices = this->operators[ i ]->get_unused_vertice();
        }
        if( best->get_total_rewards() < actual->get_total_rewards()
                || actual->get_total_time() < best->get_total_time() ){
            delete best;
            best = new Solution( *actual );
            is_moved = true;
        }

        if( !is_moved ){
            is_bigger = false;
            for( int i = 0; i < best->get_number_paths(); i++ ){
                is_bigger = is_bigger || best->get_time_path( i ) > best->get_time_per_path();
            }
        }
    }while( is_moved || is_bigger );
    delete actual;
    return best;
}

vector< Vertice * > LocalSearchWithOperators::get_unused_vertices(){
    return this->unused_vertices;
}
