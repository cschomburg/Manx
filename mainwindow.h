#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "blockinfo.h"

class NbtTag;
class QNbtTag;
class MinecraftLevel;
class MapRenderer;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool loadBlocks(const QString& blockFile, const QString& textureFile);
    const BlockInfoTable& blocks() const;

    MapRenderer * renderer() const;

    NbtTag * rawTag() const;
    QNbtTag * tag() const;
    MinecraftLevel *level() const;

signals:
    void blocksChanged(const BlockInfoTable& blocks);
    void tagChanged(NbtTag *tag) const;
    void tagChanged(QNbtTag *tag) const;
    void levelChanged(MinecraftLevel *level) const;

public slots:
    void openFile();
    void onLevelChanged();
    void exportImage();

private slots:
    void saveImage(const QImage& image);
    void progressUpdate(float percent);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    BlockInfoTable m_blocks;

    MapRenderer *m_renderer;

    NbtTag *m_tag;
    QNbtTag *m_qTag;
    MinecraftLevel *m_level;
};

#endif // MAINWINDOW_H
