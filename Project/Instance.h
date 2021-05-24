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
    std::vector< Vertice * > list_of_path_vertices;
    Vertice * initial;
    Vertice * final;

public:
    Instance(int number_of_vertices, int number_of_paths, double time_per_path);
    ~Instance();

    int get_number_of_vertices();
    int get_number_of_null_vertices();
    int get_number_of_path_vertices();
    int get_number_of_paths();
    double get_time_per_path();

    void add_point( Vertice * p );
    Vertice * get_path_vertice( int position );
    vector< Vertice * > get_path_vertices();

    Vertice * get_initial_vertice();
    Vertice * get_final_vertice();

    std::string to_string();
};

#endif