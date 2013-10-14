#-------------------------------------------------
#
# Project created by QtCreator 2013-09-26T08:28:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CataMapMaker
TEMPLATE = app

CONFIG += static

SOURCES += main.cpp\
        mapmaker.cpp \
    map.cpp \
    newmapdialog.cpp \
    maptile.cpp \
    mapoptionsdialog.cpp \
    mapoptions.cpp \
    optionsdialog.cpp

HEADERS  += mapmaker.h \
    map.h \
    newmapdialog.h \
    maptile.h \
    colors.h \
    mapoptionsdialog.h \
    mapoptions.h \
    optionsdialog.h \
    mapfeatures.h

FORMS    += mapmaker.ui \
    newmapdialog.ui \
    mapoptionsdialog.ui \
    optionsdialog.ui
