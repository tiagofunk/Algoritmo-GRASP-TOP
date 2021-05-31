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

        double time_per_path;

        void update_reward_in_add( int path, int position, Vertice * v );

        double calculate_time_in_add( int path, int position, Vertice * v );

    public:
        Solution( int number_paths, double time_per_path );
        bool add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final );
        
        bool add_vertice( int path, Vertice * v );

        Vertice * get_last_path_vertice_in_path( int path );
        double get_total_rewards();

        string to_string();
};

#endif