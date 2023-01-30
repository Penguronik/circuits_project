#ifndef CIRCUITCOMPONENT_H
#define CIRCUITCOMPONENT_H


#include "pinin.h"
#include "pinout.h"

class CircuitComponent
{
public:

    // Constructor
    CircuitComponent(int inSize, int outSize);

    // Destructor
    virtual ~CircuitComponent();

    // Abstract functions
    virtual void run() = 0;

    // Public functions
    void updateStates();
    void updateWires();

    // Getters
    int inSize() const;
    int outSize() const;
    PinIn *pinInArray() const;
    PinOut *pinOutArray() const;

protected:
    int inSize_;
    int outSize_;
    PinIn *pinInArray_;
    PinOut *pinOutArray_;

};

#endif // CIRCUITCOMPONENT_H
