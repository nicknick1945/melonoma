#-------------------------------------------------
#
# Project created by QtCreator 2017-11-01T15:24:20
#
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Melaroi
TEMPLATE = app


SOURCES +=\
    main.cpp\
    widget.cpp\
    content.cpp\
    imageview.cpp
SOURCES +=\
    SLib\Classifying\skneighborsclassifier.cpp
SOURCES +=\
    SLib\Components\sfunctors.cpp\
    SLib\Components\slinearalgebra.cpp\    
    SLib\Components\smaincomponents.cpp
SOURCES +=\
    SLib\Core\sdataframe.cpp\
    SLib\Core\simagedescriptor.cpp\
    SLib\Core\smatrix.cpp\
    SLib\Core\ssegmentationmap.cpp
SOURCES +=\
    SLib\Features\sadjacencymatrix.cpp\
    SLib\Features\shistogram.cpp\
    SLib\Features\steacher.cpp
SOURCES +=\
    SLib\Processing\sprocessing.cpp\
    SLib\Processing\sconveyor.cpp\
    SLib\Processing\sbilateralfilter.cpp\
    SLib\Processing\sedgedetection.cpp\
    SLib\Processing\sgaussfilter.cpp\
    SLib\Processing\slaplaceoperator.cpp\
    SLib\Processing\ssquaremask.cpp\
    SLib\Processing\sthreshold.cpp



HEADERS  +=\
    widget.h\
    content.h\
    imageview.h \
    SLib/classifying.h \
    SLib/components.h \
    SLib/core.h \
    SLib/features.h \
    SLib/processing.h \
    database.h
HEADERS +=\
    SLib\Classifying\sabstractclassifier.h\
    SLib\Classifying\skneighborsclassifier.h
HEADERS +=\
    SLib\Components\sfunctors.h\
    SLib\Components\slinearalgebra.h\
    SLib\Components\smaincomponents.h
HEADERS +=\
    SLib\Core\sdataframe.h\
    SLib\Core\simagedescriptor.h\
    SLib\Core\smatrix.h\
    SLib\Core\ssegmentationmap.h
HEADERS +=\
    SLib\Features\sabstractfeatures.h\
    SLib\Features\sadjacencymatrix.h\
    SLib\Features\shistogram.h\
    SLib\Features\steacher.h
HEADERS +=\
    SLib\Processing\sprocessing.h\
    SLib\Processing\sconveyor.h\
    SLib\Processing\sbilateralfilter.h\
    SLib\Processing\sedgedetection.h\
    SLib\Processing\sgaussfilter.h\
    SLib\Processing\slaplaceoperator.h\
    SLib\Processing\ssquaremask.h\
    SLib\Processing\sthreshold.h



FORMS    += widget.ui

