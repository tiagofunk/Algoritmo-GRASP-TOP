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

        void calculate_total_rewards();

    public:
        Solution( int number_paths );
        bool add_initial_vertice( int path, Vertice * v );
        bool add_final_vertice( int path, Vertice * v );
        bool add_vertice( int path, Vertice * v );
        double get_total_rewards();

        string to_string();
};

#endif