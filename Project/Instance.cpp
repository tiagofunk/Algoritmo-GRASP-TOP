#include "Instance.h"

Instance::Instance(int number_of_vertices, int number_of_paths, double time_per_path){
    this->number_of_vertices = number_of_vertices;
    this->number_of_null_vertices = 0;
    this->number_of_paths = number_of_paths;
    this->time_per_path = time_per_path;
    this->initial = 0;
    this->final = 0;
}

Instance::~Instance(){
}

int Instance::get_number_of_vertices(){
    return this->number_of_vertices;
}


int Instance::get_number_of_null_vertices(){
    return this->number_of_null_vertices;
}

int Instance::get_number_of_points(){
    return this->number_of_vertices - this->number_of_null_vertices; 
}

int Instance::get_number_of_paths(){
    return this->number_of_paths;
}

double Instance::get_time_per_path(){
    return this->time_per_path;
}

void Instance::add_point( Point * p ){
    if( p->get_score() == 0 ){
        this->number_of_null_vertices++;

        if( this->initial == NULL ){
            this->initial = p;
        } else if( this->initial != NULL ){
            this->final = p;
        }
    }else{
        this->list_of_points.push_back( p );
    }
}

Point * Instance::get_point( int position ){
    return this->list_of_points[ position ];
}

vector< Point * > Instance::get_points(){
    return this->list_of_points;
}

Point * Instance::get_initial_point(){
    return initial;
}

Point * Instance::get_final_point(){
    return final;
}

std::string Instance::to_string(){
    std::string s;
    s = "Vertices: " + std::to_string( this->number_of_vertices ) + "\n";
    s += "Paths: " + std::to_string( this->number_of_paths ) + "\n";
    s += "Time: " + std::to_string( this->time_per_path ) + "\n";
    s += "Points:\n";
    for( unsigned int i = 0; i < this->list_of_points.size(); i++ ){
        s += this->list_of_points[ i ]->to_string() + "\n";
    }
    return s;
}