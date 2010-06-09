#ifndef NBTTAGSHORT_H
#define NBTTAGSHORT_H

#include "nbttag.h"

class NbtTagShort : public NbtTag
{
public:
    NbtTagShort(short value, const char *name = "");

    short value() const;

private:
    short m_value;
};

#endif // NBTTAGSHORT_H
