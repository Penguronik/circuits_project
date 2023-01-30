#include "wire.h"
#include "Backend/pinin.h"
#include "Backend/pinout.h"

Wire::Wire():
    pinIn_{nullptr},
    pinOut_{nullptr}
{

}

Wire::~Wire() {
    pinIn_ = nullptr;
    pinOut_ = nullptr;
}

bool Wire::state() {
    return state_;
}

void Wire::setState(bool state) {
    state_ = state;
}

void Wire::connect(PinIn *pinIn, PinOut *pinOut) {
    pinIn_ = pinIn;
    pinOut_ = pinOut;
    pinIn->addWire(this);
    pinOut->addWire(this);
}
