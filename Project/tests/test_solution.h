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
        bool result = sol->add_initial_and_final_vertice( i, initial, final );
        mu_check( result == true );
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
    delete initial;
    delete final;
    delete sol;
}

MU_TEST(solution_set_initial_and_final_vertice_fail) {
    Vertice * initial = new Vertice( 0.0, 0.0, 0 );
    Vertice * final = new Vertice( 3.0, 4.0, 0 );
    Solution * sol = new Solution( 2, 7.5 );
    bool result = sol->add_initial_and_final_vertice( -1, initial, final );
    mu_check( result == false );
    result = sol->add_initial_and_final_vertice( 0, initial, 0 );
    mu_check( result == false );
    result = sol->add_initial_and_final_vertice( 0, 0, final );
    mu_check( result == false );
    result = sol->add_initial_and_final_vertice( 0, initial, final );
    mu_check( result == true );
    result = sol->add_initial_and_final_vertice( 1, initial, final );
    mu_check( result == true );
    result = sol->add_initial_and_final_vertice( 2, initial, final );
    mu_check( result == false );
    delete initial;
    delete final;
    delete sol;
}

MU_TEST(solution_add_vertice_in_path) {
    Vertice * initial = new Vertice( 0.0, 0.0, 0 );
    Vertice * final = new Vertice( 3.0, 4.0, 0 );
    Vertice * new_v = new Vertice( 6.0, 8.0, 5 );
    Solution * sol = new Solution( 2, 7.5 );
    for( int i = 0; i < 2; i++ ){
        sol->add_initial_and_final_vertice( i, initial, final );
    }
    bool result = sol->add( 0, new_v );
    mu_check( result == true );
    mu_check( sol->get_length_of_path( 0 ) == 3 );
    mu_check( sol->get_time_path( 0 ) == 15.0 );
    mu_check( sol->get_last_path_vertice_in_path( 0 )->get_hash() == final->get_hash() );

    mu_check( sol->get_length_of_path( 1 ) == 2 );
    mu_check( sol->get_time_path( 1 ) == 5.0 );
    mu_check( sol->get_last_path_vertice_in_path( 1 )->get_hash() == final->get_hash() );

	mu_check( sol->get_number_paths() == 2 );
    mu_check( sol->get_time_per_path() == 7.5 );
    mu_check( sol->get_total_rewards() == 5.0 );
    mu_check( sol->get_total_time() == 20.0 );
    
    delete initial;
    delete final;
    delete new_v;
    delete sol;
}

MU_TEST(solution_add_vertice_in_path_fail) {
    Vertice * initial = new Vertice( 0.0, 0.0, 0 );
    Vertice * final = new Vertice( 3.0, 4.0, 0 );
    Vertice * new_v = new Vertice( 6.0, 8.0, 5 );
    Solution * sol = new Solution( 2, 7.5 );
    for( int i = 0; i < 2; i++ ){
        sol->add_initial_and_final_vertice( i, initial, final );
    }
    bool result = sol->add( 2, new_v );
    mu_check( result == false );
    result = sol->add( 2, 0 );
    mu_check( result == false );
    mu_check( sol->get_length_of_path( 0 ) == 2 );
    mu_check( sol->get_time_path( 0 ) == 5.0 );
    mu_check( sol->get_last_path_vertice_in_path( 0 )->get_hash() == final->get_hash() );

    mu_check( sol->get_length_of_path( 1 ) == 2 );
    mu_check( sol->get_time_path( 1 ) == 5.0 );
    mu_check( sol->get_last_path_vertice_in_path( 1 )->get_hash() == final->get_hash() );

	mu_check( sol->get_number_paths() == 2 );
    mu_check( sol->get_time_per_path() == 7.5 );
    mu_check( sol->get_total_rewards() == 0.0 );
    mu_check( sol->get_total_time() == 10.0 );
    
    delete initial;
    delete final;
    delete new_v;
    delete sol;
}

MU_TEST_SUITE(test_suite_solution) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(solution_init);
    MU_RUN_TEST(solution_set_initial_and_final_vertice);
    MU_RUN_TEST(solution_set_initial_and_final_vertice_fail);
    MU_RUN_TEST(solution_add_vertice_in_path);
    MU_RUN_TEST(solution_add_vertice_in_path_fail);
}

#endif