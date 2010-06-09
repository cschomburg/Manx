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

QVariant QNbtTag::value(NbtTag *root, const QString& path)
{
    return value(tag(root, path));
}

QVariant QNbtTag::value(const QString& path)
{
    return value(m_root, path);
}

QVariant QNbtTag::value(NbtTag *tag)
{
    if(!tag)
        return QVariant();

    switch(tag->tagType()) {
    case NbtTag::TAG_Byte:          return reinterpret_cast<NbtTagByte *>(tag)->value(); break;
    case NbtTag::TAG_Short:         return reinterpret_cast<NbtTagShort *>(tag)->value(); break;
    case NbtTag::TAG_Int:           return reinterpret_cast<NbtTagInt *>(tag)->value(); break;
    case NbtTag::TAG_Long:          return qint64(reinterpret_cast<NbtTagLong *>(tag)->value()); break;
    case NbtTag::TAG_Float:         return reinterpret_cast<NbtTagFloat *>(tag)->value(); break;
    case NbtTag::TAG_Double:        return reinterpret_cast<NbtTagDouble *>(tag)->value(); break;
    case NbtTag::TAG_Byte_Array: {
            NbtTagByteArray *array = reinterpret_cast<NbtTagByteArray *>(tag);
            return QByteArray(array->value(), array->length());
            break;
        }
    case NbtTag::TAG_String:        return reinterpret_cast<NbtTagString *>(tag)->value(); break;
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
        NbtTagList *list = reinterpret_cast<NbtTagList *>(root);
        child = list->at(index);
    } else if(root->tagType() == NbtTag::TAG_Compound) {
        NbtTagCompound *compound = reinterpret_cast<NbtTagCompound *>(root);
        child = compound->at(part.toUtf8());
    }

    return tag(child, rest);
}
