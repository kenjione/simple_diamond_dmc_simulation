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
    button.cpp

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
    abshreaction.h

FORMS    += mainwindow.ui



