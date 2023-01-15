#ifndef PINBASE_H
#define PINBASE_H

class CircuitComponent; // fix to forward declarations in headers

class PinBase
{
public:

    // Constructor
    PinBase(CircuitComponent *parentCircuitComponent, int index);
    PinBase(CircuitComponent *parentCircuitComponent = nullptr);

    // Getters
    CircuitComponent *parentCircuitComponent() const;
    int index() const;

    // Setters
    void setParentCircuitComponent(CircuitComponent *parentCircuitComponent);
    void setIndex(int index);

protected:
    CircuitComponent *parentCircuitComponent_;
    int index_;
};

#endif // PINBASE_H
