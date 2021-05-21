#include "Solution.h"

void Solution::calculate_total_rewards(){

}

int Solution::addPoint( int route, int point ){
    if( route < 0 || route >= this->routes.size() ){
        this->routes[ route ].push_back( point );
    }
}

double Solution::get_total_rewards(){
    return this->total_rewards;
}