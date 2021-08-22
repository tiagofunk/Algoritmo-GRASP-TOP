#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>

#define VERTICE_HASH_SIZE 256

class Vertice{
private:
    double x;
    double y;
    double reward;
    int hash;

    bool is_hashed;

public:
    Vertice(double x, double y, int reward );
    ~Vertice();

    double get_x();
    double get_y();
    int get_reward();

    int get_hash();

    friend std::ostream& operator<<(std::ostream & os, const Vertice & v );

    std::string to_string();
    
};

#endif