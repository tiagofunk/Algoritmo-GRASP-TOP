#ifndef TEST_SOLUTION_H
#define TEST_SOLUTION_H

#include "minunt.h"
#include "../Solution.h"
#include "../Vertice.h"

void test_setup(void) {
}

void test_teardown(void) {
}

MU_TEST(solution_init) {
    Solution * sol = new Solution( 2, 7.5 );
	mu_check( sol->get_number_paths() == 2 );
    mu_check( sol->get_time_per_path() == 7.5 );
    mu_check( sol->get_total_rewards() == 0.0 );
    mu_check( sol->get_total_time() == 0.0 );
    delete sol;
}

MU_TEST(solution_set_initial_and_final_vertice) {
    Vertice * initial = new Vertice( 0.0, 0.0, 0 );
    Vertice * final = new Vertice( 3.0, 4.0, 0 );
    Solution * sol = new Solution( 2, 7.5 );
    for( int i = 0; i < 2; i++ ){
        sol->add_initial_and_final_vertice( i, initial, final );
    }
    for( int i = 0; i < 2; i++ ){
        mu_check( sol->get_length_of_path( i ) == 2 );
        mu_check( sol->get_time_path( i ) == 5.0 );
        mu_check( sol->get_last_path_vertice_in_path( i )->get_hash() == final->get_hash() );
    }
	mu_check( sol->get_number_paths() == 2 );
    mu_check( sol->get_time_per_path() == 7.5 );
    mu_check( sol->get_total_rewards() == 0.0 );
    mu_check( sol->get_total_time() == 10.0 );
    delete sol;
}

MU_TEST_SUITE(test_suite_solution) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(solution_init);
    MU_RUN_TEST(solution_set_initial_and_final_vertice);
}

#endif