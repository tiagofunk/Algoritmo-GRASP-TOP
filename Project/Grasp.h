#ifndef GRASP_H
#define GRASP_H

#include "Solution.h"
#include "Instance.h"
#include "LocalSearch.h"
#include "PathRelinking.h"

class GRASP{
    private:
        typedef struct score_point{
            Vertice * p;
            double score_z_score;
            double distance;
            double score_z_distance;
            double value;
            double probability;
        } score_point;

        int iterations;
        int seed;
        double alfa;
        Instance * instance;
        LocalSearch * local_search;
        PathRelinking * path_relinking;

        vector< Vertice * > unused_vertices;

        Solution * random_greedy();

        vector< double > get_scores( vector< Vertice * > vertices );

        vector< score_point > calcule_probability( Vertice * actual, vector< Vertice * > vertices );
        int select_point( vector< score_point > sp );

    public:
        GRASP( int iterations, int seed, double alfa, LocalSearch * local_search, PathRelinking * path_relinking, Instance * instance );
        Solution * execute();
        
};

#endif