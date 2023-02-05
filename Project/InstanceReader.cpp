#include "InstanceReader.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

InstanceReader::InstanceReader( string file_name ){
    this->file_name = file_name;
}

InstanceReader::~InstanceReader(){
}

void InstanceReader::read(){
    int vertices, paths, reward;
    double time, x, y;
    string aux;
    Vertice * p = 0;

    ifstream file( this->file_name.c_str(), ios::in );
    if( !file ){
        throw runtime_error( "Error on open file: " + this->file_name );
    }

    file >> aux;
    file >> vertices;

    file >> aux;
    file >> paths;

    file >> aux;
    file >> time;

    Instance * inst = Instance::instance();
    inst->set_number_of_vertices( vertices );
    inst->set_number_of_paths( paths );
    inst->set_time_per_path( time );

    for( int i = 0; i < vertices; i++ ){
        file >> x;
        file >> y;
        file >> reward;
        p = new Vertice( x, y, reward );
        inst->add_point( p );
    }

    file.close();
}