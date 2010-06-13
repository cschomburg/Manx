#include <QtGui>
// #include <QtGui/Application>
// #include "mainwindow.h"

#include "qnbttag.h"
#include "nbttag/nbttags.h"
#include "nbtreader.h"
#include "blockinfo.h"
#include "level/levelindev.h"
#include "maprenderer.h"

void print(const QVariant& variant)
{
    qDebug(variant.toString().toLatin1().data());
}

BlockInfoTable loadBlocks(const QString& blockFile, const QString& textureFile)
{
    BlockInfoTable blocks;

    QPixmap textures(textureFile);

    QFile file(blockFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return blocks;

    while(!file.atEnd()) {
        QString line = file.readLine();
        if(line.at(0) != '#') {
            QStringList info = line.split(",");

            if(info.count() < 4)
                continue;

            char blockID = info.at(0).toInt();
            QString title = info.at(1);
            int textureID = info.at(2).toInt();

            QPixmap texture;
            if(textureID > 0) {
                textureID = textureID-1;
                int tX =  textureID % 16;
                int tY = floor(textureID / 16);
                texture = textures.copy(tX * 16, tY * 16, 16, 16);
            }

            bool ok;
            QColor color = QColor::fromRgba(info.value(3, "ffff0000").toUInt(&ok, 16));

            bool transparent = false;
            bool disabled = false;
            if(info.count() > 4) {
                QString additional = info.at(4);

                transparent = additional.contains("transparent");
                disabled = additional.contains("disabled");
            }

            BlockInfo *block = new BlockInfo();
            block->blockID = blockID;
            block->title = title;
            block->transparent = transparent;
            block->color = color;
            block->texture = texture;
            block->disabled = disabled;

            blocks[blockID] = block;
        }
    }

    return blocks;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
//    w.show();
//    return a.exec();

    NbtReader reader;
    NbtTag *tag = reader.readFile("minecraft/test.mclevel");

    QNbtTag root(tag);

    if(!LevelInDev::isValid(&root)) {
        qWarning("No MinecraftLevel found in file!");
        return 1;
    }
    LevelInDev level(&root);

    BlockInfoTable blocks = loadBlocks("files/blocks.txt", "files/terrain.png");

    MapRenderer renderer;
    renderer.setBlockInfoTable(blocks);
    renderer.setLevel(&level);
    renderer.setDetails(0);

    QImage image(level.width(), level.length(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    if(!renderer.render(&image)) {
        qDebug("Rendering failed");
        return 1;
    }
    image.save("test.png");

    delete tag;
    foreach(BlockInfo *block, blocks)
        delete block;

    return 0;
}
