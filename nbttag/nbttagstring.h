#ifndef NBTTAGSTRING_H
#define NBTTAGSTRING_H

#include "nbttag.h"

class NbtTagString : public NbtTag
{
public:
    NbtTagString(const char *value, const char *name = "");
    ~NbtTagString();

    const char * value() const;

private:
    char *m_value;
};

#endif // NBTTAGSTRING_H
