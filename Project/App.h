#ifndef APP_H
#define APP_H

#include <time.h>

#include "ArgumentReader.h"
#include "SolutionGeneration.h"
#include "Operator.h"
#include "LocalSearch.h"
#include "PathRelinking.h"
#include "Grasp.h"
#include "main.h"

class App{
    private:
        int seed;
        string file;
        clock_t initial_time;
        clock_t final_time;
        clock_t total_time;

        ArgumentReader * ar;
        SolutionGeneration * sg;
        vector< Operator * > operators;
        LocalSearch * ls;
        PathRelinking * pr;
        GRASP * grasp;
        Solution * sol;

        void initialize_timer();
        void create_seed();
        void read_instance();
        void create_solution_generator();
        void create_operators();
        void create_local_search();
        void create_path_relinking();
        void create_and_execute_grasp();
        void finalize_timer();
        void show_results();

    public:
        App( ArgumentReader * ar );
        void execute();
};

#endif