#include "Grasp.h"

#include "Utils.h"

#include <iostream>

GRASP::GRASP( Instance * instance ){
    this->instance = instance;
}

Solution GRASP::execute(){
    Solution * s = 0;

    s = this->random_greedy( get_seed() );

    return *s;
}

vector< GRASP::score_point > GRASP::calcule_probability(){
    int vertices = this->instance->get_number_of_points();
    vector< double > scores = this->instance->get_scores();
    double mean = calculate_mean( scores, vertices );
    double stand = calculate_standard_deviation( scores, vertices, mean );
    
    vector< GRASP::score_point > sp( vertices );
    for( int i = 0; i < vertices; i++ ){
        Point * p = this->instance->get_point( i );
        sp[ i ].p = p;
        sp[ i ].score_z_score = calculate_score_z( this->instance->get_point( i )->get_score(), mean, stand );
        sp[ i ].distance = distance( this->instance->get_initial_point(), p );
        scores[ i ] = sp[ i ].distance;
    }

    mean = calculate_mean( scores, vertices );
    stand = calculate_standard_deviation( scores, vertices, mean );
    double sum_values = 0.0;

    for( int i = 0; i < vertices; i++ ){
        sp[ i ].score_z_distance = calculate_score_z( sp[ i ].distance, mean, stand );
        sp[ i ].value = 3 + sp[ i ].score_z_score - sp[ i ].score_z_distance;
        sum_values += sp[ i ].value;
    }

    for( int i = 0; i < vertices; i++ ){
        sp[ i ].probability = sp[ i ].value / sum_values;
        printf(
            "i: %d s: %.2f d: %.2f v: %.2f p: %.2f\n", i,
            sp[ i ].score_z_score,
            sp[ i ].score_z_distance,
            sp[ i ].value,
            sp[ i ].probability
        );
    }

    return sp;
}

GRASP::score_point GRASP::select_point( vector< GRASP::score_point > sp ){
    return sp[ 0 ];
}

Solution * GRASP::random_greedy( int seed ){
    bool is_added = false;
    int i, n_paths = this->instance->get_number_of_paths();
    Solution * sol = new Solution( n_paths );
    
    for( i = 0; i < n_paths; i++ ){
        sol->add_point( i, this->instance->get_initial_point(), true );
        sol->add_point( i, this->instance->get_final_point() , true );
    }

    GRASP::score_point selected = select_point( calcule_probability() );
    sol->add_point( 0, selected.p, false );

    cout << sol->to_string() << endl;

    // do{
    //     for( i = 0; i < n_paths; i++ ){
    //         GRASP::score_point selected = select_point( calcule_probability() );
    //         if( sol->add_point( i, selected.p ) == 0 ){
    //             is_added = true;
    //         }
    //     }
    // }while( is_added );

    return sol;
}

Solution GRASP::local_search( Solution s ){
    return s;
}

Solution GRASP::path_relinking( Solution start, Solution end ){
    return start;
}