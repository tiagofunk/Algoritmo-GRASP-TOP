#ifndef POINT_H
#define POINT_H

#include <string>

class Vertice{
private:
    double x;
    double y;
    double reward;

public:
    Vertice(double x, double y, int reward );
    ~Vertice();

    double get_x();
    double get_y();
    double get_reward();

    bool equals( Vertice &v );

    std::string to_string();
    
};

#endif