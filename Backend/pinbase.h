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

    // Getters
    CircuitComponent *parentCircuitComponent() const;

    // Setters
    void setParentCircuitComponent(CircuitComponent *parentCircuitComponent);

    // Public Functions
    void addWire(Wire *wire);

protected:
    CircuitComponent *parentCircuitComponent_;
    bool state_;
    QList<Wire *> wireList_;
};

#endif // PINBASE_H
