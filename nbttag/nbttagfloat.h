#ifndef NBTTAGFLOAT_H
#define NBTTAGFLOAT_H

#include "nbttag.h"

class NbtTagFloat : public NbtTag
{
public:
    NbtTagFloat(float value, const char *name = "");

    float value() const;

private:
    float m_value;
};

#endif // NBTTAGFLOAT_H
