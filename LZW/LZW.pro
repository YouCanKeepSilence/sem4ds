TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    writer.cpp \
    reader.cpp \
    mytable.cpp

HEADERS += \
    writer.h \
    tools.h \
    reader.h \
    mytable.h
