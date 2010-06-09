#ifndef NBTTAGLIST_H
#define NBTTAGLIST_H

#include <vector>

#include "nbttag.h"

class NbtTagList : public NbtTag
{
public:
    NbtTagList(NbtTag::TagType childTagType, const char *name = "");
    ~NbtTagList();

    void add(NbtTag *tag);
    NbtTag * at(const int i) const;
    NbtTag::TagType childTagType() const;

private:
    vector<NbtTag*> m_tags;
    NbtTag::TagType m_childTagType;
};

#endif // NBTTAGLIST_H
