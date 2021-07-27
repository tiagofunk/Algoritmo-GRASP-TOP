#ifndef DEBUG
#define DEBUG true 
#endif

#if DEBUG == false

#include "tests/test_solution.h"

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite_solution);
	MU_REPORT();
	return MU_EXIT_CODE;

}

#else

#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "RandomGreedyGen_MinMax.h"
#include "LocalSearchWithOperators.h"
#include "PathRelinkingOperator.h"
#include "ArgumentReader.h"
#include "Operator.h"
#include "OperatorSwapIntoRoute.h"
#include "OperatorAddVerticeInPath.h"
#include "OperatorSwapBetweenPathAndUnusedvertices.h"
#include "Operator2opt.h"
#include "OperatorExchange.h"
#include "OperatorRandomRemove.h"
#include "OperatorWorstRemove.h"
#include "OperatorRelocate.h"

#include <iostream>
#include <time.h>
#include <map>
#include <random>

// --alpha 0.86 --iterations 3540 --path y

using namespace std;

int main( int argc, char * argv[] ){

    clock_t initialTime = 0, finalTime = 0;
	initialTime = clock();

    random_device rd;
    int seed = rd();// stoi( argv[ 3 ] );
    cout << "seed: " << seed << endl;
	ArgumentReader arg( argc, argv );
    string file = arg.getValue("--file");
    double alpha = stod( arg.getValue("--alpha") );
    int iterations = stoi( arg.getValue("--iterations") );
    bool path = arg.getValue("--path") == "y"? true : false; 

    InstanceReader ir( file );
    ir.read();

    vector< Operator * > operators;
    operators.push_back( new OperatorRelocate() );

    GRASP g(
        iterations,
        seed,
        alpha,
        new RandomGreedyGen_MinMax( alpha, 2 ),
        new LocalSearchWithOperators( operators ),
        new PathRelinkingOperator( path ));
    Solution * s = g.execute();

    finalTime = clock();
	clock_t time = ( (finalTime - initialTime) / (double) CLOCKS_PER_SEC ) * 1000;
    cout << s->to_string();
    cout << s->get_total_rewards() << endl << time << " ms" << endl;
    return 0;
}

#endif