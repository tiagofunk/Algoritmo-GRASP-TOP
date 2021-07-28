#include "main.h"

void show_log( string s ){
    #if LOG_LEVEL == true
        cout << s;
    #endif
}

#if DEBUG == true

#include "tests/test_solution.h"

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite_solution);
	MU_REPORT();
	return MU_EXIT_CODE;

}

#else

#include "App.h"
#include "ArgumentReader.h"

using namespace std;

int main( int argc, char * argv[] ){
    App * app = new App( new ArgumentReader( argc, argv ) );
    app->execute();
    return 0;
}

#endif