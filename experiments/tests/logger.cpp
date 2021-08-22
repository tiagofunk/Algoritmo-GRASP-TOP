#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

string read_file( string file, string id ){
    int i, f, time;
    double result;
    string instance_name, ms, s;

    ifstream reader( file.c_str(), ios::in );
    if( !reader ){
        throw runtime_error( "Erro on open file: " + file );
    }

	s = "version,instance,result,time\n";
    while( !reader.eof() ){
        reader >> instance_name >> result >> time >> ms;
     	s += id + "," + instance_name + "," + to_string( result ) + "," + to_string( time ) + "\n";
    }
    reader.close();
    return s;
}

int main( int argc, char* argv[] ){
    if( argc == 3 ){
		cout << read_file( argv[ 1 ], argv[ 2 ] );
    }else{
        cerr << "parameters: ./process <log_file> <id>" << endl;
    }
    
    return 0;
}
