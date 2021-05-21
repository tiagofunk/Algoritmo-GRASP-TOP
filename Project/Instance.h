#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

#include "Point.h"

class Instance {
private:
    int number_of_vertices;
    int number_of_paths;
    double time_per_path;
    std::vector< Point > list_of_points;

public:
    Instance(int number_of_vertices, int number_of_paths, double time_per_path);
    ~Instance();

    int get_number_of_vertices();
    int get_number_of_paths();
    double get_time_per_path();

    void add_point( Point p );
    Point get_point( int position );
    std::vector< Point > get_points();
    double * get_scores();

    std::string to_string();
};

#endif