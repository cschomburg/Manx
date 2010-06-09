#include "nbttaglong.h"

NbtTagLong::NbtTagLong(long value, const char *name)
    : NbtTag(TAG_Long, name)
{
    m_value = value;
}

long NbtTagLong::value() const
{
    return m_value;
}
