TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/matrix.cpp \
    ../src/numericalsolver_test.cpp \
    ../src/numericalsolver.cpp \
    ../src/satellite_test.cpp \
    ../src/satellite.cpp \
    ../src/solarsystem.cpp \
    ../src/vec3.cpp

HEADERS += \
    ../src/matrix.h \
    ../src/numericalsolver.h \
    ../src/satellite.h \
    ../src/solarsystem.h \
    ../src/vec3.h \
    ../src/catch.hpp
