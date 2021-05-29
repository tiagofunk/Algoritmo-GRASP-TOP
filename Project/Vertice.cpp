#include "Vertice.h"

Vertice::Vertice(double x, double y, int reward){
    this->x = x;
    this->y = y;
    this->reward = reward;
}

Vertice::~Vertice(){
}

double Vertice::get_x(){
    return this->x;
}

double Vertice::get_y(){
    return this->y;
}

double Vertice::get_reward(){
    return this->reward;
}

std::string Vertice::to_string(){
    std::string s;
    s = "x: " + std::to_string( this->x );
    s += ", y: " + std::to_string( this->y );
    s += ", score: " + std::to_string( this->reward );
    return s;
}