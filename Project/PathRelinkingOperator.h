#ifndef PATH_RELINKING_OPERATOR_H
#define PATH_RELINKING_OPERATOR_H

#include "PathRelinking.h"

class PathRelinkingOperator: public PathRelinking{
    private:
        
    public:
        Solution * execute( Solution * start, Solution * end );
};

#endif