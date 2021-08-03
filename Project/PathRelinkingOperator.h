#ifndef PATH_RELINKING_OPERATOR_H
#define PATH_RELINKING_OPERATOR_H

#include "PathRelinking.h"

class PathRelinkingOperator: public PathRelinking{
    private:
        bool start_to_end;

    public:
        PathRelinkingOperator( bool start_to_end );
        virtual Solution execute( Solution start, Solution end );
};

#endif