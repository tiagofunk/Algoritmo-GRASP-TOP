#ifndef RANDOM_GREEDY_GEN_SCORE_Z
#define RANDOM_GREEDY_GEN_SCORE_Z

#include "SolutionGeneration.h"

class RandomGreedyGen_ScoreZ: public SolutionGeneration{
    private:
        typedef struct score_point{
            Vertice * p;
            double score_z_score;
            double distance;
            double score_z_distance;
            double value;
            double probability;
        } score_point;

        int number_of_paths;
        double alpha;
        double time_per_path;

        vector< Vertice * > unused_vertices;

        vector< double > get_scores( vector< Vertice * > vertices );

        vector< score_point > calcule_probability( Vertice * actual, vector< Vertice * > vertices );
        int select_point( vector< score_point > sp );

    public:
        RandomGreedyGen_ScoreZ( double alpha, int number_of_paths, double time_per_path );
        virtual Solution * random_greedy_generation( Vertice * initial, Vertice * final, vector< Vertice * > vertices );
        virtual vector< Vertice * > get_unused_vertices();
};

#endif