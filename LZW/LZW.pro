TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    myhash.cpp \
    element.cpp \
    writer.cpp \
    table.cpp \
    reader.cpp \
    mytable.cpp

HEADERS += \
    myhash.h \
    element.h \
    writer.h \
    tools.h \
    table.h \
    reader.h \
    mytable.h
