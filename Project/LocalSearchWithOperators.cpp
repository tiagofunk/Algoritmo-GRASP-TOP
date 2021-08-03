#include "LocalSearchWithOperators.h"
#include "Utils.h"

LocalSearchWithOperators::LocalSearchWithOperators( vector< Operator * > operators ):LocalSearch(){
    this->operators = operators;
}

LocalSearchWithOperators::~LocalSearchWithOperators(){
}

Solution LocalSearchWithOperators::execute( Solution s, vector< Vertice * > vertices ){
    bool is_moved = false;
    bool is_bigger = false;
    Solution best = s;
    Solution actual = s;
    this->unused_vertices = vertices;

    do{
        is_moved = false;
        is_bigger = false;
        for( unsigned int i = 0; i < this->operators.size(); i++ ){
            actual = this->operators[ i ]->execute( actual, this->unused_vertices );
            this->unused_vertices = this->operators[ i ]->get_unused_vertice();
        }
        for( int i = 0; i < actual.get_number_paths(); i++ ){
            is_bigger = is_bigger || absolute( actual.get_time_path( i ), 2 ) > absolute( actual.get_time_per_path(), 2 );
        }
        if( best.get_total_rewards() < actual.get_total_rewards()
                || (is_bigger && absolute( actual.get_total_time(), 2 ) < absolute( best.get_total_time(), 2 ) )
                || (best.get_total_rewards() == actual.get_total_rewards() && absolute( actual.get_total_time(), 2 ) < absolute( best.get_total_time(), 2 ) ) ){
            best = actual;
            is_moved = true;
        }

    }while( is_moved );
    return best;
}

vector< Vertice * > LocalSearchWithOperators::get_unused_vertices(){
    return this->unused_vertices;
}
