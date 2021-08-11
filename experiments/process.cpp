#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>

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
    string instance_name, ms;
    double result;
    int time;
    int i, f;
    vector< instance_value > instances;

    ifstream reader( file.c_str(), ios::in );
    if( !reader ){
        throw runtime_error( "Erro on open file: " + file );
    }

    while( !reader.eof() ){
        reader >> instance_name >> result >> time >> ms;
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

bool mean_on_soa( instance_value inst ){
    return inst.state_of_art == inst.mean_results;
}

bool has_on_soa( instance_value inst ){
    return inst.state_of_art == inst.best_result;
}

string print_to_csv( vector< instance_value > instances ){
    int _mean_on_soa = 0, _has_on_soa = 0;
    string aux;
    string s = "instancia;estado da arte;melhor;media;desvio padrao;tempo (ms);media no soa;chegou no soa;\n";
    for( unsigned int i = 0; i < instances.size(); i++ ){
        aux = "";
        s += instances[ i ].file + ";";
        s += to_string( instances[ i ].state_of_art ) + ";";
        s += to_string( instances[ i ].best_result ) + ";";
        aux += to_string( instances[ i ].mean_results ) + ";";
        aux += to_string( instances[ i ].stand_desv_results ) + ";";
        aux += to_string( instances[ i ].mean_time ) + ";";
        replace( aux.begin(), aux.end(), '.', ',');
        s += aux;
        if( mean_on_soa( instances[ i ] ) ){
            s += "1;";
            _mean_on_soa++;
        } else {
            s += "0;";
        }
        if( has_on_soa( instances[ i ] ) ){
            s += "1;";
            _has_on_soa++;
        } else {
            s += "0;";
        }
        s += "\n";
    }
    s += ";;;;;;" + to_string( _mean_on_soa ) + ";" + to_string( _has_on_soa - _mean_on_soa ) + ";\n";
    return s;
}

int main( int argc, char* argv[] ){
    if( argc == 3 ){
        vector< instance_value > instances = read_file( argv[ 1 ] );
        instances = read_file_state_of_art( argv[ 2 ], instances );
        instances = calcule_mean( instances );
        instances = calcule_stand_desv( instances );
        cout << print_to_csv( instances ) << endl;
    }else{
        cerr << "parameters: ./process <log_file> <state_of_art_file>" << endl;
    }
    
    return 0;
}
