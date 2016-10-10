TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    vec3.cpp \
    satellite.cpp \
    solarsystem.cpp \
    numericalsolver.cpp \


HEADERS += \
    matrix.h \
    vec3.h \
    satellite.h \
    solarsystem.h \
    numericalsolver.h \
    catch.hpp

DISTFILES += \
    earth.txt \
    sun.txt \
    solarsystem.txt
