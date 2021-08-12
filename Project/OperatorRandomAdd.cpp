#include "OperatorRamdomAdd.h"

#include "Utils.h"
#include "main.h"

Solution OperatorRandomAdd::realize_add( Solution sol ){
    this->is_added = false;
    int path = rand() % sol.get_number_paths();
    int position = 1;
    if( sol.get_length_of_path( path ) != 2 ){
        position = rand() % (sol.get_length_of_path( path ) - 2) + 1;
    }
    int vertice_position = rand() % this->unused_vertices.size();
    if( sol.add( path, position, this->unused_vertices[ vertice_position ] ) ){
        this->is_added = true;
    }
    return sol;
}

Solution OperatorRandomAdd::execute( Solution sol, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int count = 0;
    do{
        sol = this->realize_add( sol );
        count++;
    }while( is_added );
    show_log( "number of insertions: " + std::to_string( count ) + "\n", 3 );
    return sol;
}