TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    satellite.cpp \
    solarsystem.cpp \
    vec3.cpp

HEADERS += \
    matrix.h \
    satellite.h \
    solarsystem.h \
    vec3.h

DISTFILES += \
    earth.txt \
    sun.txt
