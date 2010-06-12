#include <cstring>

#include "nbttag.h"

NbtTag::NbtTag(TagType tagType, const char *name)
{
    m_tagType = tagType;

    if(name) {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    } else
        m_name = 0;
}

NbtTag::~NbtTag()
{
    if(m_name)
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
