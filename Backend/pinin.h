#ifndef PININ_H
#define PININ_H

#include "pinbase.h"
#include "qlist.h"

class PinIn : public PinBase
{
public:
    PinIn();

    bool state() {
        QList<bool *>::const_iterator i{};
        for (i = inList_.constBegin(); i != inList_.constEnd(); ++i) {
            if(*(*i)) {
                return true;
            }
        }
        return false;
    }

    QList<bool *> inList_;
};

#endif // PININ_H
