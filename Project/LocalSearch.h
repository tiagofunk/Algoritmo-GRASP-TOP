#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "Solution.h"

class LocalSearch{
    public:
        virtual Solution * execute( Solution * sol ) = 0;

};

#endif