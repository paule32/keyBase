#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T22:15:13
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG   += debug

TARGET   = keyBase
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += \
    -std=c++14 \
    -pedantic \
    -Wno-sign-compare \
    -Wno-deprecated \
    -Wno-switch

SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    myitem.cpp editorgutter.cc \
    parser_sbase.cc

HEADERS  += mainwindow.h \
    form.h \
    myitem.h editorgutter.h

FORMS    += mainwindow.ui \
    form.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    sym
