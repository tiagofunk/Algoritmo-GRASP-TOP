#ifndef MAPPER_H
#define MAPPER_H

#include <vector>
using std::vector;

#include <string>
using std::string;

class Mapper{
    private:
        int size;
        vector< bool > keys;

    public:
        Mapper();
        ~Mapper();

        void resize( int size );
        void insert( int key );
        bool find( int key );
        void erase( int key );

        string to_string();

};

#endif