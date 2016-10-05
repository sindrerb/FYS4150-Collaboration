TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../classes/matrix.cpp \
    ../classes/satellite.cpp

HEADERS += \
    ../classes/matrix.h \
    ../classes/satellite.h
