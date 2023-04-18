#include "wire.h"
#include "Backend/pinin.h"
#include "Backend/pinout.h"

Wire::Wire():
    state_{false},
    pinIn_{nullptr},
    pinOut_{nullptr}
{

}

Wire::~Wire() {
    disconnect();
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

void Wire::disconnect() {
    if (pinIn_) pinIn_->removeWire(this);
    if (pinOut_) pinOut_->removeWire(this);
    pinIn_ = nullptr;
    pinOut_ = nullptr;
}
