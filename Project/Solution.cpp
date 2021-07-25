#include "Solution.h"

#include "Utils.h"

#include <sstream>
#include <iomanip>

Solution::Solution( int number_paths, double time_per_path ){
    this->paths.resize( number_paths );
    this->path_rewards.resize( number_paths );
    this->path_times.resize( number_paths );
    this->checker_is_unlocked = true;
    this->time_per_path = time_per_path;
    this->total_rewards = 0.0;
    this->total_time = 0.0;
    this->used_vertices.resize( VERTICE_HASH_SIZE );
}

bool Solution::add_initial_and_final_vertice( int path, Vertice * initial, Vertice * final ){
    if( check_if_path_is_valid( path ) ) return false;

    this->paths[ path ].push_back( initial );
    this->used_vertices.insert( initial->get_hash() );

    this->paths[ path ].push_back( final );
    this->used_vertices.insert( final->get_hash() );

    double n_time = calculate_distance( initial, final );
    this->path_times[ path ] = n_time;
    this->total_time += n_time;
    return true;
}

void Solution::lock_checker(){
    this->checker_is_unlocked = false;
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

void Solution::update_reward_in_remove( int path, int position ){
    Vertice * to_remove = this->paths[ path ][ position ];
    this->path_rewards[ path ] -= to_remove->get_reward();
    this->total_rewards -= to_remove->get_reward();
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

double Solution::calculate_time_in_remove( int path, int position ){
    Vertice * previous = this->paths[ path ][ position-1 ];
    Vertice * middle = this->paths[ path ][ position ];
    Vertice * next = this->paths[ path ][ position+1 ];
    double old_distance_to_previous = calculate_distance( previous, middle );
    double old_distance_to_next = calculate_distance( middle, next );
    double new_distance = calculate_distance( previous, next );
    return this->path_times[ path ] - old_distance_to_previous - old_distance_to_next + new_distance;
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

bool Solution::check_if_path_is_valid( int path ){
    return path < 0 || (unsigned int) path >= this->paths.size();
}

bool Solution::check_if_path_position_is_valid( int path, int position ){
    return this->check_if_path_is_valid( path ) && ( position < 1 || (unsigned int) position >= this->paths[ path ].size() );
}

bool Solution::add_vertice( int path, Vertice * v ){
    int position = this->paths[ path ].size() - 1;
    return this->add_vertice( path, position, v );
}

bool Solution::add_vertice( int path, int position, Vertice * v ){
    if( this->check_if_path_position_is_valid( path, position ) ) return false;
    if( this->check_if_vertice_is_used( v ) ) return false;
    
    double n_time = calculate_time_in_add( path, position, v );

    if( this->checker_is_unlocked || this->time_per_path > n_time ){
        update_reward_in_add( path, v );
        this->paths[ path ].insert( this->paths[ path ].begin() + position, v );
        this->used_vertices.insert( v->get_hash() );
        this->total_time += n_time - this->path_times[ path ];
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

bool Solution::rewrite_vertice( int path, int position, Vertice * v ){
    if( this->check_if_path_position_is_valid( path, position ) ) return false;
    if( this->check_if_vertice_is_used( v ) ) return false;

    double n_time = calculate_time_in_rewrite( path, position, v );

    if( this->checker_is_unlocked || this->time_per_path > n_time ){
        update_reward_in_rewrite( path, position, v );

        Vertice * old_v = this->paths[ path ][ position ];
        this->used_vertices.erase( old_v->get_hash() );

        this->paths[ path ][ position ] = v;
        this->used_vertices.insert( v->get_hash() );
        
        this->total_time += n_time - this->path_times[ path ];
        this->path_times[ path ] = n_time;
        return true;
    }
    
    return false;
}

bool Solution::swap( int path, int pos1, int pos2 ){
    if( check_if_path_position_is_valid( path, pos1 ) ) return false;
    if( check_if_path_position_is_valid( path, pos2 ) ) return false;

    Vertice * v = this->paths[ path ][ pos1 ];
    this->paths[ path ][ pos1 ] = this->paths[ path ][ pos2 ];
    this->paths[ path ][ pos2 ] = v;

    double n_time = this->recalculate_time( path );

    if( this->checker_is_unlocked || this->time_per_path > n_time ){
        this->total_time += n_time - this->path_times[ path ];
        this->path_times[ path ] = n_time;
        return true;
    }else{
        v = this->paths[ path ][ pos1 ];
        this->paths[ path ][ pos1 ] = this->paths[ path ][ pos2 ];
        this->paths[ path ][ pos2 ] = v;
        return false;
    }
}

bool Solution::swap( int path1, int pos1, int path2, int pos2 ){
    if( check_if_path_position_is_valid( path1, pos1 ) ) return false;
    if( check_if_path_position_is_valid( path2, pos2 ) ) return false;

    Vertice * v = this->paths[ path1 ][ pos1 ];
    this->paths[ path1 ][ pos1 ] = this->paths[ path2 ][ pos2 ];
    this->paths[ path2 ][ pos2 ] = v;

    double n_time_1 = this->recalculate_time( path1 );
    double n_time_2 = this->recalculate_time( path2 );

    if( this->checker_is_unlocked || (this->time_per_path > n_time_1 || this->time_per_path > n_time_2) ){
        this->total_time += n_time_1 + n_time_2 - this->path_times[ path1 ] + this->path_times[ path2 ];
        this->path_times[ path1 ] = n_time_1;
        this->path_times[ path2 ] = n_time_2;
        return true;
    }else{
        v = this->paths[ path1 ][ pos1 ];
        this->paths[ path1 ][ pos1 ] = this->paths[ path2 ][ pos2 ];
        this->paths[ path2 ][ pos2 ] = v;
        return false;
    }
}

bool Solution::remove( int path, int position ){
    if( check_if_path_position_is_valid( path, position ) ) return false;

    update_reward_in_remove( path, position );
    double n_time = calculate_time_in_remove( path, position );
    this->total_time += n_time - this->path_times[ path ];
    this->path_times[ path ] = n_time;

    Vertice * v = this->paths[ path ][ position ];
    this->used_vertices.erase( v->get_hash() );
    this->paths[ path ].erase( this->paths[ path ].begin() + position );
    return true;
}

bool Solution::move( int path1, int position1, int path2, int position2 ){
    if( check_if_path_position_is_valid( path1, position1 ) ) return false;
    if( check_if_path_position_is_valid( path2, position2 ) ) return false;

    Vertice * v = this->paths[ path1 ][ position1 ];

    double n_time = calculate_time_in_remove( path1, position1 );
    this->total_time += n_time - this->path_times[ path1 ];
    this->path_times[ path1 ] = n_time;

    n_time = calculate_time_in_add( path2, position2, v );
    this->total_time += n_time + this->path_times[ path2 ];
    this->path_times[ path2 ] = n_time;
    
    this->paths[ path1 ].erase( this->paths[ path1 ].begin() + position1 );
    this->paths[ path2 ].insert( this->paths[ path2 ].begin() + position2, v );
    return true;
}

bool Solution::is_empty( int path ){
    if( check_if_path_is_valid( path ) ) return true;
    return this->paths[ path ].size() != 2;
}

Vertice * Solution::get_last_path_vertice_in_path( int path ){
    if( check_if_path_is_valid( path ) ) return 0;
    int last_position = this->paths[ path ].size() - 1;
    return this->paths[ path ][ last_position ];
}

Vertice * Solution::get_vertice_in_path( int path, int position ){
    if( check_if_path_position_is_valid( path, position ) ) return 0;
    return this->paths[ path ][ position ];
}

double Solution::get_total_rewards(){
    return this->total_rewards;
}

double Solution::get_total_time(){
    return this->total_time;
}

double Solution::get_distance( int path, int position ){
    if( check_if_path_position_is_valid( path, position ) ) return -1.0;
    if( this->paths[ path ].size() == 2 ) return -1.0;

    return calculate_distance( this->paths[ path ][ position-1 ], this->paths[ path ][ position ] ) +
        calculate_distance( this->paths[ path ][ position ], this->paths[ path ][ position+1 ] );
}

double Solution::get_time_path( int path ){
    if( check_if_path_is_valid( path ) ) throw runtime_error("get_time_path: path is invalid\n");
    return this->path_times[ path ];
}

double Solution::get_time_per_path(){
    return this->time_per_path;
}

int Solution::get_number_paths(){
    return this->paths.size();
}

int Solution::get_length_of_path( int path ){
    if( check_if_path_is_valid( path ) ) return -1;
    return this->paths[ path ].size();
}

string Solution::to_string(){
    string s;
    s = "number paths: " + std::to_string(this->paths.size()) + "\n";
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
    s += "time per path: " + std::to_string( this->time_per_path ) + "\n";
    s += "total reward: " + std::to_string( this->total_rewards ) + "\n";
    s += "total time: " + std::to_string( this->total_time ) + "\n";
    s += "hash: " + std::to_string( this->get_hash() ) + "\n";
    
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
