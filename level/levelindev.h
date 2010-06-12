#ifndef LEVELINDEV_H
#define LEVELINDEV_H

#include "minecraftlevel.h"

class QByteArray;
class QNbtTag;

class LevelInDev : public MinecraftLevel
{
public:
    LevelInDev(QNbtTag *root);

    static bool isValid(QNbtTag *root);

    int width();
    int height();
    int length();

    char block(int x, int y, int z);

private:
    QNbtTag *m_root;

    int m_width;
    int m_height;
    int m_length;

    QByteArray m_blocks;
};

#endif // LEVELINDEV_H
