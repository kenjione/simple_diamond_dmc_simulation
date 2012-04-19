#-------------------------------------------------
#
# Project created by QtCreator 2012-04-19T02:28:04
#
#-------------------------------------------------

QT       += core gui

TARGET = simple_dmc
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    playbutton.cpp \
    button.cpp \
    layer.cpp \
    crystal.cpp \
    addch2reaction.cpp \
    etchingreaction.cpp \
    formdimerreaction.cpp \
    migrationbridgereaction.cpp \
    surface.cpp

HEADERS  += mainwindow.h \
    volume.h \
    surface.h \
    renderarea.h \
    reactor.h \
    reaction.h \
    playbutton.h \
    monoreaction.h \
    migrationhreaction.h \
    migrationbridgereaction.h \
    layer.h \
    formdimerreaction.h \
    etchingreaction.h \
    dualreaction.h \
    dropdimerreaction.h \
    crystal.h \
    carbon.h \
    button.h \
    addhreaction.h \
    addch2reaction.h \
    abshreaction.h \
    int3.h

FORMS    += mainwindow.ui



