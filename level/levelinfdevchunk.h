#ifndef LEVELINFDEVCHUNK_H
#define LEVELINFDEVCHUNK_H

#include "minecraftlevel.h"

class QByteArray;
class QNbtTag;

class LevelInfDevChunk : public MinecraftLevel
{
public:
    LevelInfDevChunk(QNbtTag *root);

    static bool isValid(QNbtTag *root);

    int width();
    int height();
    int length();

    char block(int x, int y, int z);

private:
    QNbtTag *m_root;
    QByteArray m_blocks;
};

#endif // LEVELINFDEVCHUNK_H
