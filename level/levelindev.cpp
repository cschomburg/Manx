#include <QByteArray>

#include "qnbttag.h"

#include "levelindev.h"

LevelInDev::LevelInDev(QNbtTag *root)
{
    m_root = root;

    m_width = m_root->value("Map.Width").toInt();
    m_height = m_root->value("Map.Height").toInt();
    m_length = m_root->value("Map.Length").toInt();

    m_blocks = m_root->value("Map.Blocks").toByteArray();
}

bool LevelInDev::isValid(QNbtTag *root)
{
    if(root->name() == "MinecraftLevel" && root->has("Map.Blocks"))
        return true;
    else
        return false;
}

int LevelInDev::width()
{
    return m_width;
}

int LevelInDev::height()
{
    return m_height;
}

int LevelInDev::length()
{
    return m_length;
}

char LevelInDev::block(int x, int y, int z)
{
    if(x >= width() || z >= length() || y >= height())
        return -1;

    int pos = x + (y * length() + z) * width();
    return m_blocks.at(pos);
}
