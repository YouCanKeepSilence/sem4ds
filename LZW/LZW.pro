TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    myhash.cpp \
    element.cpp \
    writer.cpp \
    table.cpp

HEADERS += \
    myhash.h \
    element.h \
    writer.h \
    tools.h \
    table.h
