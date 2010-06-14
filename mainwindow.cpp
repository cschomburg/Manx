#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qnbttag.h"
#include "nbttag/nbttags.h"
#include "nbtreader.h"
#include "blockinfo.h"
#include "level/levels.h"
#include "maprenderer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadBlocks("files/blocks.txt", "files/terrain.png");

    m_tag = 0;
    m_qTag = 0;
    m_level = 0;

    m_renderer = new MapRenderer(this);

    connect(ui->action_Open_File, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Export_to_Image, SIGNAL(triggered()), this, SLOT(exportImage()));

    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->btnExport, SIGNAL(clicked()), this, SLOT(exportImage()));

    connect(this, SIGNAL(levelChanged(MinecraftLevel*)), this, SLOT(onLevelChanged()));
    connect(renderer(), SIGNAL(renderedImage(QImage,QRect)), this, SLOT(saveImage(QImage)));
    connect(renderer(), SIGNAL(progressChanged(float)), this, SLOT(progressUpdate(float)));
}

MainWindow::~MainWindow()
{
    delete ui;

    if(m_tag)
        delete m_tag;

    if(m_level)
        delete m_level;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool MainWindow::loadBlocks(const QString& blockFile, const QString& textureFile)
{
    foreach(BlockInfo *block, m_blocks)
        delete block;

    BlockInfoTable blocks;

    QImage textures(textureFile);

    QFile file(blockFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    while(!file.atEnd()) {
        QString line = file.readLine();
        if(line.at(0) != '#') {
            QStringList info = line.split(",");

            if(info.count() < 4)
                continue;

            char blockID = info.at(0).toInt();
            QString title = info.at(1);
            int textureID = info.at(2).toInt();

            QImage texture;
            if(textureID > 0) {
                textureID = textureID-1;
                int tX =  textureID % 16;
                int tY = floor(textureID / 16);
                texture = textures.copy(tX * 16, tY * 16, 16, 16);
            }

            bool ok;
            QColor color = QColor::fromRgba(info.value(3, "ffff0000").toUInt(&ok, 16));

            bool transparent = false;
            bool disabled = false;
            if(info.count() > 4) {
                QString additional = info.at(4);

                transparent = additional.contains("transparent");
            }

            BlockInfo *block = new BlockInfo();
            block->blockID = blockID;
            block->title = title;
            block->transparent = transparent;
            block->color = color;
            block->texture = texture;
            block->disabled = disabled;

            blocks[blockID] = block;
        }
    }

    m_blocks = blocks;
    emit blocksChanged(m_blocks);
    return true;
}

const BlockInfoTable& MainWindow::blocks() const { return m_blocks; }

MapRenderer * MainWindow::renderer() const { return m_renderer; }

NbtTag * MainWindow::rawTag() const { return m_tag; }
QNbtTag * MainWindow::tag() const { return m_qTag; }
MinecraftLevel * MainWindow::level() const { return m_level; }

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("Minecraft Level (*.mclevel *.nbt *.dat);;All Files (*)"));

    if(m_tag)
        delete m_tag;

    NbtReader reader;
    m_tag = reader.readFile(filePath);

    emit tagChanged(m_tag);

    if(!m_tag)
        return;

    if(m_qTag)
        delete m_qTag;
    m_qTag = new QNbtTag(m_tag, this);
    emit tagChanged(m_qTag);

    statusBar()->showMessage(tr("NBT file succesfully opened!"));

    if(m_level) {
        delete m_level;
        m_level = 0;
    }

    if(LevelInDev::isValid(m_qTag)) {
        m_level = new LevelInDev(m_qTag);
        statusBar()->showMessage(tr("Found InDev level file!"));
    } else if(LevelInfDevChunk::isValid(m_qTag)) {
        m_level = new LevelInfDevChunk(m_qTag);
        statusBar()->showMessage(tr("Found InfDev chunk file!"));
    }

    emit levelChanged(m_level);
}

void MainWindow::onLevelChanged()
{
    bool hasLevel = level();
    ui->menu_Map->setEnabled(hasLevel);
    ui->btnExport->setEnabled(hasLevel);
}

void MainWindow::exportImage()
{
    if(!level())
        return;

    statusBar()->showMessage(tr("Rendering started."));

    ui->btnExport->setEnabled(false);

    renderer()->setBlockInfoTable(blocks());
    renderer()->setDetails(ui->checkDetails->isChecked());
    renderer()->setLevel(level());
    renderer()->render();
}

void MainWindow::saveImage(const QImage &image)
{
    image.save("level.png");

    ui->btnExport->setEnabled(true);

    statusBar()->showMessage(tr("Rendering complete. Saved as level.png."));
}

void MainWindow::progressUpdate(float percent)
{
    ui->progressExport->setValue(qRound(percent*100));
}
