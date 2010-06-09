#ifndef NBTTAGINT_H
#define NBTTAGINT_H

#include "nbttag.h"

class NbtTagInt : public NbtTag
{
public:
    NbtTagInt(int value, const char *name = "");

    int value() const;

private:
    int m_value;
};

#endif // NBTTAGINT_H
