#include "Grasp.h"

#include "Utils.h"

struct score_point{
    Point *p;
    double score_z_score;
    double distance;
    double score_z_distance;
    double value;
    double probability;
};


GRASP::GRASP( Instance * instance ){
    this->instance = instance;
}

Solution GRASP::execute(){
    Solution * s = 0;

    s = this->random_greedy( get_seed() );

    return *s;
}

Solution * GRASP::random_greedy( int seed ){
    // adicinar em todas as rotas o ponto inicial.
    Solution * sol = new Solution();
    
    int vertices = this->instance->get_points().size();
    vector< double > scores = this->instance->get_scores();
    double mean = calculate_mean( scores, vertices );
    double stand = calculate_standard_deviation( scores, vertices, mean );
    
    vector< struct score_point > sp( vertices );
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

    return sol;
}

Solution GRASP::local_search( Solution s ){
    return s;
}

Solution GRASP::path_relinking( Solution start, Solution end ){
    return start;
}