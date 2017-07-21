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
    form.cpp \
    myitem.cpp editorgutter.cc \
    parser_sbase.cc \
    testitem.cc \
    mytranslator.cpp

HEADERS  += mainwindow.h \
    form.h \
    myitem.h editorgutter.h \
    typestruct.h \
    expression.h \
    ui_haupt.h \
    testitem.h \
    mytranslator.h

FORMS    += mainwindow.ui \
    haupt.ui

RESOURCES += \
    icons.qrc
