#include "Grasp.h"
#include "main.h"
#include "Utils.h"

GRASP::GRASP( int iterations, int seed, SolutionGeneration * solution_generation, LocalSearch * local_search, PathRelinking * path_relinking ){
    this->iterations = iterations;
    this->seed = seed;
    this->solution_generation = solution_generation;
    this->local_search = local_search;
    this->path_relinking = path_relinking;
    this->previous_generate_solutions.resize( SOLUTION_HASH_SIZE );
}

Solution GRASP::execute(){
    int h = -1;
    Solution actual;
    Solution best;
    srand( this->seed );

    show_log( "Iterations:\n", 1);
    for (int i = 0; i < this->iterations; i++){
        show_log( std::to_string( i+1 ) + " of " + std::to_string( this->iterations ) +
            " " + std::to_string( calcule_percentage( i, this->iterations ) ) + " %\n", 1 );
        this->unused_vertices.clear();
        actual = this->solution_generation->random_greedy_generation( Instance::instance()->get_path_vertices() );
        actual.lock_checker();
        
        h = actual.get_hash();
        if( !this->previous_generate_solutions.find( h ) ){
            this->previous_generate_solutions.insert( h );

            this->unused_vertices = this->solution_generation->get_unused_vertices();

            actual = this->local_search->execute( actual, this->unused_vertices );
            this->unused_vertices = this->local_search->get_unused_vertices();

            actual = this->path_relinking->execute( actual, best );

            if( actual.get_total_rewards() > best.get_total_rewards() ){
                best = actual;
            }
        }
    }
    show_log( "\n", 1 );
    return best;
}