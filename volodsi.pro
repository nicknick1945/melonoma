#-------------------------------------------------
#
# Project created by QtCreator 2017-11-05T21:00:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = volodsi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    engine.cpp \
    abstractfilter.cpp \
    coords.cpp \
    blackwhitefilte.cpp \
    loggerfactory.cpp \
    logger.cpp \
    contrastfilter.cpp \
    utils.cpp \
    sobelfilter.cpp \
    gaussfilter.cpp \
    medianfilter.cpp \
    mysuperfilter.cpp \
    skiletizationfilter.cpp \
    otsybinarizer.cpp \
    countvoloscalculater.cpp \
    scenezoom.cpp \
    form.cpp \
    startform.cpp \
    cachefactory.cpp \
    cache.cpp \
    defaultwidget.cpp \
    defaultwidgetmodel.cpp

HEADERS  += mainwindow.h \
    engine.h \
    abstractfilter.h \
    coords.h \
    blackwhitefilte.h \
    utils.h \
    loggerfactory.h \
    logger.h \
    contrastfilter.h \
    sobelfilter.h \
    gaussfilter.h \
    medianfilter.h \
    mysuperfilter.h \
    skiletizationfilter.h \
    otsybinarizer.h \
    countvoloscalculater.h \
    scenezoom.h \
    form.h \
    startform.h \
    cachefactory.h \
    cache.h \
    defaultwidget.h \
    defaultwidgetmodel.h

FORMS    += mainwindow.ui \
    form.ui \
    startform.ui

DISTFILES +=
