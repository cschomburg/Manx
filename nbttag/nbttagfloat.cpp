#include "nbttagfloat.h"

NbtTagFloat::NbtTagFloat(float value, const char *name)
    : NbtTag(TAG_Float, name)
{
    m_value = value;
}

float NbtTagFloat::value() const
{
    return m_value;
}
