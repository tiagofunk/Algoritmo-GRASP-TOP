#include "Grasp.h"

#include <iostream>

GRASP::GRASP( int iterations, int seed, double alfa, SolutionGeneration * solution_generation, LocalSearch * local_search, PathRelinking * path_relinking, Instance * instance ){
    this->iterations = iterations;
    this->seed = seed;
    this->alfa = alfa;
    this->instance = instance;
    this->solution_generation = solution_generation;
    this->local_search = local_search;
    this->path_relinking = path_relinking;
}

Solution * GRASP::execute(){
    Solution * best = 0;
    srand( this->seed );
    for (int i = 0; i < this->iterations; i++){
        this->unused_vertices.clear();
        Solution * actual = this->solution_generation->random_greedy_generation( instance->get_initial_vertice(), instance->get_final_vertice(), instance->get_path_vertices() );
        int h = actual->get_hash();
        if( this->previous_generate_solutions.find( h ) != this->previous_generate_solutions.end() ){
            continue;
        }
        this->previous_generate_solutions.insert( pair< int, Solution >( h, *actual ) );

        this->unused_vertices = this->solution_generation->get_unused_vertices();

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