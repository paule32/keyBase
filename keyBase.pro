#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T22:15:13
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG   += debug c++11

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
    haupt.cpp

HEADERS  += mainwindow.h \
    myitem.h editorgutter.h \
    typestruct.h \
    expression.h \
    ui_haupt.h \
    testitem.h \
    mytranslator.h \
    ui_mainwindow.h \
    haupt.h

FORMS    += mainwindow.ui \
    haupt.ui

RESOURCES += \
    icons.qrc
