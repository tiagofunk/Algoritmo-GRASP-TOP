#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "Vertice.h"

using namespace std;

double * find_max_min( double * values, int size );
double calculate_mean( vector< double > values, int size );
double calculate_standard_deviation( vector< double > values, int size, double mean );
double calculate_score_z( double value, double mean, double stand );

double calculate_distance( Vertice * v1, Vertice * v2 );

vector< Vertice * > shuffle_vertices( vector< Vertice * > vertices );

double random_number();

double calcule_percentage( int n, int total );

int truncate( double value, int decimals );

#endif