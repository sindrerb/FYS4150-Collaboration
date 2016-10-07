TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    vec3.cpp \
    satellite.cpp \
    solarsystem.cpp

HEADERS += \
    matrix.h \
    vec3.h \
    satellite.h \
    solarsystem.h

DISTFILES += \
    earth.txt \
    sun.txt
