#include "pinin.h"
#include "wire.h"

PinIn::PinIn(CircuitComponent *parentCircuitComponent):
    PinBase{parentCircuitComponent}
{

}

bool PinIn::state() const{
    return state_;
}

void PinIn::updateState() {
    QList<Wire *>::const_iterator i{};
    for (i = wireList_.constBegin(); i != wireList_.constEnd(); ++i) {
        if((*i)->state()) {
            state_ = true;
            return;
        }
    }
    state_ = false;
}
