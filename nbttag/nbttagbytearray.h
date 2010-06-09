#ifndef NBTTAGBYTEARRAY_H
#define NBTTAGBYTEARRAY_H

#include "nbttag.h"

class NbtTagByteArray : public NbtTag
{
public:
    NbtTagByteArray(const char *value, const int length, const char *name = "");
    ~NbtTagByteArray();

    const char * value() const;
    int length() const;

private:
    char *m_value;
    int m_length;
};

#endif // NBTTAGBYTEARRAY_H
