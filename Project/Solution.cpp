#include "Solution.h"

#include "Utils.h"

Solution::Solution( int number_paths, double time_per_path ){
    this->paths.resize( number_paths );
    this->path_rewards.resize( number_paths );
    this->path_times.resize( number_paths );
    this->is_calculate_rewards = false;
    this->is_calculate_time_per_path = false;
    this->time_per_path = time_per_path;
}

void Solution::calculate_total_rewards(){
    if( this->is_calculate_rewards ) return;
    this->total_rewards = 0.0;
    for (size_t i = 0; i < this->paths.size(); i++){
        this->path_rewards[ i ] = 0.0;
        for (size_t j = 0; j < this->paths[ i ].size(); j++){
            this->path_rewards[ i ] += this->paths[ i ][ j ]->get_score();
        }
        this->total_rewards += this->path_rewards[ i ];
    }
    this->is_calculate_rewards = true;
}

void Solution::calculate_time_per_paths(){
    if( this->is_calculate_time_per_path ) return;
    for (size_t i = 0; i < this->paths.size(); i++){
        this->path_times[ i ] = 0.0;
        for (size_t j = 1; j < this->paths[ i ].size(); j++){
            this->path_times[ i ] += calculate_distance( this->paths[ i ][ j-1 ], this->paths[ i ][ j ] );
        }
        
    }
    this->is_calculate_time_per_path = true;
}

bool Solution::add_initial_vertice( int path, Vertice * v ){
    if( path < 0 || path >= this->paths.size() ){
        return false;
    }
    this->is_calculate_rewards = false;
    this->is_calculate_time_per_path = false;
    this->paths[ path ].push_back( v );
    return true;
}

bool Solution::add_final_vertice( int path, Vertice * v ){
    if( path < 0 || path >= this->paths.size() ){
        return false;
    }
    this->is_calculate_rewards = false;
    this->is_calculate_time_per_path = false;
    this->paths[ path ].push_back( v );
    return true;
}

bool Solution::add_vertice( int path, Vertice * v ){
    if( path < 0 || path >= this->paths.size() ){
        return false;
    }
    this->is_calculate_rewards = false;
    this->is_calculate_time_per_path = false;
    int position = this->paths[ path ].size() - 1;
    this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
    calculate_time_per_paths();
    if( this->path_times[ path ] > this->time_per_path ){
        this->paths[ path ].erase( this->paths[ path ].begin() + position );
        return false;
    }
    this->is_calculate_rewards = false;
    this->is_calculate_time_per_path = false;
    
    return true;
}

Vertice * Solution::get_last_path_vertice_in_path( int path ){
    if( path < 0 || path >= this->paths.size() ){
        return 0;
    }
    int last_position = this->paths[ path ].size() - 1;
    return this->paths[ path ][ last_position ];
}

double Solution::get_total_rewards(){
    calculate_total_rewards();
    return this->total_rewards;
}

string Solution::to_string(){
    calculate_total_rewards();
    calculate_time_per_paths();
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
        s += ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    }
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    
    return s;
}