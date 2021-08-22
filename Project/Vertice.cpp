#include "Vertice.h"

#include <string>
#include <functional>
#include <iomanip>
#include <sstream>

Vertice::Vertice(double x, double y, int reward){
    this->x = x;
    this->y = y;
    this->reward = reward;
    this->is_hashed = false;
}

Vertice::~Vertice(){
}

double Vertice::get_x(){
    return this->x;
}

double Vertice::get_y(){
    return this->y;
}

int Vertice::get_reward(){
    return this->reward;
}

int Vertice::get_hash(){
    if( !this->is_hashed ){
        std::ostringstream oss;
        oss << std::setprecision( 2 ) << this->x << this->y;
        std::hash< std::string > gen_hash;
        this->hash = gen_hash( oss.str() ) % VERTICE_HASH_SIZE;
        this->is_hashed = true;
    }
    return this->hash;
}

std::ostream& operator<<(std::ostream & os, const Vertice & v ){
    os << "x: " << v.x << ", y: " << v.y << ", reward: " << v.reward; 
    return os;
}

std::string Vertice::to_string(){
    std::string s;
    s = "x: " + std::to_string( this->x );
    s += ", y: " + std::to_string( this->y );
    s += ", reward: " + std::to_string( this->reward );
    s += ", hash: " + std::to_string( this->hash );
    return s;
}