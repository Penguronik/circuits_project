#ifndef INTERFACE_H
#define INTERFACE_H

#include "circuit.h"

class Interface
{
public:
    Interface();
    ~Interface();
    Circuit newCircuit();
};

#endif // INTERFACE_H
