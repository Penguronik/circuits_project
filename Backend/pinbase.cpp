#include "pinbase.h"

PinBase::PinBase(CircuitComponent *parentCircuitComponent):
    parentCircuitComponent_{parentCircuitComponent}
{

}

PinBase::PinBase(CircuitComponent *parentCircuitComponent, int index):
    parentCircuitComponent_{parentCircuitComponent},
    index_{index}
{

}

CircuitComponent *PinBase::parentCircuitComponent() const{
    return parentCircuitComponent_;
}

void PinBase::setParentCircuitComponent(CircuitComponent *parentCircuitComponent) {
    parentCircuitComponent_ = parentCircuitComponent;
}

int PinBase::index() const
{
    return index_;
}

void PinBase::setIndex(int index)
{
    index_ = index;
}
