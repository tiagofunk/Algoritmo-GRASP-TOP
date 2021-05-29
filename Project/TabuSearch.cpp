#include "TabuSearch.h"

#include "TabuMoviment.h"

TabuSearch::TabuSearch():LocalSearch(){
}

TabuSearch::~TabuSearch(){
}

Solution * TabuSearch::execute( Solution * s ){
    bool is_moved = false;
    Solution * best = new Solution( *s );
    Solution * actual = new Solution( *s );
    vector< TabuMoviment > tabu_list;

    do{
        actual = selectNeighbor( generate_neighborhood( actual ) );
        if( best->get_total_rewards() < actual->get_total_rewards() ){
            delete best;
            best = new Solution( *actual );
            is_moved = true;
        }
        //tabu_list.push_back( 0 );

    }while( is_moved );

    return best;
}

vector< Solution * > TabuSearch::generate_neighborhood( Solution * s ){
    vector< Solution * > sol;
    sol.push_back( s );
    return sol;
}

Solution * TabuSearch::selectNeighbor( vector< Solution * > neighborhood ){
    return neighborhood[ 0 ];
}