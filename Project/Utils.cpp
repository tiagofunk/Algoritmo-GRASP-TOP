#include "Utils.h"

#include <math.h>

int get_seed(){
    srand( time( 0 ) );
    return rand();
}

double calculate_mean( vector< double > values, int size ){
    double sum = 0.0;
    for( int i = 0; i < size; i++ ){
        sum += values[ i ];
    }
    double r = sum / (double) size;
    return r;
}

double calculate_standard_deviation( vector< double > values, int size, double mean ){
    double sum = 0.0;
    for( int i = 0; i < size; i++ ){
        sum += pow( values[ i ] - mean, 2 );
    }
    sum = sum / size;
    sum = sqrt( sum );
    return sum;
}

double calculate_score_z( double value, double mean, double stand ){
    return ( value - mean ) / stand;
}

double distance( Point * p1, Point * p2 ){
    double x = p2->get_x() - p1->get_x();
    double y = p2->get_y() - p1->get_y();
    return sqrt( pow( x, 2 ) + pow( y, 2 ) );
}