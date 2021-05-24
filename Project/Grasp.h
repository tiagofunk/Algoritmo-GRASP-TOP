#ifndef GRASP_H
#define GRASP_H

#include "Solution.h"
#include "Instance.h"

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

        Instance * instance;

        Solution * random_greedy( int seed );
        Solution local_search( Solution s );
        Solution path_relinking( Solution start, Solution end );

        vector< double > get_scores( vector< Vertice * > points );

        vector< score_point > calcule_probability( vector< Vertice * > points );
        int select_point( vector< score_point > sp );

    public:
        GRASP( Instance * instance );
        Solution * execute();
        
};

#endif