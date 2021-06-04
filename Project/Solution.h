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

        void update_reward_in_add( int path, Vertice * v );
        void update_reward_in_rewrite( int path, int position, Vertice * v );

        double calculate_time_in_add( int path, int position, Vertice * v );
        double calculate_time_in_rewrite( int path, int position, Vertice * v );

        bool check_if_vertice_not_used( Vertice * v );

    public:
        Solution( int number_paths, double time_per_path );
        bool add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final );
        
        bool add_vertice( int path, Vertice * v );
        bool add_vertice_in_position( int path, int position, Vertice * v );
        bool rewrite_vertice( int path, int position, Vertice * v );

        Vertice * get_last_path_vertice_in_path( int path );
        Vertice * get_vertice_in_path( int path, int position );
        double get_total_rewards();

        int get_number_paths();
        int get_length_of_path( int path );

        string to_string();
};

#endif