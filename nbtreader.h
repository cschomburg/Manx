#ifndef NBTREADER_H
#define NBTREADER_H

#include "nbttag/nbttag.h"

class QString;
class QDataStream;

class NbtReader
{
public:
    NbtTag * readFile(const QString& filePath);

private:
    NbtTag * readTag(NbtTag::TagType tagType = NbtTag::TAG_Unknown);
    bool read(void *dest, int bytes);
    char * readString();

    QDataStream m_stream;
};

#endif // NBTREADER_H
