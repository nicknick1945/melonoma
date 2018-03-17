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
    kolay_impl/engine.cpp \
    kolay_impl/abstractfilter.cpp \
    kolay_impl/coords.cpp \
    kolay_impl/blackwhitefilte.cpp \
    kolay_impl/contrastfilter.cpp \
    kolay_impl/utils.cpp \
    kolay_impl/sobelfilter.cpp \
    kolay_impl/gaussfilter.cpp \
    kolay_impl/medianfilter.cpp \
    kolay_impl/mysuperfilter.cpp \
    kolay_impl/skiletizationfilter.cpp \
    kolay_impl/otsybinarizer.cpp \
    kolay_impl/countvoloscalculater.cpp \
    kolay_impl/scenezoom.cpp \
    kolay_impl/form.cpp \
    kolay_impl/startform.cpp \
    platform_impl/cachefactory.cpp \
    platform_impl/cache.cpp \
    platform_impl/defaultwidget.cpp \
    platform_impl/defaultwidgetmodel.cpp\
    platform_impl/loggerfactory.cpp \
    platform_impl/logger.cpp \
    platform_impl/mainwindow.cpp \
    sasha/imagematrix.cpp \
    sasha/processing.cpp \
    sasha/viewer.cpp \
    sasha/features.cpp \
    sasha/sashawindow.cpp


HEADERS  += kolya_headers/engine.h \
    kolya_headers/abstractfilter.h \
    kolya_headers/coords.h \
    kolya_headers/blackwhitefilte.h \
    kolya_headers/utils.h \
    kolya_headers/contrastfilter.h \
    kolya_headers/sobelfilter.h \
    kolya_headers/gaussfilter.h \
    kolya_headers/medianfilter.h \
    kolya_headers/mysuperfilter.h \
    kolya_headers/skiletizationfilter.h \
    kolya_headers/otsybinarizer.h \
    kolya_headers/countvoloscalculater.h \
    kolya_headers/scenezoom.h \
    kolya_headers/form.h \
    kolya_headers/startform.h \
    platform_headers/mainwindow.h \
    platform_headers/defaultwidgetmodel.h \
    platform_headers/loggerfactory.h \
    platform_headers/logger.h \
    platform_headers/cachefactory.h \
    platform_headers/cache.h \
    platform_headers/defaultwidget.h \
    sasha/imagematrix.h \
    sasha/processing.h \
    sasha/viewer.h \
    sasha/features.h \
    sasha/sashawindow.h

FORMS    += mainwindow.ui \
    form.ui \
    startform.ui \
    sasha/sashawindow.ui \

DISTFILES +=
