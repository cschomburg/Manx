#ifndef BLOCKINFO_H
#define BLOCKINFO_H

#include <QString>
#include <QPixmap>
#include <QColor>
#include <QHash>

struct BlockInfo
{
    char blockID;
    QString title;
    QPixmap texture;
    bool isTransparent;
    QColor color;
};

typedef QHash<char, BlockInfo *> BlockInfoTable;

#endif // BLOCKINFO_H
