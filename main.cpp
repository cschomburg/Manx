#include <QtGui/QApplication>
#include "mainwindow.h"

#include "qnbttag.h"
#include "nbttag/nbttags.h"
#include "nbtreader.h"

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
    NbtTag *tag = reader.readFile("minecraft/bigtest.nbt");

    QNbtTag root(tag);
    foreach(QString name, root.childNames("listTest (compound)"))
        qDebug(name.toLatin1().data());

    return 0;
}
