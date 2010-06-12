#include <QStringList>

#include "qnbttag.h"

QNbtTag::QNbtTag(NbtTag *root, QObject *parent)
    : QObject(parent)
{
    m_root = root;
}

QString QNbtTag::name()
{
    return name(m_root);
}

QString QNbtTag::name(NbtTag *tag)
{
    return QString::fromUtf8(tag->name());
}

QVariant QNbtTag::value()
{
    return value(m_root);
}

QVariant QNbtTag::value(const QString& path)
{
    return value(m_root, path);
}

QVariant QNbtTag::value(NbtTag *root, const QString& path)
{
    return value(tag(root, path));
}

QVariant QNbtTag::value(NbtTag *tag)
{
    if(!tag)
        return QVariant();

    switch(tag->tagType()) {
    case NbtTag::TAG_Byte:          return dynamic_cast<NbtTagByte *>(tag)->value(); break;
    case NbtTag::TAG_Short:         return dynamic_cast<NbtTagShort *>(tag)->value(); break;
    case NbtTag::TAG_Int:           return dynamic_cast<NbtTagInt *>(tag)->value(); break;
    case NbtTag::TAG_Long:          return qint64(dynamic_cast<NbtTagLong *>(tag)->value()); break;
    case NbtTag::TAG_Float:         return dynamic_cast<NbtTagFloat *>(tag)->value(); break;
    case NbtTag::TAG_Double:        return dynamic_cast<NbtTagDouble *>(tag)->value(); break;
    case NbtTag::TAG_Byte_Array: {
            NbtTagByteArray *array = dynamic_cast<NbtTagByteArray *>(tag);
            return QByteArray(array->value(), array->length());
            break;
        }
    case NbtTag::TAG_String:        return dynamic_cast<NbtTagString *>(tag)->value(); break;
    default:                        return QVariant(); break;
    }
}

QVariant QNbtTag::operator [](const QString& path)
{
    return value(path);
}

bool QNbtTag::has(const QString& path)
{
    return has(m_root, path);
}

bool QNbtTag::has(NbtTag *root, const QString &path)
{
    return tag(root, path);
}

NbtTag * QNbtTag::tag(const QString& path = "")
{
    return tag(m_root, path);
}

NbtTag * QNbtTag::tag(NbtTag *root, const QString& path)
{
    if(path.isEmpty())
        return root;

    if(!root)
        return 0;

    QString part;
    QString rest;
    int del = path.indexOf(".");

    if(del == -1) {
        part = path;
    } else {
        part = path.left(del);
        rest = path.mid(del+1);
    }

    NbtTag *child = 0;
    bool ok;
    int index = part.toInt(&ok);

    if(ok && root->tagType() == NbtTag::TAG_List) {
        NbtTagList *list = dynamic_cast<NbtTagList *>(root);
        child = list->at(index);
    } else if(root->tagType() == NbtTag::TAG_Compound) {
        NbtTagCompound *compound = dynamic_cast<NbtTagCompound *>(root);
        child = compound->at(part.toUtf8());
    }

    return tag(child, rest);
}

QStringList QNbtTag::childNames()
{
    return childNames(m_root);
}

QStringList QNbtTag::childNames(const QString& path)
{
    return childNames(m_root, path);
}

QStringList QNbtTag::childNames(NbtTag *root, const QString& path)
{
    return childNames(tag(root, path));
}

QStringList QNbtTag::childNames(NbtTag *root)
{
    QStringList names;
    if(!root)
        return names;

    if(root->tagType() == NbtTag::TAG_List) {
        NbtTagList *list = dynamic_cast<NbtTagList *>(root);
        for(unsigned int i=0; i < list->length(); i++)
            names << QString::number(i);
    } else if(root->tagType() == NbtTag::TAG_Compound) {
        NbtTagCompound *compound = dynamic_cast<NbtTagCompound *>(root);
        compoundMap map = compound->data();
        for(compoundMap::iterator it = map.begin(); it != map.end(); ++it)
            names << it->first;
    }

    return names;
}
