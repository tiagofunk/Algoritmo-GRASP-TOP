#ifndef INSTANCE_READER_H
#define INSTANCE_READER_H

#include <string>

#include "Instance.h"
#include "Vertice.h"

class InstanceReader{
private:
    std::string file_name;

public:
    InstanceReader(std::string file_name);
    ~InstanceReader();

    void read();
};


#endif