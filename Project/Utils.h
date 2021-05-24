#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "Vertice.h"

using namespace std;

int get_seed();

double calculate_mean( vector< double > values, int size );
double calculate_standard_deviation( vector< double > values, int size, double mean );
double calculate_score_z( double value, double mean, double stand );

double distance( Vertice * p1, Vertice * p2 );

#endif