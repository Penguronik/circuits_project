#include "pinbase.h"

PinBase::PinBase(CircuitComponent *parentCircuitComponent):
    parentCircuitComponent_{parentCircuitComponent},
    state_{false},
    wireList_{}
{

}

CircuitComponent *PinBase::parentCircuitComponent() const{
    return parentCircuitComponent_;
}

void PinBase::setParentCircuitComponent(CircuitComponent *parentCircuitComponent) {
    parentCircuitComponent_ = parentCircuitComponent;
}

void PinBase::addWire(Wire *wire) {
    wireList_.append(wire);
}
