TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    ../satelliteClass/satellite.cpp

HEADERS += \
    matrix.h \
    ../satelliteClass/satellite.h
