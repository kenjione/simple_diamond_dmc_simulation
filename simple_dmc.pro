#-------------------------------------------------
#
# Project created by QtCreator 2012-04-19T02:28:04
#
#-------------------------------------------------

QT       += core gui

TARGET = simple_dmc
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/lib64 -lboost_regex

SOURCES += main.cpp\
    layer.cpp \
    crystal.cpp \
    addch2reaction.cpp \
    etchingreaction.cpp \
    formdimerreaction.cpp \
    migrationbridgereaction.cpp \
    surface.cpp \
    abshreaction.cpp \
    addhreaction.cpp \
    dropdimerreaction.cpp \
    migrationhreaction.cpp \
    monoreaction.cpp \
    dualreaction.cpp \
    reaction.cpp \
    handbook.cpp \
    handbookerror.cpp \
    runner.cpp \
    saver.cpp \
    migrationbridgeinfo.cpp \
    reactionspool.cpp \
    reactionpoolsaver.cpp \
    surfacesaver.cpp \
    crystalsaver.cpp \
    timenumbercurvessaver.cpp \
    configurator.cpp \
    migrationfrontdown.cpp

HEADERS  += \
    surface.h \
    reactor.h \
    reaction.h \
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
    addhreaction.h \
    addch2reaction.h \
    abshreaction.h \
    int3.h \
    handbook.h \
    handbookerror.h \
    runner.h \
    saver.h \
    migrationbridgeinfo.h \
    reactionspool.h \
    reactionpoolsaver.h \
    surfacesaver.h \
    crystalsaver.h \
    timenumbercurvessaver.h \
    configurator.h \
    parse_error.h \
    parse_params_error.h \
    migrationfrontdown.h

FORMS    +=

OTHER_FILES += \
    Makefile \
    handbook.cnf
