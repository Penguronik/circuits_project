#ifndef CIRCUIT_H
#define CIRCUIT_H


#include "pinin.h"
#include "pinout.h"


class Circuit
{
public:
    Circuit(int inSize, int outSize);
    ~Circuit();
    PinIn &in(int index) const;
    void out(int outIndex, Circuit &inCircuit, int inIndex);
    virtual void run() = 0;
    void propogate(int index);
    void propogateAll();
    static void connect(Circuit &inCircuit, int pinInIndex, Circuit &outCircuit, int pinOutIndex);
    static void connect(Circuit *inCircuit, int pinInIndex, Circuit *outCircuit, int pinOutIndex);

    //Getters
    int inSize() const;
    int outSize() const;

//protected:
    int inSize_;
    int outSize_;
    PinIn *pinInArray_;
    PinOut *pinOutArray_;
    Circuit **connectedCircuitArray_; //Consider replacing the out array completely with the connected circuit array

};

#endif // CIRCUIT_H
