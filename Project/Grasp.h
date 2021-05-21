#ifndef GRASP_H
#define GRASP_H

#include "Solution.h"
#include "Instance.h"

class GRASP{
    private:
        Instance * instance;

        Solution * random_greedy( int seed );
        Solution local_search( Solution s );

        Solution path_relinking( Solution start, Solution end );

    public:
        GRASP( Instance * instance );
        Solution execute();
        
};

#endif