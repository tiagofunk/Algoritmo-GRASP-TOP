#include "OperatorWorstRemove.h"
#include "Utils.h"

#include <iostream>

Solution * OperatorWorstRemove::execute( Solution * sol, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    Solution * actual = new Solution( *sol );
    bool is_empty = true;
    double worst_reward = 0.0;
    double worst_distance = 0.0;
    int worst_path = 0;
    int worst_position = 1;
    for( int i = 0; i < actual->get_number_paths(); i++ ){
        if( actual->get_length_of_path( i ) != 2 ){
            worst_reward = actual->get_vertice_in_path( i, 1 )->get_reward();
            worst_distance = actual->get_distance( 0, 1 );
            worst_path = i;
            is_empty = false;
            break;
        }
    }
    if( is_empty ){
        delete sol;
        return actual;
    }
    Vertice * v = 0;
    for( int i = 0; i < actual->get_number_paths(); i++ ){
        for( int j = 1; j < actual->get_length_of_path( i ) - 1; j++ ){
            double d = actual->get_distance( i, j );
            v = actual->get_vertice_in_path( i, j );
            if( worst_reward > v->get_reward() ){
                worst_path = i;
                worst_position = j;
                worst_reward = v->get_reward();
                worst_distance = d;
                cout << "trocou 1" << endl;
            }else if( worst_reward == v->get_reward() ){
                if( worst_distance > d ){
                    worst_path = i;
                    worst_position = j;
                    worst_reward = v->get_reward();
                    worst_distance = d;
                    cout << "trocou 2" << endl;
                }
            }
        }
    }
    v = actual->get_vertice_in_path( worst_path, worst_position );
    actual->remove( worst_path, worst_position );
    this->unused_vertices.push_back( v );
    cout << "fim" << endl;
    delete sol;
    return actual;
}