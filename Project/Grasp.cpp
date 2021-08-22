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

Solution GRASP::generate(){
    this->unused_vertices.clear();
    Solution sol = this->solution_generation->random_greedy_generation( Instance::instance()->get_path_vertices() );
    sol.update_time_per_path( Instance::instance()->get_time_per_path() );
    this->unused_vertices = this->solution_generation->get_unused_vertices();
    return sol;
}

bool GRASP::is_acepted( Solution sol ){
    int h = sol.get_hash();
    if( !this->previous_generate_solutions.find( h ) ){
        this->previous_generate_solutions.insert( h );
        return true;
    }
    return false;
}

Solution GRASP::apply_local_search( Solution sol ){
    Solution actual = this->local_search->execute( sol, this->unused_vertices );
    this->unused_vertices = this->local_search->get_unused_vertices();
    return actual;
}

Solution GRASP::apply_path_relinking( Solution sol, Solution best ){
    if( best.get_total_time() != 0.0 ){
        return this->path_relinking->execute( sol, best );
    }
    return sol;
}

bool GRASP::is_better( Solution sol, Solution best ){
    return sol.get_total_rewards() > best.get_total_rewards();
}

Solution GRASP::execute(){
    Solution actual;
    Solution best;
    srand( this->seed );

    show_log( "Iterations:\n", 2);
    for (int i = 0; i < this->iterations; i++){
        show_log( std::to_string( i+1 ) + " of " + std::to_string( this->iterations ) + " " + std::to_string( (int) calcule_percentage( i, this->iterations ) ) + " %\n", 2 );
        
        actual = this->generate();

        if( !is_acepted( actual ) ) continue;

        actual = this->apply_local_search( actual );

        if( this->is_better( actual, best ) ){
            best = actual;
            show_log( std::to_string( i+1 ) + " " + std::to_string( best.get_total_rewards() ) + "\n", 1 );
        }
    }
    show_log( "\n", 2 );
    return best;
}