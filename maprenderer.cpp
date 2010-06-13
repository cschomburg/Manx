#include <QPaintDevice>
#include <QPainter>

#include "level/minecraftlevel.h"

#include "maprenderer.h"

MapRenderer::MapRenderer(QObject *parent) :
    QThread(parent)
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

void MapRenderer::render(const QRect& viewport)
{
    m_viewport = viewport;

    if(!isRunning())
        start(LowPriority);
}

void MapRenderer::run()
{
    // Copy member variables
    // We're running threaded, after all
    MinecraftLevel *level = m_level;

    QRect viewport = m_viewport;

    int layer = m_layer;
    int depth = m_depth;
    int details = m_details;
    BlockInfoTable blockTable = m_blockTable;

    // Calculate variables
    QRect levelRect(0, 0, level->width(), level->length());
    if(viewport.isEmpty())
       viewport = levelRect;
    QRect drawRect = viewport.intersected(levelRect);
    if(layer == -1)
        layer = level->height();
    if(depth == -1)
        depth = level->height();
    int xOffset = drawRect.left();
    int zOffset = drawRect.top();

    QImage image;
    if(details == 1)
        image = QImage(viewport.size() * 8, QImage::Format_ARGB32);
    else
        image = QImage(viewport.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);

    if(details == 1)
        painter.scale(8, 8);

    int yMax = qMin(level->height(), layer);
    int yMin = qMax(0, layer-depth);

    for(int x = 0; x < drawRect.width(); x++) {
        for(int z = 0; z < drawRect.height(); z++) {
            for(int y = yMax; y >= yMin; y--) {

                char blockID = level->block(x + xOffset, y, z + zOffset);
                BlockInfo *block = blockTable.value(blockID, 0);


                // No block? try next y-layer
                if(!block || block->disabled)
                    continue;

                // If the block is transparent, draw the next solid one
                if(block->transparent) {
                    for(int y2 = y-1; y2 >= yMin; y2--) {
                        char blockID2 = level->block(x + xOffset, y2, z + zOffset);
                        BlockInfo *block2 = blockTable.value(blockID2, 0);

                        if(block2 && !block2->disabled && !block2->transparent) {
                            renderBlock(painter, block2, x, y, z, details);
                            break;
                        }
                    }
                }

                renderBlock(painter, block, x, y, z, details);
                break;
            }
            float progress = (float(z) / drawRect.height() + x) / drawRect.width();
            emit progressChanged(progress);
        }
    }

    emit renderedImage(image, viewport);
}

bool MapRenderer::renderBlock(QPainter &painter, BlockInfo *block, int x, int y, int z, int details)
{
    if(!block)
        return false;

    if(details == 1)
        painter.drawImage(QRect(x, z, 1, 1), block->texture);
    else
        painter.fillRect(x, z, 1, 1, block->color);

    return true;
}
