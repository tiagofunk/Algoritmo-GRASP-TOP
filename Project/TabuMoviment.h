#ifndef TABU_MOVIMENT_H
#define TABU_MOVIMENT_H

class TabuMoviment{
    private:
    int path;
    int path_position;
    int vertice_position;

    public:
        TabuMoviment( int path, int path_position, int vertice_position );

        bool operator==( TabuMoviment &other );
};

#endif