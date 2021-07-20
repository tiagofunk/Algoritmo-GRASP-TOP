#include "Instance.h"

Instance * Instance::_instance = 0;

Instance::Instance(){
    this->number_of_vertices = 0;
    this->number_of_null_vertices = 0;
    this->number_of_path_vertices = 0;
    this->number_of_paths = 0;
    this->time_per_path = 0.0;
    this->initial = 0;
    this->final = 0;
}

Instance * Instance::instance(){
    if( Instance::_instance == 0 ){
        Instance::_instance = new Instance();
    }
    return Instance::_instance;
}

void Instance::set_number_of_vertices( int number_of_vertices ){
    this->number_of_vertices = number_of_vertices;
}

void Instance::set_number_of_paths( int number_of_paths ){
    this->number_of_paths = number_of_paths;
}

void Instance::set_time_per_path( double time_per_path ){
    this->time_per_path = time_per_path;
}

void Instance::add_point( Vertice * p ){
    if( p->get_reward() == 0 ){
        this->number_of_null_vertices++;

        if( this->initial == NULL ){
            this->initial = p;
        } else if( this->initial != NULL ){
            this->final = p;
        }
    }else{
        this->number_of_path_vertices++;
        this->list_of_path_vertices.push_back( p );
    }
}

int Instance::get_number_of_vertices(){
    return this->number_of_vertices;
}

int Instance::get_number_of_null_vertices(){
    return this->number_of_null_vertices;
}

int Instance::get_number_of_path_vertices(){
    return this->number_of_path_vertices; 
}

int Instance::get_number_of_paths(){
    return this->number_of_paths;
}

double Instance::get_time_per_path(){
    return this->time_per_path;
}

Vertice * Instance::get_path_vertice( int position ){
    return this->list_of_path_vertices[ position ];
}

vector< Vertice * > Instance::get_path_vertices(){
    return this->list_of_path_vertices;
}

Vertice * Instance::get_initial_vertice(){
    return initial;
}

Vertice * Instance::get_final_vertice(){
    return final;
}

std::string Instance::to_string(){
    std::string s;
    s = "Vertices: " + std::to_string( this->number_of_vertices ) + "\n";
    s += "Paths: " + std::to_string( this->number_of_paths ) + "\n";
    s += "Time: " + std::to_string( this->time_per_path ) + "\n";
    s += "Points:\n";
    for( unsigned int i = 0; i < this->list_of_path_vertices.size(); i++ ){
        s += this->list_of_path_vertices[ i ]->to_string() + "\n";
    }
    return s;
}