#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T22:15:13
#
#-------------------------------------------------

QT       += core gui widgets 3dextras
CONFIG   += debug c++14

TARGET   = keyBase
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += \
    -pedantic \
    -Wno-sign-compare \
    -Wno-deprecated \
    -Wno-switch

SOURCES += main.cpp\
        mainwindow.cpp \
    myitem.cpp editorgutter.cc \
    parser_sbase.cc \
    testitem.cc \
    mytranslator.cpp \
    haupt.cpp \
    shapedetector.cpp \
    my2dworld.cpp \
    dreidworld.cpp

HEADERS  += mainwindow.h \
    myitem.h editorgutter.h \
    typestruct.h \
    expression.h \
    ui_haupt.h \
    testitem.h \
    mytranslator.h \
    ui_mainwindow.h \
    haupt.h \
    shapedetector.h \
    my2dworld.h \
    dreidworld.h

FORMS    += mainwindow.ui \
    haupt.ui

RESOURCES += \
    images.qrc

LIBS += -L/usr/local/lib -lopencv_core
LIBS += -L/usr/local/lib -lopencv_highgui
LIBS += -L/usr/local/lib -lopencv_imgproc
LIBS += -L/usr/local/lib -lopencv_imgcodecs
