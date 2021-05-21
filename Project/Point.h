#ifndef POINT_H
#define POINT_H

#include <string>

class Point{
private:
    double x;
    double y;
    double score;

public:
    Point(double x, double y, int score );
    ~Point();

    double get_x();
    double get_y();
    double get_score();

    std::string to_string();
    
};

#endif