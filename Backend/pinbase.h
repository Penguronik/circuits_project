#ifndef PINBASE_H
#define PINBASE_H

#include <QList>

class Wire;

class CircuitComponent; // fix to forward declarations in headers

class PinBase
{
public:

    // Constructor
    PinBase(CircuitComponent *parentCircuitComponent = nullptr);

    // Destructor
    ~PinBase();

    // Public Functions
    void addWire(Wire *wire);
    void removeWire(Wire *wire);

protected:
    bool state_;
    QList<Wire *> wireList_;
};

#endif // PINBASE_H
