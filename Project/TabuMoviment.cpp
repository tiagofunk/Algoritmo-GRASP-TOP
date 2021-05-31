#include "TabuMoviment.h"

TabuMoviment::TabuMoviment( int path, int path_position, int vertice_position ){
    this->path = path;
    this->path_position = path_position;
    this->vertice_position = vertice_position;
}

bool TabuMoviment::operator==( TabuMoviment &other ){
    return this->path == other.path
        && this->path_position == other.path_position
        && this->vertice_position == other.vertice_position;
}