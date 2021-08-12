#ifndef RANDOM_GREEDY_GEN_MIN_MAX
#define RANDOM_GREEDY_GEN_MIN_MAX

#include "SolutionGeneration.h"

class RandomGreedyGen_MinMax: public SolutionGeneration{
    private:
        typedef struct score_point{
            Vertice * p;
            double score_reward;
            double distance;
            double score_distance;
            double value;
            double probability;
        } score_point;

        int number_of_paths;
        double alpha;
        double margin;
        double time_per_path;

        vector< Vertice * > unused_vertices;

        Solution initialize_solution( int number_of_paths, double time_per_path, Vertice * initial, Vertice * final );
        Solution * remove_excess( Solution * sol );
        double * get_scores( vector< Vertice * > vertices );
        double * get_distances( vector< score_point > sp );

        vector< score_point > calcule_probability( Vertice * actual, vector< Vertice * > vertices );
        int select_vertice_greedy( vector< score_point > sp );
        int select_vertice_random( vector< score_point > sp );
        int select_vertice( vector< score_point > sp );
        double calcule_score( double value, double min, double max );

    public:
        RandomGreedyGen_MinMax( double alpha, double margin );
        virtual Solution random_greedy_generation( vector< Vertice * > vertices );
        virtual vector< Vertice * > get_unused_vertices();
};

#endif