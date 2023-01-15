#include "pinin.h"

PinIn::PinIn(CircuitComponent *parentCircuitComponent, int index):
    PinBase{parentCircuitComponent, index}
{

}

PinIn::PinIn(CircuitComponent *parentCircuitComponent):
    PinBase{parentCircuitComponent}
{

}

bool PinIn::state() {
    QList<bool *>::const_iterator i{};
    for (i = inList_.constBegin(); i != inList_.constEnd(); ++i) {
        if(*(*i)) {
            return true;
        }
    }
    return false;
}
