#ifndef ARGUMENTSREADER_H_
#define ARGUMENTSREADER_H_

#include <string>
#include <vector>

using namespace std;

struct Argument{
	string name;
	string value;
};

class ArgumentReader{
private:
	vector< Argument > arguments;

	void process( vector< string > args );

public:
	ArgumentReader( int argc, char* argv[] );
	string getValue( string name );
};

#endif /* ARGUMENTSREADER_H_ */