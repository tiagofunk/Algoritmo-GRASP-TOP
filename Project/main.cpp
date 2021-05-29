
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "TabuSearch.h"

#include <iostream>

using namespace std;

int main( int argc, char * argv[] ){
    if( argc != 3 ){
        cerr << "Exemplo de utilização do programa: ./TOP_GRASP_TS_PR <seed> <file>" << endl;
        return 1;
    }

    int seed = stoi( argv[ 1 ] );
    InstanceReader ir( argv[ 2 ] );
    Instance i = ir.read();

    GRASP g( seed, 0.0, new TabuSearch(), &i );
    Solution * s = g.execute();
    cout << s->get_total_rewards() << endl;
    cout << s->to_string() << endl;
    return 0;
}