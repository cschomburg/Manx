#include "nbttagdouble.h"

NbtTagDouble::NbtTagDouble(double value, const char *name)
    : NbtTag(TAG_Double, name)
{
    m_value = value;
}

double NbtTagDouble::value() const
{
    return m_value;
}
