#ifndef OPERATOR_WORST_REMOVE_H
#define OPERATOR_WORST_REMOVE_H

#include "Operator.h"

class OperatorWorstRemove: public Operator{
    private:
        bool is_empty;
        double worst_reward;
        double worst_distance;
        int worst_path;
        int worst_position;

        void initialize();
        void check_if_not_empty( Solution * sol );
        void find_worst( Solution * sol );
        void update_worst( double worst_reward, double worst_distance, int worst_path, int worst_position );
        Solution * remove_worst( Solution * sol );

    public:
        virtual Solution * execute( Solution * sol, vector< Vertice * > unused_vertices );
};

#endif