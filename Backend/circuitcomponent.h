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

    // sets the pin out states based on the pin in states and the component's inner logic
    virtual void run() = 0;

    // Public functions

    // sets pin in state to wire state
    void updateStates();

    // sets wire state to pin out state
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
    PinOut *pinOutArray_; // switch this to QList

};

#endif // CIRCUITCOMPONENT_H
