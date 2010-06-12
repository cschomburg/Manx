#ifndef NBTTAG_H
#define NBTTAG_H

class NbtTag
{
public:
    enum TagType {
        TAG_End,
        TAG_Byte,
        TAG_Short,
        TAG_Int,
        TAG_Long,
        TAG_Float,
        TAG_Double,
        TAG_Byte_Array,
        TAG_String,
        TAG_List,
        TAG_Compound,
        TAG_Unknown,
    };

    NbtTag(TagType tagType = TAG_Unknown, const char *name = "");
    virtual ~NbtTag();

    TagType tagType() const;
    const char* name() const;

private:
    char *m_name;
    TagType m_tagType;
};

#endif // NBTTAG_H
