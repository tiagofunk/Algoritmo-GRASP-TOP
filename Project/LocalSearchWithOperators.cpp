#include "LocalSearchWithOperators.h"
#include "Utils.h"

LocalSearchWithOperators::LocalSearchWithOperators( vector< Operator * > operators ):LocalSearch(){
    this->operators = operators;
}

bool LocalSearchWithOperators::is_better( Solution actual, Solution best ){
    return best.get_total_rewards() < actual.get_total_rewards();
}

bool LocalSearchWithOperators::is_bigger( Solution actual, Solution best ){
    bool is = false;
    for( int i = 0; i < actual.get_number_paths(); i++ ){
        is = is || absolute( actual.get_time_path( i ), 2 ) > absolute( actual.get_time_per_path(), 2 );
    }
    return is && absolute( actual.get_total_time(), 2 ) < absolute( best.get_total_time(), 2 );
}

bool LocalSearchWithOperators::is_shorter( Solution actual, Solution best ){
    bool result = best.get_total_rewards() == actual.get_total_rewards();
    result = result && absolute( actual.get_total_time(), 2 ) < absolute( best.get_total_time(), 2 );
    return  result;
}

Solution LocalSearchWithOperators::execute( Solution s, vector< Vertice * > vertices ){
    bool is_moved = false;
    Solution best = s;
    Solution actual = s;
    this->unused_vertices = vertices;

    do{
        is_moved = false;
        for( unsigned int i = 0; i < this->operators.size(); i++ ){
            actual = this->operators[ i ]->execute( actual, this->unused_vertices );
            this->unused_vertices = this->operators[ i ]->get_unused_vertice();
        }
        if( this->is_better( actual, best ) ){
            best = actual;
            is_moved = true;
        }else if( this->is_bigger( actual, best ) ){
            best = actual;
            is_moved = true;
        }else if( this->is_shorter( actual, best ) ){
            best = actual;
            is_moved = true;
        }

    }while( is_moved );
    return best;
}

vector< Vertice * > LocalSearchWithOperators::get_unused_vertices(){
    return this->unused_vertices;
}
