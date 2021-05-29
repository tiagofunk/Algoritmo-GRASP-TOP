#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include "LocalSearch.h"

class TabuSearch: public LocalSearch {
    private:
        vector< Solution * > generate_neighborhood( Solution * s );
        Solution * selectNeighbor( vector< Solution * > neighborhood );

    public:
        TabuSearch();
        ~TabuSearch();

        Solution * execute( Solution * sol );
};

#endif