TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    namegenerator.cpp \
    maploader.cpp \
    map.cpp \
    engine.cpp \
    ninjadata.cpp

HEADERS += \
    namegenerator.h \
    maploader.h \
    map.h \
    engine.h \
    ninjadata.h
