#ifndef PINOUT_H
#define PINOUT_H

#include "pinbase.h"
#include "qlist.h"
#include <iostream>

class PinOut : public PinBase
{
public:
    PinOut(CircuitComponent *parentCircuitComponent, int index);
    PinOut(CircuitComponent *parentCircuitComponent = nullptr);

    // Setter
    void set(bool state);

//private:
    QList<bool *> outList_;
};

#endif // PINOUT_H
