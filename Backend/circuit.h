#ifndef CIRCUIT_H
#define CIRCUIT_H


class Circuit
{
public:
    Circuit(int stateSize, int outSize);
    ~Circuit();
    bool &in(int index) const;
    void out(int outIndex, Circuit &inCircuit, int inIndex);
    virtual void run() = 0;
    void propogate(int index);
    void propogateAll();

    //Getters
    int stateSize() const;
    int outSize() const;

protected:
    int stateSize_;
    int outSize_;
    bool *stateArray_;
    bool **outArray_;
    Circuit **connectedCircuitArray_; //Consider replacing the out array completely with the connected circuit array

};

#endif // CIRCUIT_H
