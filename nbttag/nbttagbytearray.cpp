#include "nbttagbytearray.h"

NbtTagByteArray::NbtTagByteArray(const char *value, int length, const char *name)
    : NbtTag(TAG_Byte_Array, name)
{
    m_length = length;

    m_value = new char[length];
    for(int i=0; i < length; i++)
        m_value[i] = value[i];
}

NbtTagByteArray::~NbtTagByteArray()
{
    delete [] m_value;
}

const char * NbtTagByteArray::value() const
{
    return m_value;
}

int NbtTagByteArray::length() const
{
    return m_length;
}
