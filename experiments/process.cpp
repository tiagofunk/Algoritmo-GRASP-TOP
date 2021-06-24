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
    int time[ NUMBER_RESULTS ];
    int best_result;
    double mean_results;
    double stand_desv_results;
    double mean_time;
    int state_of_art;
};

vector< instance_value > add_value_on_instance( vector< instance_value > instances, string instance, int value, int time ){
    bool finded = false;
    for (unsigned int i = 0; i < instances.size(); i++){
        if( instances[ i ].file == instance ){
            instances[ i ].results[ instances[ i ].position ] = value;
            instances[ i ].time[ instances[ i ].position ] = time;
            instances[ i ].position++;
            if( instances[ i ].best_result < value ){
                instances[ i ].best_result = value;
            }
            finded = true;
        }
    }
    if( !finded ){
        instance_value inst;
        inst.file = instance;
        inst.position = 1;
        inst.results[ 0 ] = value;
        inst.time[ 0 ] = time;
        inst.best_result = value;
        instances.push_back( inst );
    }
    return instances;
}

vector< instance_value > read_file( string file ){
    string instance_name;
    int result, time;
    int i, f;
    vector< instance_value > instances;

    ifstream reader( file.c_str(), ios::in );
    if( !reader ){
        throw runtime_error( "Erro on open file: " + file );
    }

    while( !reader.eof() ){
        reader >> instance_name >> result >> time;
        i = instance_name.find_last_of("/") + 1;
        f = instance_name.find_last_of(".") - i;
        instance_name = instance_name.substr( i, f );
        instances = add_value_on_instance( instances, instance_name, result, time );
    }
    instances.erase( instances.end()-1 );
    reader.close();
    return instances;
}

vector< instance_value > read_file_state_of_art( string file, vector< instance_value > instances ){
    string instance_name;
    int result;

    ifstream reader( file.c_str(), ios::in );
    if( !reader ){
        throw runtime_error( "Erro on open file: " + file );
    }

    while( !reader.eof() ){
        reader >> instance_name >> result;
        for( unsigned int i = 0; i < instances.size(); i++ ){
            if( instances[ i ].file == instance_name ){
                instances[ i ].state_of_art = result;
                break;
            }
        }
    }
    reader.close();
    return instances;
}

vector< instance_value > calcule_mean( vector< instance_value > instances ){
    double sum_result, sum_time;
    for( unsigned int i = 0; i < instances.size(); i++ ){
        sum_result = 0.0;
        sum_time = 0.0;
        for( int j = 0; j < instances[ i ].position; j++ ){
            sum_result += instances[ i ].results[ j ];
            sum_time += instances[ i ].time[ j ];
        }
        instances[ i ].mean_results = sum_result / instances[ i ].position;
        instances[ i ].mean_time = sum_time / instances[ i ].position;
    }
    return instances;
}

vector< instance_value > calcule_stand_desv( vector< instance_value > instances ){
    double sum, mean;
    for( unsigned int i = 0; i < instances.size(); i++ ){
        sum = 0.0;
        mean = instances[ i ].mean_results;
        for( int j = 0; j < instances[ i ].position; j++ ){
            sum += pow( instances[ i ].results[ j ] - mean, 2);
        }
        instances[ i ].stand_desv_results = sqrt( sum / instances[ i ].position );
    }
    return instances;
}

void print_to_csv( vector< instance_value > instances ){
    cout << "Instância;estado da arte;melhor;média;desvio padrão;tempo (ms)" << endl;
    for( unsigned int i = 0; i < instances.size(); i++ ){
        cout << instances[ i ].file << ";";
        cout << instances[ i ].state_of_art << ";";
        cout << instances[ i ].best_result << ";";
        cout << instances[ i ].mean_results << ";";
        cout << instances[ i ].stand_desv_results << ";";
        cout << instances[ i ].mean_time << ";";
        cout << endl;
    }
}

int main( int argc, char* argv[] ){
    vector< instance_value > instances = read_file( "log.txt" );
    instances = read_file_state_of_art( "soa.txt", instances );
    instances = calcule_mean( instances );
    instances = calcule_stand_desv( instances );
    print_to_csv( instances );
    return 0;
}
