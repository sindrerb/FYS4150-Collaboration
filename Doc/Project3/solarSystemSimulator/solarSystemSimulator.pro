TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    satellite.cpp \
    ../satelliteClass/satellite.cpp

HEADERS += \
    matrix.h \
    satellite.h \
    ../satelliteClass/satellite.h
