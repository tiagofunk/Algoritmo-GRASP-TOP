#include "RandomGreedyGen_ScoreZ.h"

#include "Utils.h"

RandomGreedyGen_ScoreZ::RandomGreedyGen_ScoreZ( double alpha, int number_of_paths, double time_per_path ):SolutionGeneration(){
    this->number_of_paths = number_of_paths;
    this->alpha = alpha;
    this->time_per_path = time_per_path;
}

Solution * RandomGreedyGen_ScoreZ::random_greedy_generation( Vertice * initial, Vertice * final, vector< Vertice * > vertices ){
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
            if( sol->add_vertice( i, selected_vertice, false ) ){
                is_added = true;
                this->unused_vertices.erase( this->unused_vertices.begin() + selected );
            }
        }
    }while( is_added );

    return sol;
}

vector< Vertice * > RandomGreedyGen_ScoreZ::get_unused_vertices(){
    return this->unused_vertices;
}

vector< double > RandomGreedyGen_ScoreZ::get_scores( vector< Vertice * > vertices ){
    vector< double > scores;
    for( unsigned int i = 0; i < vertices.size(); i++ ){
        scores.push_back( vertices[ i ]->get_reward() );
    }
    return scores;
}

vector< RandomGreedyGen_ScoreZ::score_point > RandomGreedyGen_ScoreZ::calcule_probability( Vertice * actual, vector< Vertice * > vertices ){
    unsigned int n_vertices = vertices.size();
    vector< RandomGreedyGen_ScoreZ::score_point > sp( n_vertices );
    if( vertices.empty() ) return sp;

    vector< double > scores = this->get_scores( vertices );
    double mean = calculate_mean( scores, n_vertices );
    double stand = calculate_standard_deviation( scores, n_vertices, mean );
    
    for( unsigned int i = 0; i < n_vertices; i++ ){
        Vertice * v = vertices[ i ];
        sp[ i ].p = v;
        sp[ i ].score_z_score = calculate_score_z( scores[ i ], mean, stand );
        sp[ i ].distance = calculate_distance( actual, v );
        scores[ i ] = sp[ i ].distance;
    }

    mean = calculate_mean( scores, n_vertices );
    stand = calculate_standard_deviation( scores, n_vertices, mean );
    double sum_values = 0.0;

    for( unsigned int i = 0; i < n_vertices; i++ ){
        sp[ i ].score_z_distance = calculate_score_z( sp[ i ].distance, mean, stand );
        sp[ i ].value = 3 + sp[ i ].score_z_score - sp[ i ].score_z_distance;
        sum_values += sp[ i ].value;
    }

    for( unsigned int i = 0; i < n_vertices; i++ ){
        sp[ i ].probability = sp[ i ].value / sum_values;
        // printf(
        //     "i: %d s: %.2f d: %.2f v: %.2f p: %.2f\n", i,
        //     sp[ i ].score_z_score,
        //     sp[ i ].score_z_distance,
        //     sp[ i ].value,
        //     sp[ i ].probability
        // );
    }

    return sp;
}

int RandomGreedyGen_ScoreZ::select_vertice( vector< RandomGreedyGen_ScoreZ::score_point > sp ){
    if( sp.empty() ) return -1;

    int selected_position = 0;
    double r1 = (double) rand() / RAND_MAX;
    double r2 = (double) rand() / RAND_MAX;
    double sum = 0.0, max = 0.0;
    bool is_greedy = r2 >= this->alpha;
    for( unsigned int i = 0; i < sp.size(); i++ ){
        sum += sp[ i ].probability;
        if( !is_greedy && r1 < sum ){
            selected_position = i;
            break;
        }else if( is_greedy && max < sp[ i ].probability ){
            max = sp[ i ].probability;
            selected_position = i;
        }
    }
    return selected_position;
}
