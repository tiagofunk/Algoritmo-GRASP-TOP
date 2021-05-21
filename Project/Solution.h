#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

using namespace std;

class Solution{
    private:
        vector< vector< int > > routes;
        vector< double > rewards;
        vector< double > times;
        double total_rewards;

        void calculate_total_rewards();

    public:
        int addPoint( int route, int point );

        double get_total_rewards();
};

#endif