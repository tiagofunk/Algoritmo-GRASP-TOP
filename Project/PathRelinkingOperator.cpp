#include "PathRelinkingOperator.h"

PathRelinkingOperator::PathRelinkingOperator():PathRelinking(){}

Solution * PathRelinkingOperator::execute( Solution * start, Solution * end ){
    if( start == NULL && end != NULL ) return end;
    if( start != NULL && end == NULL ) return start;
    if( start == NULL && end == NULL ) return 0; 

    Solution * actual = new Solution( *start );
    Solution * best = new Solution( *start );

    return best;
}