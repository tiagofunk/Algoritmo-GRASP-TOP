#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

#include "Point.h"

using namespace std;

class Instance {
private:
    int number_of_vertices;
    int number_of_null_vertices;
    int number_of_paths;
    double time_per_path;
    std::vector< Point * > list_of_points;
    Point * initial;
    Point * final;

public:
    Instance(int number_of_vertices, int number_of_paths, double time_per_path);
    ~Instance();

    int get_number_of_vertices();
    int get_number_of_null_vertices();
    int get_number_of_points();
    int get_number_of_paths();
    double get_time_per_path();

    void add_point( Point * p );
    Point * get_point( int position );
    vector< double > get_scores();

    Point * get_initial_point();
    Point * get_final_point();

    std::string to_string();
};

#endif