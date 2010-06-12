#include <cstring>
#include <map>

#include "nbttagcompound.h"

using namespace std;


NbtTagCompound::NbtTagCompound(const char *name)
    : NbtTag(TAG_Compound, name)
{
}

NbtTagCompound::~NbtTagCompound()
{
    for(compoundMap::iterator it = m_tags.begin(); it != m_tags.end(); ++it)
        delete it->second;
}

void NbtTagCompound::add(NbtTag *tag)
{
    char *key = new char[strlen(tag->name()) + 1];
    strcpy(key, tag->name());
    m_tags[key] = tag;
}

int NbtTagCompound::length() const
{
    return m_tags.size();
}

NbtTag * NbtTagCompound::at(const char *name)
{
    return m_tags[name];
}

const compoundMap NbtTagCompound::data() const
{
    return m_tags;
}
