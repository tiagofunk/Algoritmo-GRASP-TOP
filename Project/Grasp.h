#ifndef GRASP_H
#define GRASP_H

#include "Solution.h"
#include "Instance.h"
#include "SolutionGeneration.h"
#include "LocalSearch.h"
#include "PathRelinking.h"

class GRASP{
    private:
        int iterations;
        int seed;
        double alfa;
        Instance * instance;
        SolutionGeneration * solution_generation;
        LocalSearch * local_search;
        PathRelinking * path_relinking;

        vector< Vertice * > unused_vertices;

        map< int, Solution > previous_generate_solutions;

    public:
        GRASP( int iterations, int seed, double alfa, SolutionGeneration * solution_generation, LocalSearch * local_search, PathRelinking * path_relinking, Instance * instance );
        Solution * execute();
        
};

#endif