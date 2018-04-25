#-------------------------------------------------
#
# Project created by QtCreator 2017-11-05T21:00:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = volodsi
TEMPLATE = app
CONFIG += c++14
#INCLUDEPATH += C:\Users\4ssk\Downloads\volodsi\volodsi\timofey\include

#LIBS += C:\Users\4ssk\Downloads\volodsi\volodsi\timofey\bin\libopencv_core2413.dll
#LIBS += C:\Users\4ssk\Downloads\volodsi\volodsi\timofey\bin\libopencv_highgui2413.dll
#LIBS += C:\Users\4ssk\Downloads\volodsi\volodsi\timofey\bin\libopencv_imgproc2413.dll
#LIBS += C:\Users\4ssk\Downloads\volodsi\volodsi\timofey\bin\libopencv_features2d2413.dll
#LIBS += C:\Users\4ssk\Down loads\volodsi\volodsi\timofey\bin\libopencv_calib3d2413.dll

#INCLUDEPATH += /usr/local/include/opencv
#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_features2d -lopencv_calib3d -lopencv_photo

INCLUDEPATH += E:/opencv/build/install/include/
LIBS += E:/opencv/build/install/x86/mingw/bin/libopencv_core341.dll
LIBS +=E:/opencv/build/install/x86/mingw/bin/libopencv_features2d341.dll
LIBS +=E:/opencv/build/install/x86/mingw/bin/libopencv_highgui341.dll
LIBS +=E:/opencv/build/install/x86/mingw/bin/libopencv_imgcodecs341.dll
LIBS +=E:/opencv/build/install/x86/mingw/bin/libopencv_imgproc341.dll
LIBS +=E:/opencv/build/install/x86/mingw/bin/libopencv_calib3d341.dll
LIBS +=E:/opencv/build/install/x86/mingw/bin/libopencv_photo341.dll

#INCLUDEPATH += usr/local/include

#LIBS += usr/local/lib/opencv_core3.2.0
#LIBS += usr/local/lib/opencv_highgui3.2.0
#LIBS += usr/local/lib/opencv_imgcodecs3.2.0
#LIBS += usr/local/lib/opencv_imgproc3.2.0
#LIBS += usr/local/lib/opencv_features2d3.2.0
#LIBS += usr/local/lib/opencv_calib3d3.2.0
#LIBS += usr/local/lib/opencv_photo3.2.0


SOURCES += main.cpp\
    kolay_impl/engine.cpp \
    kolay_impl/abstractfilter.cpp \
    kolay_impl/coords.cpp \
    kolay_impl/blackwhitefilte.cpp \
    kolay_impl/contrastfilter.cpp \
    kolay_impl/utils.cpp \
    kolay_impl/sobelfilter.cpp \
    kolay_impl/gaussfilter.cpp \
#    kolay_impl/medianfilter.cpp \
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
    sasha/sashawindow.cpp\
    semion/widget.cpp\
    semion/content.cpp\
    semion/imageview.cpp\
    semion/SLib/Classifying/skneighborsclassifier.cpp\
    semion/SLib/Components/sfunctors.cpp\
    semion/SLib/Components/slinearalgebra.cpp\
    semion/SLib/Components/smaincomponents.cpp\
    semion/SLib/Core/sdataframe.cpp\
    semion/SLib/Core/simagedescriptor.cpp\
    semion/SLib/Core/smatrix.cpp\
    semion/SLib/Core/ssegmentationmap.cpp\
    semion/SLib/Features/sadjacencymatrix.cpp\
    semion/SLib/Features/shistogram.cpp\
    semion/SLib/Features/steacher.cpp\
    semion/SLib/Processing/sprocessing.cpp\
    semion/SLib/Processing/sconveyor.cpp\
    semion/SLib/Processing/sbilateralfilter.cpp\
    semion/SLib/Processing/sedgedetection.cpp\
    semion/SLib/Processing/sgaussfilter.cpp\
    semion/SLib/Processing/slaplaceoperator.cpp\
    semion/SLib/Processing/ssquaremask.cpp\
    semion/SLib/Processing/sthreshold.cpp\
    timofey/haralickfeatures.cpp\
    timofey/timofeywindow.cpp\
    timofey/kernel.cpp\
    timofey/timofeyzoom.cpp\
    Alex/qcustomplot.cpp \
    Alex/alexwindow.cpp
#	ilya/transformations.cpp\
#	ilya/scenezoom.cpp\
#	ilya/mainwindow.cpp\
#	ilya/dilatation.cpp\
#	ilya/algorithms.cpp




HEADERS  += kolya_headers/engine.h \
    kolya_headers/abstractfilter.h \
    kolya_headers/coords.h \
    kolya_headers/blackwhitefilte.h \
    kolya_headers/utils.h \
    kolya_headers/contrastfilter.h \
    kolya_headers/sobelfilter.h \
    kolya_headers/gaussfilter.h \
#    kolya_headers/medianfilter.h \
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
    sasha/sashawindow.h \
    semion/widget.h \
    semion/content.h \
    semion/imageview.h \
    semion/SLib/classifying.h \
    semion/SLib/components.h \
    semion/SLib/core.h \
    semion/SLib/features.h \
    semion/SLib/processing.h \
    semion/database.h \
    semion/SLib/Classifying/sabstractclassifier.h \
    semion/SLib/Classifying/skneighborsclassifier.h \
    semion/SLib/Components/sfunctors.h \
    semion/SLib/Components/slinearalgebra.h \
    semion/SLib/Components/smaincomponents.h \
    semion/SLib/Core/sdataframe.h \
    semion/SLib/Core/simagedescriptor.h \
    semion/SLib/Core/smatrix.h \
    semion/SLib/Core/ssegmentationmap.h \
    semion/SLib/Features/sabstractfeatures.h \
    semion/SLib/Features/sadjacencymatrix.h \
    semion/SLib/Features/shistogram.h \
    semion/SLib/Features/steacher.h \
    semion/SLib/Processing/sprocessing.h \
    semion/SLib/Processing/sconveyor.h \
    semion/SLib/Processing/sbilateralfilter.h \
    semion/SLib/Processing/sedgedetection.h \
    semion/SLib/Processing/sgaussfilter.h \
    semion/SLib/Processing/slaplaceoperator.h \
    semion/SLib/Processing/ssquaremask.h \
    semion/SLib/Processing/sthreshold.h \
    timofey/haralickfeatures.h \
    timofey/timofeywindow.h \
    timofey/kernel.h \
    timofey/timofeyzoom.h \
    Alex/qcustomplot.h \
    Alex/alexwindow.h
#    ilya/transformations.h\
#    ilya/scenezoom.h\
#    ilya/opencvtransform.h\
#    ilya/mygraphicsview.h\
#    ilya/mainwindow.h\
#    ilya/kernels.h\
#    ilya/dilatation.h\
#    ilya/algorithms.h \



FORMS    += mainwindow.ui \
    form.ui \
    startform.ui \
    sasha/sashawindow.ui \
    semion/widget.ui \
    timofey/timofeywindow.ui \
    Alex/alexwindow.ui
#    ilya/ilyaform.ui \

DISTFILES +=
