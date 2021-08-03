#ifndef SOLUTION_GENERATION_H
#define SOLUTION_GENERATION_H

#include <vector>
#include "Solution.h"
#include "Vertice.h"
#include "Instance.h"

class SolutionGeneration {
    public:
        SolutionGeneration(){}

        virtual Solution random_greedy_generation( vector< Vertice * > vertices ) = 0;
        virtual vector< Vertice * > get_unused_vertices() = 0;
};

#endif