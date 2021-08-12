#include "ArgumentReader.h"
#include <stdexcept>

#define FIRST_ARGUMENT_ON_PARAMETERS 3
#define FIRST_ARGUMENT 2
#define JUMP 2

ArgumentReader::ArgumentReader( int argc, char* argv[] ){
	vector< string > args;
	for( int i = FIRST_ARGUMENT_ON_PARAMETERS; i < argc; i++ ){
		args.push_back( argv[ i ] );
	}
	process( args );
}

void ArgumentReader::process( vector< string > args ){
	arguments.push_back( {"--seed", args[0]} );
	arguments.push_back( {"--file", args[1]} );
	for( unsigned int i = FIRST_ARGUMENT; i < args.size(); i += JUMP ){
		arguments.push_back( { args[ i ], args[ i+1 ] } );
	}
}

string ArgumentReader::getValue( string name ){
	for( unsigned int i = 0; i < arguments.size(); i++ ){
		if( arguments[i].name == name ){
			return arguments[i].value;
		}
	}
	throw runtime_error( "ArgumentReader->getValue: not found argument: " + name + "\n");
}