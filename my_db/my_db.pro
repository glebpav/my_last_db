TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dbhelper.cpp \
    dataholder.cpp \
    utils.cpp \
    commandhelper.cpp

HEADERS += \
    dbhelper.h \
    dataholder.h \
    utils.h \
    commandhelper.h

