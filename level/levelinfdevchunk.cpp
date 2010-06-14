#include <QByteArray>

#include "qnbttag.h"

#include "levelinfdevchunk.h"

LevelInfDevChunk::LevelInfDevChunk(QNbtTag *root)
{
    m_root = root;
    m_blocks = m_root->value("Level.Blocks").toByteArray();
}

bool LevelInfDevChunk::isValid(QNbtTag *root)
{
    if(root->has("Level.Blocks"))
        return true;
    else
        return false;
}

int LevelInfDevChunk::width()
{
    return 16;
}

int LevelInfDevChunk::height()
{
    return 128;
}

int LevelInfDevChunk::length()
{
    return 16;
}

char LevelInfDevChunk::block(int x, int y, int z)
{
    if(x >= width() || z >= length() || y >= height())
        return -1;

    int pos = y + (z * width() + x) * height();
    return m_blocks.at(pos);
}
