TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    numericalsolver_test.cpp \
    satellite_test.cpp \
    ../src/numericalsolver.cpp \    
    ../src/satellite.cpp \
    ../src/solarsystem.cpp \
    ../src/vec3.cpp \
    solarsystem_test.cpp

HEADERS += \
    catch.hpp \
    ../src/numericalsolver.h \
    ../src/satellite.h \
    ../src/solarsystem.h \
    ../src/vec3.h
