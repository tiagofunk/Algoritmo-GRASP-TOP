#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

#include "Vertice.h"

using namespace std;

class Instance {
private:
    int number_of_vertices;
    int number_of_null_vertices;
    int number_of_path_vertices;
    int number_of_paths;
    double time_per_path;
    vector< Vertice * > list_of_path_vertices;
    Vertice * initial;
    Vertice * final;

    static Instance * _instance;

protected:
    Instance();

public:
    static Instance * instance();

    void set_number_of_vertices( int number_of_vertices );
    void set_number_of_paths( int number_of_paths );
    void set_time_per_path( double time_per_path );
    void add_point( Vertice * p );

    int get_number_of_vertices();
    int get_number_of_null_vertices();
    int get_number_of_path_vertices();
    int get_number_of_paths();
    double get_time_per_path();
    Vertice * get_path_vertice( int position );
    vector< Vertice * > get_path_vertices();
    Vertice * get_initial_vertice();
    Vertice * get_final_vertice();

    std::string to_string();
};

#endif