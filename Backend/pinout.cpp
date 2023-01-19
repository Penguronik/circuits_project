#include "pinout.h"
#include "wire.h"

PinOut::PinOut(CircuitComponent *parentCircuitComponent):
    PinBase{parentCircuitComponent}
{

}

void PinOut::setState(bool state) {
    state_ = state;
}

bool PinOut::state() const {
    return state_;
}

void PinOut::updateWire() {
    QList<Wire *>::iterator i{};
    for (i = wireList_.begin(); i != wireList_.end(); ++i) {
        (*i)->setState(state_);
    }
}
