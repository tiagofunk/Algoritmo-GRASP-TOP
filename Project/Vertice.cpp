#include "Vertice.h"

Vertice::Vertice(double x, double y, int score){
    this->x = x;
    this->y = y;
    this->score = score;
}

Vertice::~Vertice(){
}

double Vertice::get_x(){
    return this->x;
}

double Vertice::get_y(){
    return this->y;
}

double Vertice::get_score(){
    return this->score;
}

std::string Vertice::to_string(){
    std::string s;
    s = "x: " + std::to_string( this->x );
    s += ", y: " + std::to_string( this->y );
    s += ", score: " + std::to_string( this->score );
    return s;
}