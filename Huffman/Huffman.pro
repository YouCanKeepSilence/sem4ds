TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bintree.cpp \
    fileworker.cpp \
    bitreader.cpp

HEADERS += \
    bintree.h \
    fileworker.h \
    bitreader.h
