TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    bintree.cpp \
    bitreader.cpp \
    binarywriter.cpp

HEADERS += \
    bintree.h \
    bitreader.h \
    binarywriter.h
