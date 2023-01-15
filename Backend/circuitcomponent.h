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
    ~CircuitComponent();

    // Abstract functions
    virtual void run() = 0;

    // Public functions
    void propogate(int index);
    void propogateAll();

    // Static functions
    static void connect(CircuitComponent &inCircuit, int pinInIndex, CircuitComponent &outCircuit, int pinOutIndex);
    static void connect(CircuitComponent *inCircuit, int pinInIndex, CircuitComponent *outCircuit, int pinOutIndex);
    static void connect(PinBase *pinIn, PinBase *pinOut);

    //Getters
    int inSize() const;
    int outSize() const;
    PinIn *pinInArray() const;
    PinOut *pinOutArray() const;

protected:
    int inSize_;
    int outSize_;
    PinIn *pinInArray_;
    PinOut *pinOutArray_;
    CircuitComponent **connectedCircuitArray_; //Consider replacing the out array completely with the connected circuit array

};

#endif // CIRCUITCOMPONENT_H
