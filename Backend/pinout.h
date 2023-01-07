#ifndef PINOUT_H
#define PINOUT_H

#include "pinin.h"
#include "pinbase.h"
#include "qlist.h"
#include <iostream>

class PinOut : public PinBase
{
public:
    PinOut();

    void set(bool state) {
        QList<bool *>::iterator i{};
        for (i = outList_.begin(); i != outList_.end(); ++i) {
            *(*i) = state;
        }

    }

    QList<bool *> outList_;
};

#endif // PINOUT_H
