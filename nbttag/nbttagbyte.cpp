#include "nbttagbyte.h"

NbtTagByte::NbtTagByte(char value, const char *name)
    : NbtTag(TAG_Byte, name)
{
    m_value = value;
}

char NbtTagByte::value() const
{
    return m_value;
}
