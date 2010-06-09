#ifndef NBTTAGBYTE_H
#define NBTTAGBYTE_H

#include "nbttag.h"

class NbtTagByte : public NbtTag
{
public:
    NbtTagByte(const char value, const char *name = "");

    char value() const;

private:
    char m_value;
};

#endif // NBTTAGBYTE_H
