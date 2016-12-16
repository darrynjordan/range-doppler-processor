#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T12:01:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-port
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv

LIBS += -L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc
LIBS += -lfftw3


SOURCES += main.cpp\
        mainwindow.cpp \
    timer.cpp \
    processor.cpp \
    logger.cpp \
    taper.cpp \
    plot.cpp \
    colour.cpp \
    convertUTF.c

HEADERS  += mainwindow.h \
    timer.h \
    processor.h \
    plot.h \
    taper.h \
    logger.h \
    colour.h \
    convertUTF.h \
    simpleIni.h

FORMS    += mainwindow.ui
