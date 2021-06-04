
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "LocalSearchWithOperators.h"
#include "PathRelinkingOperator.h"
#include "ArgumentReader.h"

#include <iostream>

using namespace std;

int main( int argc, char * argv[] ){

    int seed = stoi( argv[ 3 ] );
	ArgumentReader arg( argc, argv );
    string file = arg.getValue("--file");
    double alpha = stoi( arg.getValue("--alpha") );
    int iterations = stoi( arg.getValue("--iterations") );
    bool path = arg.getValue("--path") == "y"? true : false; 

    InstanceReader ir( file );
    Instance i = ir.read();

    GRASP g( iterations, seed, alpha, new LocalSearchWithOperators(), new PathRelinkingOperator( path ), &i );
    Solution * s = g.execute();
    cout << s->get_total_rewards() << endl;
    //cout << s->to_string() << endl;
    return 0;
}