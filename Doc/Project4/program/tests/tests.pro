TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/ising2d.cpp \    
    ../src/main.cpp \

HEADERS += \
    catch.hpp \
    ../src/ising2d.h \
