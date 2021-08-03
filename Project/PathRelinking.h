#ifndef PATH_RELINKING_H
#define PATH_RELINKING_H

#include "Solution.h"

class PathRelinking{
    public:
        virtual Solution execute( Solution start, Solution end )= 0;
};

#endif