#include "nbttagshort.h"

NbtTagShort::NbtTagShort(short value, const char *name)
    : NbtTag(TAG_Byte, name)
{
    m_value = value;
}

short NbtTagShort::value() const
{
    return m_value;
}
