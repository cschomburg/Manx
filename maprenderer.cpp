#include <QPaintDevice>
#include <QPainter>

#include "level/minecraftlevel.h"

#include "maprenderer.h"

MapRenderer::MapRenderer(QObject *parent) :
    QObject(parent)
{
    m_layer = -1;
    m_depth = -1;
    m_details = 0;
}

void MapRenderer::setBlockInfoTable(const BlockInfoTable &blockTable)
{
    m_blockTable = blockTable;
}

void MapRenderer::setLevel(MinecraftLevel *level)
{
    m_level = level;
}

void MapRenderer::setDepth(int depth)
{
    m_depth = depth;
}

void MapRenderer::setLayer(int layer)
{
    m_layer = layer;
}

void MapRenderer::setDetails(int details)
{
    m_details = details;
}

bool MapRenderer::render(QPaintDevice *device, const QRect& viewport)
{
    if(!m_level || m_blockTable.isEmpty())
        return false;

    emit started();

    QRect levelRect(0, 0, m_level->width(), m_level->length());
    QRect drawRect;

    if(viewport.isEmpty())
        drawRect = levelRect;
    else
        drawRect = viewport.intersected(levelRect);

    int layer = m_layer;
    if(layer == -1)
        layer = m_level->height();

    int depth = m_depth;
    if(depth == -1)
        depth = m_level->height();

    int xOffset = drawRect.left();
    int zOffset = drawRect.top();

    QPainter painter(device);
    float xScale = float(device->width()) / drawRect.width();
    float zScale = float(device->height()) / drawRect.height();
    painter.scale(xScale, zScale);

    for(int x = 0; x < drawRect.width(); x++) {
        for(int z = 0; z < drawRect.height(); z++) {
            for(int y = qMin(m_level->height(), layer); y >= qMax(0, layer-depth); y--) {

                char blockID = m_level->block(x + xOffset, y, z + zOffset);
                BlockInfo *block = m_blockTable.value(blockID, 0);

                if(block) {
                    if(m_details == 1) {
                        if(!block->texture.isNull())
                            painter.drawPixmap(x, z, x+1, z+1, block->texture);
                    } else if(block->color.isValid() && block->color.alpha() > 0) {
                            painter.fillRect(x, z, x+1, z+1, block->color);
                    }

                    if(!block->isTransparent)
                        break;
                }

            }
            float progress = (float(z) / drawRect.height() + x) / drawRect.width();
            emit progressChanged(progress);
            qDebug("%.2f%% rendered", progress * 100);
        }
    }

    emit finished();
    return true;
}
