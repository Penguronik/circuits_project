#ifndef PININ_H
#define PININ_H

#include "pinbase.h"
#include "qlist.h"

class PinIn : public PinBase
{
public:

    // Constructors
    PinIn(CircuitComponent *parentCircuitComponent, int index);
    PinIn(CircuitComponent *parentCircuitComponent = nullptr);

    // Getter
    bool state();

//private:
    QList<bool *> inList_;
};

#endif // PININ_H
