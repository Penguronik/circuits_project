#include "circuitcomponent.h"

class ButtonComponent : public CircuitComponent {
public:

    ButtonComponent():
        CircuitComponent{0, 1},
        state_{false}
    {

    }

    virtual void run() override {
        pinOutArray_[0].setState(state_); // consider switching this to just a 1 output pin system, this is good for now but think about it and the pros/cons
    }

    void setState(bool state) {
        state_ = state;
    }

private:
    bool state_;
};
