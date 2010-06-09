#include "nbttagint.h"

NbtTagInt::NbtTagInt(int value, const char *name)
    : NbtTag(TAG_Int, name)
{
    m_value = value;
}

int NbtTagInt::value() const
{
    return m_value;
}
