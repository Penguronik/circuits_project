#ifndef WIRE_H
#define WIRE_H


class PinIn;
class PinOut;

class Wire
{
public:
    Wire();

    ~Wire();

    bool state();

    void setState(bool state);

    void connect(PinIn *pinIn, PinOut *pinOut);

private:
    bool state_;
    PinIn *pinIn_;
    PinOut *pinOut_;
};

#endif // WIRE_H
