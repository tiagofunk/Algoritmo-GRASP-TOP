#include "Grasp.h"

#include "Utils.h"

#include <iostream>

GRASP::GRASP( int iterations, int seed, double alfa, LocalSearch * local_search, PathRelinking * path_relinking, Instance * instance ){
    this->iterations = iterations;
    this->seed = seed;
    this->alfa = alfa;
    this->instance = instance;
    this->local_search = local_search;
    this->path_relinking = path_relinking;
}

Solution * GRASP::execute(){
    Solution * best = 0;
    srand( this->seed );

    for (int i = 0; i < this->iterations; i++){
        this->unused_vertices.clear();
        Solution * actual = this->random_greedy();

        actual = this->local_search->execute( actual, this->unused_vertices );
        this->unused_vertices = this->local_search->get_unused_vertices();

        actual = this->path_relinking->execute( actual, best );

        if( best == NULL || actual->get_total_rewards() > best->get_total_rewards() ){
            best = new Solution( *actual );
        }
        delete actual;
    }

    return best;
}

vector< double > GRASP::get_scores( vector< Vertice * > vertices ){
    vector< double > scores;
    for( unsigned int i = 0; i < vertices.size(); i++ ){
        scores.push_back( vertices[ i ]->get_reward() );
    }
    return scores;
}

vector< GRASP::score_point > GRASP::calcule_probability( Vertice * actual, vector< Vertice * > vertices ){
    unsigned int i = 0;
    unsigned int n_vertices = vertices.size();
    vector< GRASP::score_point > sp( n_vertices );
    if( vertices.empty() ) return sp;

    vector< double > scores = this->get_scores( vertices );
    double mean = calculate_mean( scores, n_vertices );
    double stand = calculate_standard_deviation( scores, n_vertices, mean );
    
    for( i = 0; i < n_vertices; i++ ){
        Vertice * v = vertices[ i ];
        sp[ i ].p = v;
        sp[ i ].score_z_score = calculate_score_z( scores[ i ], mean, stand );
        sp[ i ].distance = calculate_distance( actual, v );
        scores[ i ] = sp[ i ].distance;
    }

    mean = calculate_mean( scores, n_vertices );
    stand = calculate_standard_deviation( scores, n_vertices, mean );
    double sum_values = 0.0;

    for( i = 0; i < n_vertices; i++ ){
        sp[ i ].score_z_distance = calculate_score_z( sp[ i ].distance, mean, stand );
        sp[ i ].value = 3 + sp[ i ].score_z_score - sp[ i ].score_z_distance;
        sum_values += sp[ i ].value;
    }

    for( i = 0; i < n_vertices; i++ ){
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

int GRASP::select_point( vector< GRASP::score_point > sp ){
    if( sp.empty() ) return -1;

    int selected_position = 0;
    double r1 = (double) rand() / RAND_MAX;
    double r2 = (double) rand() / RAND_MAX;
    double sum = 0.0, max = 0.0;
    bool is_greedy = r2 >= this->alfa;
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

Solution * GRASP::random_greedy(){
    bool is_added = false;
    int i, n_paths = this->instance->get_number_of_paths();
    Solution * sol = new Solution( n_paths, this->instance->get_time_per_path() );
    this->unused_vertices = this->instance->get_path_vertices();
    
    for( i = 0; i < n_paths; i++ ){
        sol->add_initial_and_final_vertice(
            i,
            this->instance->get_initial_vertice(),
            this->instance->get_final_vertice()
        );
    }

    do{
        is_added = false;
        for( i = 0; i < n_paths; i++ ){
            int selected = select_point( calcule_probability( sol->get_last_path_vertice_in_path( i ), this->unused_vertices ) );
            if( selected == -1 ) break;
            Vertice * selected_vertice = this->unused_vertices[ selected ]; 
            if( sol->add_vertice( i, selected_vertice ) == true ){
                is_added = true;
                this->unused_vertices.erase( this->unused_vertices.begin() + selected );
            }
        }
    }while( is_added );

    return sol;
}