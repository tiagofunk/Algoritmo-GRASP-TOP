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
#include "OperatorAddVerticeInPath.h"
#include "OperatorSwapBetweenPathAndUnusedvertices.h"
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
    show_log( "seed: " + std::to_string( seed ) + "\n" );
}


void App::read_instance(){
    this->file = this->ar->getValue( "--file" );
    InstanceReader ir( this->file );
    ir.read();
    show_log( "file: " + this->file + "\n" );
}

void App::create_solution_generator(){
    double alpha = stod( this->ar->getValue( "--alpha" ) );
    this->sg = new RandomGreedyGen_MinMax( alpha, 2 );
}

void App::create_operators(){
    this->operators.push_back( new OperatorRandomRemove( 0.5 ) );
    this->operators.push_back( new OperatorRelocate() );
    this->operators.push_back( new OperatorAddVerticeInPath() );
}

void App::create_local_search(){
    this->ls = new LocalSearchWithOperators( this->operators );
}

void App::create_path_relinking(){
    bool path = this->ar->getValue("--path") == "y"? true : false; 
    this->pr = new PathRelinkingOperator( path );
}

void App::create_and_execute_grasp(){
    int iterations = stoi( this->ar->getValue("--iterations") );
    this->grasp = new GRASP( iterations, this->seed, 1.0, this->sg, this->ls, this->pr );
    this->sol = this->grasp->execute();
}

void App::finalize_timer(){
    this->final_time = clock();
	this->total_time = ( (this->final_time - this->initial_time) / (double) CLOCKS_PER_SEC ) * 1000;
}

void App::show_results(){
    show_log( this->sol->to_string() );
    show_log( std::to_string( this->total_time ) + " ms\n" );
    cout << this->sol->get_total_rewards() << endl;
}

App::App( ArgumentReader * ar ){
    this->ar = ar;
    this->sg = 0;
    this->ls = 0;
    this->pr = 0;
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