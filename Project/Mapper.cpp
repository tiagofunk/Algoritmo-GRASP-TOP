#include "Mapper.h"

#include <stdexcept>

Mapper::Mapper( const int size ){
    this->size = size;
    this->keys = new bool[ size ];
    for( int i = 0; i < size; i++ ){
        this->keys[ i ] = false;
    }
}

Mapper::~Mapper(){
    delete [] this->keys;
}

void Mapper::insert( int key ){
    if( key < 0 || key >= this->size ) throw std::runtime_error("insert: key is invalid\n");
    this->keys[ key ] = true;
}

bool Mapper::find( int key ){
    if( key < 0 || key >= this->size ) throw std::runtime_error("find: key is invalid\n");
    return this->keys[ key ];
}

void Mapper::erase( int key ){
    if( key < 0 || key >= this->size ) throw std::runtime_error("erase: key is invalid\n");
    this->keys[ key ] = false;
}