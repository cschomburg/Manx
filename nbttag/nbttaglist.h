#ifndef NBTTAGLIST_H
#define NBTTAGLIST_H

#include <vector>

#include "nbttag.h"

typedef vector<NbtTag *> listVector;

class NbtTagList : public NbtTag
{
public:
    NbtTagList(NbtTag::TagType childTagType, const char *name = "");
    ~NbtTagList();

    void add(NbtTag *tag);
    int length() const;
    NbtTag * at(const int i) const;
    NbtTag::TagType childTagType() const;

private:
    listVector m_tags;
    NbtTag::TagType m_childTagType;
};

#endif // NBTTAGLIST_H
