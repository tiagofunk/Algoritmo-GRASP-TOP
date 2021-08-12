#include "OperatorWorstRemove.h"
#include "Utils.h"
#include "main.h"

bool OperatorWorstRemove::check_if_not_empty( Solution sol ){
    for( int i = 0; i < sol.get_number_paths(); i++ ){
        if( sol.get_length_of_path( i ) != 2 ){
            worst_reward = sol.get_vertice_in_path( i, 1 )->get_reward();
            worst_distance = sol.get_distance( 0, 1 );
            worst_path = i;
            return false;
        }
    }
    return true;
}

void OperatorWorstRemove::find_worst( Solution sol ){
    double d = 0.0;
    Vertice * v = 0;
    bool is_better = false;
    for( int i = 0; i < sol.get_number_paths(); i++ ){
        if( sol.get_time_path( i ) > sol.get_time_per_path() ){
            is_better = true;
            d = sol.get_distance( i, 1 );
            v = sol.get_vertice_in_path( i, 1 );
            this->update_worst( v->get_reward(), d, i, 1 );
        }
        for( int j = 1; j < sol.get_length_of_path( i ) - 1; j++ ){
            d = sol.get_distance( i, j );
            v = sol.get_vertice_in_path( i, j );
            if( this->worst_reward > v->get_reward() ){
                this->update_worst( v->get_reward(), d, i, j );

            }else if( this->worst_reward == v->get_reward() ){
                if( this->worst_distance > d ){
                    this->update_worst( v->get_reward(), d, i, j );
                    
                }
            }
        }
        if( is_better ) break;
    }
}

void OperatorWorstRemove::update_worst( double worst_reward, double worst_distance, int worst_path, int worst_position ){
    this->worst_reward = worst_reward;
    this->worst_distance = worst_distance;
    this->worst_path = worst_path;
    this->worst_position = worst_position;
}

Solution OperatorWorstRemove::remove_worst( Solution sol ){
    Vertice * v = sol.get_vertice_in_path( this->worst_path, this->worst_position );
    sol.remove( this->worst_path, this->worst_position );
    this->unused_vertices.push_back( v );
    return sol;
}

Solution OperatorWorstRemove::execute_remove( Solution sol ){
    this->update_worst( 0.0, 0.0, 0, 1 );
    if( this->check_if_not_empty( sol ) ) return sol;
    Solution actual = sol;
    this->find_worst( actual );
    actual = this->remove_worst( actual );
    return actual;
}

OperatorWorstRemove::OperatorWorstRemove( double iterations ){
    this->iterations = iterations;
}

Solution OperatorWorstRemove::execute( Solution sol, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int n = sol.get_total_length_of_path();
    n = n - 2 * sol.get_number_paths();
    if( n != 0 ){
        n = n * this->iterations + 1;
        for( int i = 0; i < n; i++ ){
            sol = this->execute_remove( sol );
        }
        show_log( "number of removes: " + std::to_string( n ) + "\n", 3 );
    }
    return sol;
}