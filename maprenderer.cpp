#include <QPaintDevice>
#include <QPainter>

#include "level/minecraftlevel.h"

#include "maprenderer.h"

MapRenderer::MapRenderer(QObject *parent) :
    QObject(parent)
{
    m_layer = -1;
    m_depth = -1;
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

    QPainter painter(device);
    float xScale = float(device->width()) / drawRect.width();
    float yScale = float(device->height()) / drawRect.height();
    painter.scale(xScale, yScale);

    for(int x = drawRect.left(); x <= drawRect.right(); x++) {
        for(int z = drawRect.top(); z <= drawRect.bottom(); z++) {
            for(int y = qMin(m_level->height(), layer); y >= qMax(0, layer-depth); y--) {

                char blockID = m_level->block(x, y, z);
                BlockInfo *block = m_blockTable.value(blockID, 0);

                if(block) {
                    if(block->color.isValid() && block->color.alpha() > 0)
                        painter.fillRect(x, z, x+1, z+1, block->color);

                    if(!block->isTransparent)
                        break;
                }
            }
        }

        float progress = float(x-drawRect.left()) / drawRect.width();
        emit progressChanged(progress);
    }

    emit finished();
    return true;
}
