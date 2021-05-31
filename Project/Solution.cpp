#include "Solution.h"

#include "Utils.h"

Solution::Solution( int number_paths, double time_per_path ){
    this->paths.resize( number_paths );
    this->path_rewards.resize( number_paths );
    this->path_times.resize( number_paths );
    this->time_per_path = time_per_path;
    this->total_rewards = 0.0;
}

void Solution::update_reward_in_add( int path, Vertice * v ){
    this->path_rewards[ path ] += v->get_reward();
    this->total_rewards += v->get_reward();
}

void Solution::update_reward_in_rewrite( int path, int position, Vertice * v ){
    Vertice * to_remove = this->paths[ path ][ position ];
    this->path_rewards[ path ] -= to_remove->get_reward();
    this->total_rewards -= to_remove->get_reward();
    this->path_rewards[ path ] += v->get_reward();
    this->total_rewards += v->get_reward();
}

double Solution::calculate_time_in_add( int path, int position, Vertice * v ){
    double d1 = calculate_distance( this->paths[ path ][ position-1 ], this->paths[ path ][ position ] );
    double d2 = calculate_distance( this->paths[ path ][ position-1 ], v );
    double d3 = calculate_distance( this->paths[ path ][ position ], v );
    return this->path_times[ path ] - d1 + d2 + d3;
}

double Solution::calculate_time_in_rewrite( int path, int position, Vertice * v ){
    Vertice * previous = this->paths[ path ][ position-1 ];
    Vertice * middle = this->paths[ path ][ position ];
    Vertice * next = this->paths[ path ][ position+1 ];
    double old_distance_to_previous = calculate_distance( previous, middle );
    double old_distance_to_next = calculate_distance( middle, next );
    double new_distance_to_previous = calculate_distance( previous, v );
    double new_distance_to_next = calculate_distance( v, next );
    return this->path_times[ path ] 
        - old_distance_to_previous - old_distance_to_next
        + new_distance_to_previous + new_distance_to_next;
}

bool Solution::add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return false;
    }
    this->paths[ path ].push_back( initial );
    this->paths[ path ].push_back( final );
    this->path_times[ path ] = calculate_distance( initial, final );
    return true;
}

bool Solution::add_vertice( int path, Vertice * v ){
    if( path < 0 ||  (unsigned int) path >= this->paths.size() ){
        return false;
    }

    int position = this->paths[ path ].size() - 1;
    double n_time = calculate_time_in_add( path, position, v );

    if( this->time_per_path > n_time ){
        update_reward_in_add( path, v );
        this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

bool Solution::add_vertice_in_position( int path, int position, Vertice * v ){
    if( path < 0 ||  (unsigned int) path >= this->paths.size() ){
        return false;
    }
    if( position < 1 || (unsigned int) position >= this->paths[ path ].size() ){
        return 0;
    }
    
    double n_time = calculate_time_in_add( path, position, v );

    if( this->time_per_path > n_time ){
        update_reward_in_add( path, v );
        this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

bool Solution::rewrite_vertice( int path, int position, Vertice * v ){
    if( path < 0 ||  (unsigned int) path >= this->paths.size() ){
        return false;
    }

    double n_time = calculate_time_in_rewrite( path, position, v );

    if( this->time_per_path > n_time ){
        update_reward_in_rewrite( path, position, v );
        this->paths[ path ][ position ] = v;
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

Vertice * Solution::get_last_path_vertice_in_path( int path ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return 0;
    }
    int last_position = this->paths[ path ].size() - 1;
    return this->paths[ path ][ last_position ];
}

Vertice * Solution::get_vertice_in_path( int path, int position ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return 0;
    }
    if( position < 1 || (unsigned int) position >= this->paths[ path ].size() ){
        return 0;
    }
    return this->paths[ path ][ position ];
}

double Solution::get_total_rewards(){
    return this->total_rewards;
}

int Solution::get_number_paths(){
    return this->paths.size();
}

int Solution::get_length_of_path( int path ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return -1;
    }
    return this->paths[ path ].size();
}

string Solution::to_string(){
    string s;
    s = "number paths: " + std::to_string(this->paths.size()) + "\n";
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    s += "paths:\n";
    for (unsigned int i = 0; i < this->paths.size(); i++){
        s += "size: " + std::to_string( this->paths[ i ].size() ) + "\n" ;
        for (unsigned int j = 0; j < this->paths[ i ].size(); j++){
            s += this->paths[ i ][ j ]->to_string() + "\n";
        }
        s += "reward: " + std::to_string( this->path_rewards[ i ])+"\n";
        s += "time: " + std::to_string( this->path_times[ i ])+"\n";
        s += ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    }
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    
    return s;
}