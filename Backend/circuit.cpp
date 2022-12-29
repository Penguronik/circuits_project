#include "circuit.h"

Circuit::Circuit(int stateSize, int outSize):
    stateSize_{stateSize},
    outSize_{outSize},
    stateArray_{new bool[stateSize_]{false}},
    outArray_{new bool *[outSize_]{nullptr}},
    connectedCircuitArray_{new Circuit *[outSize_]{nullptr}}
{

}

Circuit::~Circuit(){
    delete[] stateArray_;
    delete[] outArray_;
    delete[] connectedCircuitArray_;
}

bool &Circuit::in(int index) const{
    return stateArray_[index];
}

void Circuit::out(int outIndex, Circuit &inCircuit, int inIndex){
    outArray_[outIndex] = &inCircuit.stateArray_[inIndex];
    connectedCircuitArray_[outIndex] = &inCircuit;
}

void Circuit::propogate(int index){
    connectedCircuitArray_[index]->run();
}

void Circuit::propogateAll(){
    for (int i{0}; i < outSize_; i++) {
        propogate(i);
    }
}

int Circuit::stateSize() const
{
    return stateSize_;
}

int Circuit::outSize() const
{
    return outSize_;
}


