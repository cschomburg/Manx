#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <QObject>

#include "blockinfo.h"

class QRect;
class QPaintDevice;
class MinecraftLevel;

class MapRenderer : public QObject
{
Q_OBJECT
public:
    explicit MapRenderer(QObject *parent = 0);

    bool render(QPaintDevice *device, const QRect& viewport = QRect());
    void setLevel(MinecraftLevel *level);
    void setBlockInfoTable(const BlockInfoTable& blockTable);

    void setDepth(int depth = -1);
    void setLayer(int layer = -1);
    void setDetails(int details = 0);

signals:
    void started();
    void finished();
    void progressChanged(float percent);

private:
    MinecraftLevel *m_level;
    BlockInfoTable m_blockTable;

    int m_depth;
    int m_layer;
    int m_details;
};

#endif // MAPRENDERER_H
