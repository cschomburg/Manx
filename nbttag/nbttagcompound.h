#ifndef NBTTAGCOMPOUND_H
#define NBTTAGCOMPOUND_H

#include <map>

#include "nbttag.h"

using namespace std;

struct cmp_str
{
    bool operator()(char const *a, char const *b)
    {
        return strcmp(a, b) < 0;
    }
};

class NbtTagCompound : public NbtTag
{
public:
    NbtTagCompound(const char *name = "");
    ~NbtTagCompound();

    void add(NbtTag *tag);
    NbtTag * at(const char *name);

private:
    map<const char *, NbtTag *, cmp_str> m_tags;
};

#endif // NBTTAGCOMPOUND_H
