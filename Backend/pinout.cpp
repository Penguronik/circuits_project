#include "pinout.h"

PinOut::PinOut(CircuitComponent *parentCircuitComponent, int index):
    PinBase{parentCircuitComponent, index}
{

}

PinOut::PinOut(CircuitComponent *parentCircuitComponent):
    PinBase{parentCircuitComponent}
{

}

void PinOut::set(bool state) {
    QList<bool *>::iterator i{};
    for (i = outList_.begin(); i != outList_.end(); ++i) {
        *(*i) = state;
    }
}
