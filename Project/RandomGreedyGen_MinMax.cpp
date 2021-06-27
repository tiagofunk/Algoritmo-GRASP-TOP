#include "RandomGreedyGen_MinMax.h"

#include "Utils.h"

RandomGreedyGen_MinMax::RandomGreedyGen_MinMax( double alpha, int number_of_paths, double time_per_path ):SolutionGeneration(){
    this->number_of_paths = number_of_paths;
    this->alpha = alpha;
    this->time_per_path = time_per_path;
}

Solution * RandomGreedyGen_MinMax::random_greedy_generation( Vertice * initial, Vertice * final, vector< Vertice * > vertices ){
    bool is_added = false;
    Solution * sol = new Solution( this->number_of_paths, this->time_per_path );
    this->unused_vertices.clear();
    this->unused_vertices = vertices;
    
    for( int i = 0; i < this->number_of_paths; i++ ){
        sol->add_initial_and_final_vertice( i, initial, final );
    }

    do{
        is_added = false;
        for( int i = 0; i < this->number_of_paths; i++ ){
            int selected = select_vertice( calcule_probability( sol->get_last_path_vertice_in_path( i ), this->unused_vertices ) );
            if( selected == -1 ) break;
            Vertice * selected_vertice = this->unused_vertices[ selected ]; 
            if( sol->add_vertice( i, selected_vertice ) ){
                is_added = true;
                this->unused_vertices.erase( this->unused_vertices.begin() + selected );
            }
        }
    }while( is_added );

    return sol;
}

vector< Vertice * > RandomGreedyGen_MinMax::get_unused_vertices(){
    return this->unused_vertices;
}

vector< double > RandomGreedyGen_MinMax::get_scores( vector< Vertice * > vertices ){
    vector< double > scores;
    for( unsigned int i = 0; i < vertices.size(); i++ ){
        scores.push_back( vertices[ i ]->get_reward() );
    }
    return scores;
}

vector< RandomGreedyGen_MinMax::score_point > RandomGreedyGen_MinMax::calcule_probability( Vertice * actual, vector< Vertice * > vertices ){
    double min_reward = 0.0, max_reward = 0.0;
    double min_distance = 0.0, max_distance = 0.0;
    double sum_values = 0.0;
    unsigned int n_vertices = vertices.size();
    vector< RandomGreedyGen_MinMax::score_point > sp( n_vertices );
    
    if( vertices.empty() ) return sp;

    for( unsigned int i = 0; i < vertices.size(); i++ ){
        if( i == 0 ){
            min_reward = vertices[ i ]->get_reward();
            max_reward = vertices[ i ]->get_reward();
        } else if( min_reward > vertices[ i ]->get_reward() ){
            min_reward = vertices[ i ]->get_reward();
        } else if( max_reward < vertices[ i ]->get_reward() ){
            max_reward = vertices[ i ]->get_reward();
        }
    }
    
    for( unsigned int i = 0; i < n_vertices; i++ ){
        Vertice * v = vertices[ i ];
        sp[ i ].p = v;
        sp[ i ].score_reward = this->calcule_score( v->get_reward(), min_reward, max_reward );
        sp[ i ].distance = calculate_distance( actual, v );
    }

    for( unsigned int i = 0; i < vertices.size(); i++ ){
        if( i == 0 ){
            min_distance = sp[ i ].distance;
            max_distance = sp[ i ].distance;
        } else if( min_distance > sp[ i ].distance ){
            min_distance = sp[ i ].distance;
        } else if( max_distance < sp[ i ].distance ){
            max_distance = sp[ i ].distance;
        }
    }

    for( unsigned int i = 0; i < n_vertices; i++ ){
        sp[ i ].score_distance = this->calcule_score( sp[ i ].distance, min_distance, max_distance );
        sp[ i ].value = 1.1 + sp[ i ].score_reward - sp[ i ].score_distance;
        sum_values += sp[ i ].value;
    }

    for( unsigned int i = 0; i < n_vertices; i++ ){
        sp[ i ].probability = sp[ i ].value / sum_values;
    }

    return sp;
}

int RandomGreedyGen_MinMax::select_vertice_greedy( vector< RandomGreedyGen_MinMax::score_point > sp ){
    int selected_position = 0;
    double max = 0.0;
    for( unsigned int i = 0; i < sp.size(); i++ ){
        if( max < sp[ i ].probability ){
            max = sp[ i ].probability;
            selected_position = i;
        }
    }
    return selected_position;
}

int RandomGreedyGen_MinMax::select_vertice_random( vector< RandomGreedyGen_MinMax::score_point > sp ){
    int selected_position = -1;
    double random_number = (double) rand() / RAND_MAX;
    double sum = 0.0;
    for( unsigned int i = 0; i < sp.size(); i++ ){
        sum += sp[ i ].probability;
        if( random_number < sum ){
            selected_position = i;
            break;
        }
    }
    return selected_position;
}

int RandomGreedyGen_MinMax::select_vertice( vector< RandomGreedyGen_MinMax::score_point > sp ){
    if( sp.empty() ) return -1;
    double random_number = (double) rand() / RAND_MAX;
    bool is_greedy = random_number >= this->alpha;
    if( is_greedy ){
        return select_vertice_greedy( sp );
    }
    return select_vertice_random( sp );
}

double RandomGreedyGen_MinMax::calcule_score( double value, double min, double max ){
    return (value - min)/(max - min);
}