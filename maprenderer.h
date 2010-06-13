#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <QThread>

#include "blockinfo.h"

class QRect;
class QPainter;
class MinecraftLevel;

class MapRenderer : public QThread
{
Q_OBJECT
public:
    explicit MapRenderer(QObject *parent = 0);

    void render(const QRect& viewport = QRect());
    void setLevel(MinecraftLevel *level);
    void setBlockInfoTable(const BlockInfoTable& blockTable);

    void setDepth(int depth = -1);
    void setLayer(int layer = -1);
    void setDetails(int details = 0);

    void run();

signals:
    void renderedImage(const QImage& image, const QRect& viewport);
    void progressChanged(float percent);

protected:
    bool renderBlock(QPainter &painter, BlockInfo *block, int x, int z, int details, qreal depth);

private:
    MinecraftLevel *m_level;
    BlockInfoTable m_blockTable;

    QRect m_viewport;

    int m_depth;
    int m_layer;
    int m_details;
};

#endif // MAPRENDERER_H
