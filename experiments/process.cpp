#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

#define NUMBER_RESULTS 32

struct instance_value{
    string file;
    int position;
    int results[ NUMBER_RESULTS ];
    double mean;
    double stand_desv;
};

vector< instance_value > add_value_on_instance( vector< instance_value > instances, string instance, int value ){
    bool finded = false;
    for (unsigned int i = 0; i < instances.size(); i++){
        if( instances[ i ].file == instance ){
            instances[ i ].results[ instances[ i ].position ] = value;
            instances[ i ].position++;
            finded = true;
        }
    }
    if( !finded ){
        instance_value inst;
        inst.file = instance;
        inst.position = 1;
        inst.results[ 0 ] = value;
        instances.push_back( inst );
    }
    return instances;
}

vector< instance_value > read_file( string file ){
    string instance_name;
    int value;
    vector< instance_value > instances;
    
    ifstream reader( file.c_str(), ios::in );
    if( !reader ){
        throw runtime_error( "Erro on open file: " + file );
    }

    while( reader >> instance_name >> value ){
        //cout << "instance_name: " << instance_name << " value: " << value <<endl;
        instances = add_value_on_instance( instances, instance_name, value );
    }

    reader.close();
    return instances;
}

vector< instance_value > calcule_mean( vector< instance_value > instances ){
    double sum;
    for( unsigned int i = 0; i < instances.size(); i++ ){
        sum = 0.0;
        for( int j = 0; j < instances[ i ].position; j++ ){
            sum += instances[ i ].results[ j ];
        }
        instances[ i ].mean = sum / instances[ i ].position;
    }
    return instances;
}

vector< instance_value > calcule_stand_desv( vector< instance_value > instances ){
    double sum, mean;
    for( unsigned int i = 0; i < instances.size(); i++ ){
        sum = 0.0;
        mean = instances[ i ].mean;
        for( int j = 0; j < instances[ i ].position; j++ ){
            sum += pow( instances[ i ].results[ j ] - mean, 2);
        }
        instances[ i ].stand_desv = sqrt( sum / instances[ i ].position );
    }
    return instances;
}

void print( vector< instance_value > instances ){
    for( unsigned int i = 0; i < instances.size(); i++ ){
        cout << "instance: " << instances[ i ].file << endl;
        cout << "position: " << instances[ i ].position << endl;
        for( int j = 0; j < instances[ i ].position; j++ ){
            cout << instances[ i ].results[ j ] << " ";
        }
        cout << endl;
        cout << "mean: " << instances[ i ].mean << endl;
        cout << "stand desv: " << instances[ i ].stand_desv << endl;
        cout << endl << endl;
    }
}

int main( int argc, char* argv[] ){
    string file = "log.txt";
    vector< instance_value > instances = read_file( file );
    instances = calcule_mean( instances );
    instances = calcule_stand_desv( instances );
    print( instances );
    return 0;
}