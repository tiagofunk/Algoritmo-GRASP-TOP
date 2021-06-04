#include "ArgumentReader.h"

ArgumentReader::ArgumentReader( int argc, char* argv[] ){
	string *args = new string[ argc-4 ];
	for( int i = 4; i < argc; i++ ){
		args[ i-4 ] = argv[ i ];
	}
	process( argc-4, args );
	delete [] args;
}

void ArgumentReader::process( int size, string *args ){
	arguments.push_back( {"--file", args[0]} );
	for( int i = 1; i < size; i += 2 ){
		arguments.push_back( { args[ i ], args[ i+1 ] } );
	}
}


string ArgumentReader::getValue( string name ){
	for( unsigned int i = 0; i < arguments.size(); i++ ){
		if( arguments[i].name == name ){
			return arguments[i].value;
		}
	}
	return "-1";
}