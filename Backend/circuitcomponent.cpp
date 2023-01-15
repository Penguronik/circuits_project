#include "circuitcomponent.h"

CircuitComponent::CircuitComponent(int inSize, int outSize):
    inSize_{inSize},
    outSize_{outSize},
    pinInArray_{new PinIn[inSize_]{}},
    pinOutArray_{new PinOut[outSize_]{}},
    connectedCircuitArray_{new CircuitComponent *[outSize_]{nullptr}}
{
    for (int i{0}; i < inSize_; i++) {
        pinInArray_[i].setParentCircuitComponent(this);
        pinInArray_[i].setIndex(i);
    }

    for (int j{0}; j < outSize_; j++) {
        pinOutArray_[j].setParentCircuitComponent(this);
        pinOutArray_[j].setIndex(j);
    }
}

CircuitComponent::~CircuitComponent(){
    delete[] pinInArray_;
    delete[] pinOutArray_;
    delete[] connectedCircuitArray_;
}

void CircuitComponent::connect(CircuitComponent &inCircuit, int pinInIndex, CircuitComponent &outCircuit, int pinOutIndex) {
    bool *state { new bool{false}};
    inCircuit.pinInArray_[pinInIndex].inList_.append(state);
    outCircuit.pinOutArray_[pinOutIndex].outList_.append(state);
    outCircuit.connectedCircuitArray_[pinOutIndex] = &inCircuit;
}

void CircuitComponent::connect(CircuitComponent *inCircuit, int pinInIndex, CircuitComponent *outCircuit, int pinOutIndex) {
    connect(*inCircuit, pinInIndex, *outCircuit, pinOutIndex);
}

void CircuitComponent::connect(PinBase *pinIn, PinBase *pinOut){
    CircuitComponent *inCircuitComponent = pinIn->parentCircuitComponent();
    CircuitComponent *outCircuitComponent = pinOut->parentCircuitComponent();
    connect(inCircuitComponent, pinIn->index(), outCircuitComponent, pinOut->index());
}

void CircuitComponent::propogate(int index){
    connectedCircuitArray_[index]->run();
}

void CircuitComponent::propogateAll(){
    for (int i{0}; i < outSize_; i++) {
        propogate(i);
    }
}

int CircuitComponent::inSize() const
{
    return inSize_;
}

int CircuitComponent::outSize() const
{
    return outSize_;
}

PinIn *CircuitComponent::pinInArray() const {
    return pinInArray_;
}
PinOut *CircuitComponent::pinOutArray() const {
    return pinOutArray_;
}

