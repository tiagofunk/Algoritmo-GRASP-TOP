#ifndef MAPPER_H
#define MAPPER_H

class Mapper{
    private:
        int size;
        bool * keys;

    public:
        Mapper( const int size );
        ~Mapper();

        void insert( int key );
        bool find( int key );
        void erase( int key );

};

#endif