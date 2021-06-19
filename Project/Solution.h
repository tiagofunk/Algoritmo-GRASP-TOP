#ifndef SOLUTION_H
#define SOLUTION_H

#include "Vertice.h"
#include "Mapper.h"

#include <vector>
#include <string>

#define SOLUTION_HASH_SIZE 8192

using namespace std;

class Solution{
    private:
        vector< vector< Vertice * > > paths;
        vector< double > path_rewards;
        vector< double > path_times;
        
        double total_rewards;
        double total_time;
        double time_per_path;

        Mapper used_vertices;

        void update_reward_in_add( int path, Vertice * v );
        void update_reward_in_rewrite( int path, int position, Vertice * v );
        void update_reward_in_remove( int path, int position );

        double calculate_time_in_add( int path, int position, Vertice * v );
        double calculate_time_in_rewrite( int path, int position, Vertice * v );
        double calculate_time_in_remove( int path, int position );
        double recalculate_time( int path );

        bool check_if_vertice_is_used( Vertice * v );

        bool check_if_path_is_valid( int path );
        bool check_if_position_is_valid( int path, int position );

    public:
        Solution( int number_paths, double time_per_path );
        bool add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final );
        
        bool add_vertice( int path, Vertice * v );
        bool add_vertice_in_position( int path, int position, Vertice * v );
        bool rewrite_vertice( int path, int position, Vertice * v );
        bool swap( int path, int pos1, int pos2 );
        bool swap( int path1, int pos1, int path2, int pos2 );
        bool remove( int path, int position );

        Vertice * get_last_path_vertice_in_path( int path );
        Vertice * get_vertice_in_path( int path, int position );
        double get_total_rewards();
        double get_time_path( int path );
        double get_total_time();

        int get_number_paths();
        int get_length_of_path( int path );

        string to_string();

        int get_hash();
};

#endif