#ifndef POINT_H
#define POINT_H

#include <string>

class Vertice{
private:
    double x;
    double y;
    double score;

public:
    Vertice(double x, double y, int score );
    ~Vertice();

    double get_x();
    double get_y();
    double get_score();

    std::string to_string();
    
};

#endif