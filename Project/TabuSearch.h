#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include "LocalSearch.h"
#include "TabuMoviment.h"

class TabuSearch: public LocalSearch {
    private:
        vector< TabuMoviment > tabu_list;

        Solution * generate_neighborhood_and_select( Solution * s, vector< Vertice * > vertices );

    public:
        TabuSearch();
        ~TabuSearch();

        Solution * execute( Solution * sol, vector< Vertice * > vertices );
};

#endif