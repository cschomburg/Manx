#ifndef NBTTAGLONG_H
#define NBTTAGLONG_H

#include "nbttag.h"

class NbtTagLong : public NbtTag
{
public:
    NbtTagLong(long value, const char *name = "");

    long value() const;

private:
    long m_value;
};

#endif // NBTTAGLONG_H
