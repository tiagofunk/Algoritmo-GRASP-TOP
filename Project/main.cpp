
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "LocalSearchWithOperators.h"
#include "PathRelinkingOperator.h"

#include <iostream>

using namespace std;

int main( int argc, char * argv[] ){
    if( argc != 4 ){
        cerr << "Exemplo de utilização do programa: ./TOP_GRASP_TS_PR <seed> <alfa> <file>" << endl;
        return 1;
    }

    int seed = stoi( argv[ 1 ] );
    double alfa = stod( argv[ 2 ] );
    InstanceReader ir( argv[ 3 ] );
    Instance i = ir.read();

    GRASP g( seed, alfa, new LocalSearchWithOperators(), new PathRelinkingOperator(), &i );
    Solution * s = g.execute();
    cout << s->get_total_rewards() << endl;
    cout << s->to_string() << endl;
    return 0;
}