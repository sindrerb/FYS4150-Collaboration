TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    satellite.cpp \
    solarsystem.cpp

HEADERS += \
    matrix.h \
    satellite.h \
    solarsystem.h

DISTFILES += \
    earth.txt \
    sun.txt
