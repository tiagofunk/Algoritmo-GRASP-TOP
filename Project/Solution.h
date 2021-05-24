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
        int add_point( int path, Vertice * point, bool end );
        double get_total_rewards();

        string to_string();
};

#endif