#include "Solution.h"

#include "Utils.h"

#include <sstream>
#include <iomanip>

Solution::Solution( int number_paths, double time_per_path ){
    this->paths.resize( number_paths );
    this->path_rewards.resize( number_paths );
    this->path_times.resize( number_paths );
    this->time_per_path = time_per_path;
    this->total_rewards = 0.0;
    this->used_vertices.resize( VERTICE_HASH_SIZE );
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

double Solution::recalculate_time( int path ){
    double sum = 0.0;
    for( unsigned int i = 0; i < this->paths[ path ].size()-1; i++ ){
        sum += calculate_distance( this->paths[ path ][ i ], this->paths[ path ][ i+1 ] );
    }
    return sum;
}

bool Solution::check_if_vertice_is_used( Vertice * v ){
    return this->used_vertices.find( v->get_hash() );
}

bool Solution::add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final ){
    if( path < 0 || (unsigned int) path >= this->paths.size() ){
        return false;
    }
    this->paths[ path ].push_back( initial );
    this->used_vertices.insert( initial->get_hash() );

    this->paths[ path ].push_back( final );
    this->used_vertices.insert( final->get_hash() );

    this->path_times[ path ] = calculate_distance( initial, final );
    return true;
}

bool Solution::add_vertice( int path, Vertice * v ){
    if( path < 0 ||  (unsigned int) path >= this->paths.size() ){
        return false;
    }
    if( this->check_if_vertice_is_used( v ) ){
        return false;
    }

    int position = this->paths[ path ].size() - 1;
    double n_time = calculate_time_in_add( path, position, v );

    if( this->time_per_path > n_time ){
        update_reward_in_add( path, v );
        this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
        this->used_vertices.insert( v->get_hash() );
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
        return false;
    }
    if( this->check_if_vertice_is_used( v ) ){
        return false;
    }
    
    double n_time = calculate_time_in_add( path, position, v );

    if( this->time_per_path > n_time ){
        update_reward_in_add( path, v );
        this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
        this->used_vertices.insert( v->get_hash() );
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

bool Solution::rewrite_vertice( int path, int position, Vertice * v ){
    if( path < 0 ||  (unsigned int) path >= this->paths.size() ){
        return false;
    }
    if( this->check_if_vertice_is_used( v ) ){
        return false;
    }

    double n_time = calculate_time_in_rewrite( path, position, v );

    if( this->time_per_path > n_time ){
        update_reward_in_rewrite( path, position, v );

        Vertice * old_v = this->paths[ path ][ position ];
        this->used_vertices.erase( old_v->get_hash() );

        this->paths[ path ][ position ] = v;
        this->used_vertices.insert( v->get_hash() );
        
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

bool Solution::swap( int path, int pos1, int pos2 ){
    if( path < 0 || path > this->paths.size() ) return false;
    if( pos1 < 1 || pos1 >= this->paths[ path ].size() ) return false;
    if( pos2 < 1 || pos2 >= this->paths[ path ].size() ) return false;

    Vertice * v = this->paths[ path ][ pos1 ];
    this->paths[ path ][ pos1 ] = this->paths[ path ][ pos2 ];
    this->paths[ path ][ pos2 ] = v;

    double n_time = this->recalculate_time( path );

    if( this->time_per_path > n_time ){
        this->path_times[ path ] = n_time;
        return true;
    }else{
        v = this->paths[ path ][ pos1 ];
        this->paths[ path ][ pos1 ] = this->paths[ path ][ pos2 ];
        this->paths[ path ][ pos2 ] = v;
        return false;
    }
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

double Solution::get_time_path( int path ){
    if( path < 0 || path >= this->paths.size() ) throw runtime_error("get_time_path: path is invalid\n");
    return this->path_times[ path ];
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

int Solution::get_hash(){
    ostringstream oss;
    Vertice * v = 0;
    for( unsigned int i = 0; i < this->paths.size(); i++ ){
        for( unsigned int j = 0; j < this->paths[ i ].size(); j++ ){
            v = this->paths[ i ][ j ];
            oss << setprecision(2) << v->get_x() << v->get_y();
        }
    }
    std::hash< std::string > gen_hash;
    return gen_hash( oss.str() ) % SOLUTION_HASH_SIZE;
}