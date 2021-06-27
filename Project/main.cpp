
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "RandomGreedyGen_ScoreZ.h"
#include "RandomGreedyGen_MinMax.h"
#include "LocalSearchWithOperators.h"
#include "PathRelinkingOperator.h"
#include "ArgumentReader.h"
#include "Operator.h"
#include "OperatorSwapIntoRoute.h"
#include "OperatorAddVerticeInPath.h"
#include "OperatorSwapBetweenPathAndUnusedvertices.h"
#include "Operator2opt.h"
#include "OperatorSwapInterRoute.h"
#include "OperatorRandomRemove.h"

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
	ArgumentReader arg( argc, argv );
    string file = arg.getValue("--file");
    double alpha = stod( arg.getValue("--alpha") );
    int iterations = stoi( arg.getValue("--iterations") );
    bool path = arg.getValue("--path") == "y"? true : false; 

    InstanceReader ir( file );
    Instance i = ir.read();

    vector< Operator * > operators;

    // Operator * orr = new OperatorRandomRemove();
    // operators.push_back( orr );

    Operator * o0 = new OperatorSwapIntoRoute();
    operators.push_back( o0 );

    // Operator * oo = new OperatorSwapInterRoute();
    // operators.push_back( oo );

    // Operator * two_opt = new Operator2opt();
    // operators.push_back( two_opt );

    Operator * o1 = new OperatorAddVerticeInPath();
    operators.push_back( o1 );

    Operator * o2 = new OperatorSwapBetweenPathAndUnusedvertices();
    operators.push_back( o2 );

    GRASP g(
        iterations,
        seed,
        alpha,
        new RandomGreedyGen_MinMax( alpha, i.get_number_of_paths(), i.get_time_per_path() ),
        new LocalSearchWithOperators( operators ),
        new PathRelinkingOperator( path ), 
        &i );
    Solution * s = g.execute();

    finalTime = clock();
	clock_t time = ( (finalTime - initialTime) / (double) CLOCKS_PER_SEC ) * 1000;
    cout << s->to_string();
    cout << s->get_total_rewards() << endl << time << " ms" << endl;
    return 0;
}