#include <cstring>

#include "nbttag.h"

NbtTag::NbtTag(TagType tagType, const char *name)
{
    m_tagType = tagType;

    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}

NbtTag::~NbtTag()
{
    delete [] m_name;
}

NbtTag::TagType NbtTag::tagType() const
{
    return m_tagType;
}

const char * NbtTag::name() const
{
    return m_name;
}
