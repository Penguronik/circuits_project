#ifndef PININ_H
#define PININ_H

#include "pinbase.h"

class PinIn : public PinBase
{
public:

    // Constructors
    PinIn(CircuitComponent *parentCircuitComponent = nullptr);

    // Getter
    bool state() const;

    // Public Functions
    void updateState();

};

#endif // PININ_H
