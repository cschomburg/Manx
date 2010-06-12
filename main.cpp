#include <QtGui/QApplication>
#include "mainwindow.h"

#include "qnbttag.h"
#include "nbttag/nbttags.h"
#include "nbtreader.h"
#include "level/levelindev.h"

void print(const QVariant& variant)
{
    qDebug(variant.toString().toLatin1().data());
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

    if(LevelInDev::isValid(&root))
        qDebug("yay");
    else
        qDebug("noes");

    return 0;
}
