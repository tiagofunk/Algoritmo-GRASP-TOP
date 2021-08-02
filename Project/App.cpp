#include "App.h"

#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "RandomGreedyGen_MinMax.h"
#include "LocalSearchWithOperators.h"
#include "PathRelinkingOperator.h"
#include "ArgumentReader.h"
#include "Operator.h"
#include "OperatorSwapIntoRoute.h"
#include "OperatorFirstAdd.h"
#include "OperatorRamdomAdd.h"
#include "OperatorBestSwap.h"
#include "Operator2opt.h"
#include "OperatorExchange.h"
#include "OperatorRandomRemove.h"
#include "OperatorWorstRemove.h"
#include "OperatorRelocate.h"

#include <iostream>
#include <map>
#include <random>

using namespace std;

void App::initialize_timer(){
    this->initial_time = clock();
}

void App::create_seed(){
    random_device rd;
    this->seed = rd();
    show_log( "seed: " + std::to_string( seed ) + "\n", 1 );
}


void App::read_instance(){
    this->file = this->argument_reader->getValue( "--file" );
    InstanceReader ir( this->file );
    ir.read();
    show_log( "file: " + this->file + "\n", 1 );
}

void App::create_solution_generator(){
    double alpha = stod( this->argument_reader->getValue( "--alpha" ) );
    this->solution_generator = new RandomGreedyGen_MinMax( alpha, 2 );
}

void App::create_operators(){
    this->operators.push_back( new OperatorRandomRemove( 0.5 ) );
    this->operators.push_back( new OperatorRelocate() );
    this->operators.push_back( new OperatorFirstAdd() );
    this->operators.push_back( new OperatorBestSwap() );
}

void App::create_local_search(){
    this->local_search = new LocalSearchWithOperators( this->operators );
}

void App::create_path_relinking(){
    bool path = this->argument_reader->getValue("--path") == "y"? true : false; 
    this->path_relinking = new PathRelinkingOperator( path );
}

void App::create_and_execute_grasp(){
    int iterations = stoi( this->argument_reader->getValue("--iterations") );
    this->grasp = new GRASP( iterations, this->seed, this->solution_generator, this->local_search, this->path_relinking );
    this->sol = this->grasp->execute();
}

void App::finalize_timer(){
    this->final_time = clock();
	this->total_time = ( (this->final_time - this->initial_time) / (double) CLOCKS_PER_SEC ) * 1000;
}

void App::show_results(){
    show_log( this->sol->to_string(), 1 );
    show_log( std::to_string( this->total_time ) + " ms\n", 1 );
    show_log( std::to_string( IRACE_CONSTANT * this->sol->get_total_rewards() ) + "\n", 0 );
}

App::App( ArgumentReader * ar ){
    this->argument_reader = ar;
    this->solution_generator = 0;
    this->local_search = 0;
    this->path_relinking = 0;
    this->grasp = 0;
    this->initial_time = 0;
    this->final_time = 0;
}

void App::execute(){
    this->initialize_timer();
    this->create_seed();
    this->read_instance();
    this->create_solution_generator();
    this->create_operators();
    this->create_local_search();
    this->create_path_relinking();
    this->create_and_execute_grasp();
    this->finalize_timer();
    this->show_results();
}