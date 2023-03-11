#include "pinbase.h"
#include "circuitcomponent.h"

PinBase::PinBase(CircuitComponent *parentCircuitComponent):
    state_{false},
    wireList_{}
{

}

PinBase::~PinBase() {
    wireList_.clear(); // Expectation is that the wires are deleted from the graphical frontend
}

void PinBase::addWire(Wire *wire) {
    wireList_.append(wire);
}

void PinBase::removeWire(Wire *wire) {
    wireList_.removeAll(wire);
}
