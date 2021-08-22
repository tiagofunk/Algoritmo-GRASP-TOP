#include "Utils.h"

#include <math.h>

double * find_max_min( double * values, int size ){
    double * min_max = new double[ 2 ];
    min_max[ 0 ] = values[ 0 ];
    min_max[ 1 ] = values[ 0 ];
    for( int i = 1; i < size; i++ ){
        if( min_max[ 0 ] > values[ i ] ){
            min_max[ 0 ] = values[ i ];
        } else if( min_max[ 1 ] < values[ i ] ){
            min_max[ 1 ] = values[ i ];
        }
    }
    return min_max;
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

double calculate_distance( Vertice * v1, Vertice * v2 ){
    double x = v2->get_x() - v1->get_x();
    double y = v2->get_y() - v1->get_y();
    return sqrt( pow( x, 2 ) + pow( y, 2 ) );
}

vector< Vertice * > shuffle_vertices( vector< Vertice * > vertices ){
    int n = 0;
    Vertice * v = 0;
    for( unsigned int i = 0; i < vertices.size(); i++ ){
        n = rand() % vertices.size();
        v = vertices[ i ];
        vertices[ i ] = vertices[ n ];
        vertices[ n ] = v;
    }
    return vertices;
}

double random_number(){
    return (double) rand() / RAND_MAX;
}

double calcule_percentage( int n, int total ){
    return 100 * ( (double) n / (double) total );
}

int truncate( double value, int decimals ){
    for( int i = 0; i < decimals; i++ ){
        value *= 10;
    }
    int result = value;
    return result;
}