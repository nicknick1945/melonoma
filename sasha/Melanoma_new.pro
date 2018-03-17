#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T12:56:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Melanoma_new
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagematrix.cpp \
    processing.cpp \
    viewer.cpp \
    features.cpp

HEADERS  += mainwindow.h \
    imagematrix.h \
    processing.h \
    viewer.h \
    features.h

FORMS    += mainwindow.ui
