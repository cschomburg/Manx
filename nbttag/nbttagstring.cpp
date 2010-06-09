#include <cstring>

#include "nbttagstring.h"

NbtTagString::NbtTagString(const char *value, const char *name)
    : NbtTag(TAG_String, name)
{
    m_value = new char[strlen(value) + 1];
    strcpy(m_value, value);
}

NbtTagString::~NbtTagString()
{
    delete [] m_value;
}

const char * NbtTagString::value() const
{
    return m_value;
}
