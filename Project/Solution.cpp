#include "Solution.h"

Solution::Solution( int number_paths ){
    this->paths.resize( number_paths );
    this->path_rewards.resize( number_paths );
    this->path_times.resize( number_paths );
}

void Solution::calculate_total_rewards(){

}

bool Solution::add_initial_vertice( int path, Vertice * v ){
    if( path < 0 || path >= this->paths.size() ){
        return false;
    }
    this->paths[ path ].push_back( v );
    return true;
}

bool Solution::add_final_vertice( int path, Vertice * v ){
    if( path < 0 || path >= this->paths.size() ){
        return false;
    }
    this->paths[ path ].push_back( v );
    return true;
}

bool Solution::add_vertice( int path, Vertice * v ){
    if( path < 0 || path >= this->paths.size() ){
        return 0;
    }
    int position = this->paths[ path ].size() - 1;
    this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
    
    return 1;
}

Vertice * Solution::get_last_path_vertice_in_path( int path ){
    if( path < 0 || path >= this->paths.size() ){
        return 0;
    }
    int last_position = this->paths[ path ].size() - 1;
    return this->paths[ path ][ last_position ];
}

double Solution::get_total_rewards(){
    return this->total_rewards;
}

string Solution::to_string(){
    string s;
    s = "number paths: " + std::to_string(this->paths.size()) + "\n";
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    s += "paths:\n";
    for (int i = 0; i < this->paths.size(); i++){
        s += "size: " + std::to_string( this->paths[ i ].size() ) + "\n" ;
        for (int j = 0; j < this->paths[ i ].size(); j++){
            s += this->paths[ i ][ j ]->to_string() + "\n";
        }
        s += "reward: " + std::to_string( this->path_rewards[ i ])+"\n";
        s += "time: " + std::to_string( this->path_times[ i ])+"\n";
        s += ";D;D;D;D;D;D;D;D;D;D;D;D;D;D;D;D;D;D\n";
    }
    
    return s;
}