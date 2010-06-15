#include <QtGui>

#include "mapwidget.h"

MapWidget::MapWidget(MainWindow *parent) :
    QWidget(parent)
{
    m_scale = 1;

    m_renderer = new MapRenderer(this);

    connect(m_renderer, SIGNAL(renderedImage(QImage,QRect)), this, SLOT(updatePixmap(QImage,QRect)));
    connect(parent, SIGNAL(blocksChanged(BlockInfoTable)), m_renderer, SLOT(setBlockInfoTable(BlockInfoTable)));
    connect(parent, SIGNAL(levelChanged(MinecraftLevel*)), m_renderer, SLOT(setLevel(MinecraftLevel*)));

    connect(parent, SIGNAL(levelChanged(MinecraftLevel*)), this, SLOT(updateLevel(MinecraftLevel*)));
}

void MapWidget::zoom(double zoomFactor)
{
    m_scale = m_scale * zoomFactor;
    qDebug("%.2f", m_scale);
    update();
    startRendering();
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    if(m_pixmap.isNull())
        return;

    painter.scale(m_scale, m_scale);
    painter.translate(m_pos);

    painter.fillRect(-5, -5, 10, 10, Qt::red);

    QRectF exposed = QRectF(m_pixViewport).intersected(viewport());
    painter.drawPixmap(exposed, m_pixmap, exposed);
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    startRendering();
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = -event->delta() / 8;
    double numSteps = numDegrees / 15.0f;
    zoom(pow(0.8, numSteps));
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_lastDragPos = event->pos();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        m_pos += (event->pos() - m_lastDragPos) / m_scale;
        m_lastDragPos = event->pos();
        update();
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pos += event->pos() - m_lastDragPos;
        m_lastDragPos = QPoint();

        update();
        startRendering();
    }
}

QRectF MapWidget::viewport()
{
    QSizeF size = this->size() / m_scale;

    QRectF viewport;
    viewport.setSize(size);
    viewport.translate(-m_pos);

    return viewport;
}

void MapWidget::updatePixmap(const QImage &image, const QRect &viewport)
{
//    if (!lastDragPos.isNull())
//        return;
    m_pixmap = QPixmap::fromImage(image);
    m_pixViewport = viewport;
    update();
}

void MapWidget::updateLevel(MinecraftLevel *level)
{
    m_renderer->setLevel(level);

    m_scale = 1;
    m_pos = QPointF(0, 0);

    m_pixmap = QPixmap();
    m_pixViewport = QRect();

    update();
    startRendering(true);
}

void MapWidget::startRendering(bool force)
{
    QRect viewport = this->viewport().toRect();

    if(!force && m_pixViewport.contains(viewport))
        return;

    m_renderer->render(viewport);
}
