#include <vector>

using namespace std;

#include "nbttaglist.h"

NbtTagList::NbtTagList(NbtTag::TagType childTagType, const char *name)
    : NbtTag(TAG_List, name)
{
    m_childTagType = childTagType;
}

NbtTagList::~NbtTagList()
{
    for(unsigned int i=0; i < m_tags.size(); i++)
        delete m_tags.at(i);
}

void NbtTagList::add(NbtTag *tag)
{
    m_tags.push_back(tag);
}

int NbtTagList::length() const
{
    return m_tags.size();
}

NbtTag * NbtTagList::at(int i) const
{
    return m_tags.at(i);
}

NbtTag::TagType NbtTagList::childTagType() const
{
    return m_childTagType;
}
