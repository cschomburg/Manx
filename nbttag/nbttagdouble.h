#ifndef NBTTAGDOUBLE_H
#define NBTTAGDOUBLE_H

#include "nbttag.h"

class NbtTagDouble : public NbtTag
{
public:
    NbtTagDouble(double value, const char *name = "");

    double value() const;

private:
    double m_value;
};

#endif // NBTTAGDOUBLE_H
