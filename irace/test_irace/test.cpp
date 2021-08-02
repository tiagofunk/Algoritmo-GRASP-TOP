#include <iostream>

using namespace std;

int main( int argc, char ** argv ){
    int a = stoi( argv[ 6 ] );
    int b = stoi( argv[ 8 ] );
    cout << -1*(a+b) << endl;
    return 0;
}