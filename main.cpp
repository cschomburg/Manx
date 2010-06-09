#include <QtGui/QApplication>
#include "mainwindow.h"

#include "qnbttag.h"
#include "nbttag/nbttags.h"

void print(const QVariant& variant)
{
    qDebug(variant.toString().toLatin1().data());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
        Compound("test") : 3 entries
        {
            List("words", String): 2 entries
            {
                "foo"
                "bar"
            }
            Int("leet") : 1337
            Float("something") : 4815.1623
        }
    */

    NbtTagCompound *comp = new NbtTagCompound("test");

    NbtTagList *list = new NbtTagList(NbtTag::TAG_String, "lol");
    list->add(new NbtTagString("foo"));
    list->add(new NbtTagString("bar"));
    comp->add(list);

    comp->add(new NbtTagInt(1337, "leet"));
    comp->add(new NbtTagFloat(4815.1623, "something"));

    QNbtTag compound(comp);

    if(compound.has("lol")) {
        print(  compound["lol.0"]   );
        print(  compound["lol.1"]   );
    }
    print(  compound["leet"]   );
    print(  compound["something"]   );

//    MainWindow w;
//    w.show();
//    return a.exec();
    return 0;
}
