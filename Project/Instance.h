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
    int number_of_paths;
    double time_per_path;
    std::vector< Vertice * > list_of_points;
    Vertice * initial;
    Vertice * final;

public:
    Instance(int number_of_vertices, int number_of_paths, double time_per_path);
    ~Instance();

    int get_number_of_vertices();
    int get_number_of_null_vertices();
    int get_number_of_points();
    int get_number_of_paths();
    double get_time_per_path();

    void add_point( Vertice * p );
    Vertice * get_point( int position );
    vector< Vertice * > get_points();

    Vertice * get_initial_point();
    Vertice * get_final_point();

    std::string to_string();
};

#endif