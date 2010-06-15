#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>

#include "maprenderer.h"
#include "mainwindow.h"
#include "level/minecraftlevel.h"
#include "blockinfo.h"

class MapWidget : public QWidget
{
Q_OBJECT
public:
    explicit MapWidget(MainWindow *parent);

    void zoom(double zoomFactor);

protected:
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);
     void wheelEvent(QWheelEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);

     QRectF viewport();
     void startRendering(bool force = false);

 private slots:
     void updatePixmap(const QImage& image, const QRect& viewport);
     void updateLevel(MinecraftLevel *level);

private:

    MapRenderer *m_renderer;
    QPixmap m_pixmap;
    QRect m_pixViewport;
    double m_scale;
    QPointF m_pos;
    QPoint m_lastDragPos;
};

#endif // MAPWIDGET_H
