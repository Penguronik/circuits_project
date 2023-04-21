#include "circuitcomponent.h"
#include "qdebug.h"
#include <gpiod.h>
#include <QList>

class ButtonComponent : public CircuitComponent {
public:

    ButtonComponent():
        CircuitComponent{0, 1},
        state_{false}
    {

    }

    virtual void run() override {
        pinOutArray_[0].setState(state_);
    }

    void setState(bool state) {
        state_ = state;
    }

private:
    bool state_;
};

// Singleton design pattern applied for CircuitIn and CircuitOut in order to interface properly with GPIO
class CircuitIn : public CircuitComponent {
public:

    CircuitIn(gpiod_chip *chip, int inSize):
        CircuitComponent{0, inSize},
        gpiodLinesList_{}
    {
        gpiodLinesList_.append(gpiod_chip_get_line(chip, 16));
        gpiodLinesList_.append(gpiod_chip_get_line(chip, 17));
        gpiodLinesList_.append(gpiod_chip_get_line(chip, 18));

        gpiod_line_request_input(gpiodLinesList_.at(0), "circuits_project");
        gpiod_line_request_input(gpiodLinesList_.at(1), "circuits_project");
        gpiod_line_request_input(gpiodLinesList_.at(2), "circuits_project");
    }

    virtual void run() override {
        for (int i{}; i < outSize_; i++) { // outSize_ is set to inSize value due to nomenclature of CircuitComponent
            pinOutArray_[i].setState(gpiod_line_get_value(gpiodLinesList_.at(i)));
        }
    }

    void run(bool input[]) {
        for (int i{}; i < outSize_; i++) {
            pinOutArray_[i].setState(input[i]);
        }
    }

private:
    QList<gpiod_line *> gpiodLinesList_;
};

class CircuitOut : public CircuitComponent {
public:

    CircuitOut(gpiod_chip *chip, int outSize):
        CircuitComponent{outSize, 0},
        gpiodLinesList_{}
    {   
        gpiodLinesList_.append(gpiod_chip_get_line(chip, 24));
        gpiodLinesList_.append(gpiod_chip_get_line(chip, 25));
        gpiodLinesList_.append(gpiod_chip_get_line(chip, 26));

        gpiod_line_request_output(gpiodLinesList_.at(0), "circuits_project", 0);
        gpiod_line_request_output(gpiodLinesList_.at(1), "circuits_project", 0);
        gpiod_line_request_output(gpiodLinesList_.at(2), "circuits_project", 0);
    }

    virtual void run() override {
        for (int i{}; i < inSize_; i++) { // outSize_ is set to inSize value due to nomenclature of CircuitComponent
            gpiod_line_set_value(gpiodLinesList_.at(i), pinInArray_[i].state());
        }
    }

private:
    QList<gpiod_line *> gpiodLinesList_;
};
