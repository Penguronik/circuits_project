#ifndef PINOUT_H
#define PINOUT_H

#include "pinbase.h"

class PinOut : public PinBase
{
public:

    // Constructors
    PinOut(CircuitComponent *parentCircuitComponent = nullptr);

    // Setter
    void setState(bool state);

    // Getter
    bool state() const;

    // Public Functions
    void updateWire();

};

#endif // PINOUT_H
