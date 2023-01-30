#include "pinbase.h"
#include "circuitcomponent.h"

PinBase::PinBase(CircuitComponent *parentCircuitComponent):
    parentCircuitComponent_{parentCircuitComponent},
    state_{false},
    wireList_{}
{

}

PinBase::~PinBase() {
    delete parentCircuitComponent_;
    parentCircuitComponent_ = nullptr;
    wireList_.clear(); // Expectation is that the wires are deleted from the graphical frontend
}

CircuitComponent *PinBase::parentCircuitComponent() const {
    return parentCircuitComponent_;
}

void PinBase::setParentCircuitComponent(CircuitComponent *parentCircuitComponent) {
    parentCircuitComponent_ = parentCircuitComponent;
}

void PinBase::addWire(Wire *wire) {
    wireList_.append(wire);
}
