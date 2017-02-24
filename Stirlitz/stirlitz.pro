TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    translator.cpp \
    analyzer.cpp

HEADERS += \
    codeTables.h \
    translator.h \
    analyzer.h
