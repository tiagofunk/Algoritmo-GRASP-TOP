#ifndef SOLUTION_H
#define SOLUTION_H

#include "Vertice.h"

#include <vector>
#include <string>

using namespace std;

class Solution{
    private:
        vector< vector< Vertice * > > paths;
        vector< double > path_rewards;
        vector< double > path_times;
        double total_rewards;

        bool is_calculate_rewards;
        bool is_calculate_time_per_path;

        double time_per_path;

        void calculate_total_rewards();
        void calculate_time_per_paths();

    public:
        Solution( int number_paths, double time_per_path );
        bool add_initial_vertice( int path, Vertice * v );
        bool add_final_vertice( int path, Vertice * v );
        bool add_vertice( int path, Vertice * v );

        Vertice * get_last_path_vertice_in_path( int path );
        double get_total_rewards();

        string to_string();
};

#endif