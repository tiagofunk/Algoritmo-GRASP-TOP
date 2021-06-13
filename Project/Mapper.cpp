#include "Mapper.h"

#include <stdexcept>
#include <iostream>

Mapper::Mapper(){
    this->size = 64;
    this->keys.resize( this->size );
    for( int i = 0; i < this->size; i++ ){
        this->keys[ i ] = false;
    }
}

Mapper::~Mapper(){}

void Mapper::resize( int size ){
    this->size = size;
    this->keys.resize( this->size );
    for( int i = 0; i < this->size; i++ ){
        this->keys[ i ] = false;
    }
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

string Mapper::to_string(){
    string s = "";
    for( int i = 0; i < this->size; i++ ){
        if( this->keys[ i ] ){
            s += std::to_string( i ) + " ";
        }
    }
    if( s == "" ) return "empty";
    return s;
}