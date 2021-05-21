
#include "InstanceReader.h"
#include "Instance.h"
#include "Grasp.h"

#include <iostream>

using namespace std;

int main( int argc, char * argv[] ){
    InstanceReader ir( argv[ 1 ] );
    Instance i = ir.read();
    cout << i.to_string() << endl;

    GRASP g( &i );
    g.execute();
    return 0;
}