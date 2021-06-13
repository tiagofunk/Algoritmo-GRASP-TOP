
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "RandomGreedyGen_ScoreZ.h"
#include "LocalSearchWithOperators.h"
#include "PathRelinkingOperator.h"
#include "ArgumentReader.h"

#include <iostream>
#include <time.h>
#include <map>

using namespace std;

int main( int argc, char * argv[] ){

    clock_t initialTime = 0, finalTime = 0;
	initialTime = clock();

    int seed = time( 0 );//stoi( argv[ 3 ] );
	ArgumentReader arg( argc, argv );
    string file = arg.getValue("--file");
    double alpha = stod( arg.getValue("--alpha") );
    int iterations = stoi( arg.getValue("--iterations") );
    bool path = arg.getValue("--path") == "y"? true : false; 

    InstanceReader ir( file );
    Instance i = ir.read();

    GRASP g(
        iterations,
        seed,
        alpha,
        new RandomGreedyGen_ScoreZ( alpha, i.get_number_of_paths(), i.get_time_per_path() ),
        new LocalSearchWithOperators(),
        new PathRelinkingOperator( path ), 
        &i );
    Solution * s = g.execute();

    finalTime = clock();
	clock_t time = ( (finalTime - initialTime) / (double) CLOCKS_PER_SEC ) * 1000;
    cout << s->get_total_rewards() << endl << time << endl;
    cout << s->to_string() << endl;
    return 0;
}