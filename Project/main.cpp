
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"
#include "TabuSearch.h"

#include <iostream>

using namespace std;

int main( int argc, char * argv[] ){
    InstanceReader ir( argv[ 1 ] );
    Instance i = ir.read();
    //cout << i.to_string() << endl;

    GRASP g( 0.0, new TabuSearch(), &i );
    Solution * s = g.execute();
    cout << s->get_total_rewards() << endl;
    cout << s->to_string() << endl;
    return 0;
}