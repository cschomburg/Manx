# -------------------------------------------------
# Project created by QtCreator 2010-06-08T11:26:26
# -------------------------------------------------
QT += opengl \
    script
TARGET = Manx
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    nbttag/nbttag.cpp \
    nbttag/nbttagbyte.cpp \
    nbttag/nbttagshort.cpp \
    nbttag/nbttagint.cpp \
    nbttag/nbttaglong.cpp \
    nbttag/nbttagfloat.cpp \
    nbttag/nbttagdouble.cpp \
    nbttag/nbttagbytearray.cpp \
    nbttag/nbttagstring.cpp \
    nbttag/nbttaglist.cpp \
    nbttag/nbttagcompound.cpp \
    qnbttag.cpp \
    nbtreader.cpp \
    level/levelindev.cpp \
    maprenderer.cpp \
    level/levelinfdevchunk.cpp \
    mapviewer.cpp \
    mapwidget.cpp
HEADERS += mainwindow.h \
    nbttag/nbttag.h \
    nbttag/nbttagbyte.h \
    nbttag/nbttagshort.h \
    nbttag/nbttagint.h \
    nbttag/nbttaglong.h \
    nbttag/nbttagfloat.h \
    nbttag/nbttagdouble.h \
    nbttag/nbttagbytearray.h \
    nbttag/nbttagstring.h \
    nbttag/nbttaglist.h \
    nbttag/nbttagcompound.h \
    nbttag/nbttags.h \
    qnbttag.h \
    nbtreader.h \
    level/minecraftlevel.h \
    level/levelindev.h \
    blockinfo.h \
    level/levels.h \
    maprenderer.h \
    level/levelinfdevchunk.h \
    mapviewer.h \
    mapwidget.h
FORMS += mainwindow.ui
