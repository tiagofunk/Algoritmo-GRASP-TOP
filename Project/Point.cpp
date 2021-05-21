#include "Point.h"

Point::Point(double x, double y, int score){
    this->x = x;
    this->y = y;
    this->score = score;
}

Point::~Point(){
}

double Point::get_x(){
    return this->x;
}

double Point::get_y(){
    return this->y;
}

double Point::get_score(){
    return this->score;
}

std::string Point::to_string(){
    std::string s;
    s = "x: " + std::to_string( this->x );
    s += ", y: " + std::to_string( this->y );
    s += ", score: " + std::to_string( this->score ) + "\n";
    return s;
}