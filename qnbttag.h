#ifndef QNBTTAG_H
#define QNBTTAG_H

#include <QObject>
#include <QVariant>

#include "nbttag/nbttags.h"

class QNbtTag : public QObject
{
Q_OBJECT
public:
    explicit QNbtTag(NbtTag *root, QObject *parent = 0);

    QString name();
    static QString name(NbtTag *tag);

    QVariant operator [](const QString& path);

    QVariant value(const QString& path = "");
    static QVariant value(NbtTag *root, const QString& path);
    static QVariant value(NbtTag *tag);

    bool has(const QString& path = "");
    static bool has(NbtTag *root, const QString& path = "");

    NbtTag * tag(const QString& path);
    static NbtTag * tag(NbtTag *root, const QString& path);

private:
    NbtTag *m_root;
};

#endif // QNBTTAG_H
