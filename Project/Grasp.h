#ifndef GRASP_H
#define GRASP_H

#include "Solution.h"
#include "Instance.h"
#include "SolutionGeneration.h"
#include "LocalSearch.h"
#include "PathRelinking.h"
#include "Mapper.h"

class GRASP{
    private:
        int iterations;
        int seed;
        SolutionGeneration * solution_generation;
        LocalSearch * local_search;
        PathRelinking * path_relinking;

        vector< Vertice * > unused_vertices;
        Mapper previous_generate_solutions;

        Solution generate();
        bool is_acepted( Solution sol );
        Solution apply_local_search( Solution sol );
        Solution apply_path_relinking( Solution sol, Solution best );
        bool is_better( Solution sol, Solution best );

    public:
        GRASP( int iterations, int seed, SolutionGeneration * solution_generation, LocalSearch * local_search, PathRelinking * path_relinking );
        Solution execute();
        
};

#endif