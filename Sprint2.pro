TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../lib/dsstring.cpp \
    readinandparse.cpp \
    word.cpp

HEADERS += \
    ../../lib/dsstring.h \
    ../../lib/dsvector.h \
    readinandparse.h \
    word.h
