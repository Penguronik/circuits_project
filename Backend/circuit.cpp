#include "circuit.h"

Circuit::Circuit(int inSize, int outSize):
    inSize_{inSize},
    outSize_{outSize},
    pinInArray_{new PinIn[inSize_]{}},
    pinOutArray_{new PinOut[outSize_]{}},
    connectedCircuitArray_{new Circuit *[outSize_]{nullptr}}
{

}

Circuit::~Circuit(){
    delete[] pinInArray_;
    delete[] pinOutArray_;
    delete[] connectedCircuitArray_;
}

void Circuit::connect(Circuit &inCircuit, int pinInIndex, Circuit &outCircuit, int pinOutIndex) {
    bool *state { new bool{false}};
    inCircuit.pinInArray_[pinInIndex].inList_.append(state);
    outCircuit.pinOutArray_[pinOutIndex].outList_.append(state);
    outCircuit.connectedCircuitArray_[pinOutIndex] = &inCircuit;
}

void Circuit::connect(Circuit *inCircuit, int pinInIndex, Circuit *outCircuit, int pinOutIndex) {
    connect(*inCircuit, pinInIndex, *outCircuit, pinOutIndex);
}

void Circuit::propogate(int index){
    connectedCircuitArray_[index]->run();
}

void Circuit::propogateAll(){
    for (int i{0}; i < outSize_; i++) {
        propogate(i);
    }
}

int Circuit::inSize() const
{
    return inSize_;
}

int Circuit::outSize() const
{
    return outSize_;
}


