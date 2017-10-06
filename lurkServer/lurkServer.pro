TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += g++14
QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
SOURCES += main.cpp \
    server.cpp \
    LURKing.cpp \
    LURKer.cpp \
    lurkworld.cpp \
    lurkroom.cpp \
    jalib.cpp

HEADERS += \
    server.h \
    LURKing.h \
    LURKer.h \
    LURK.h \
    LURK.h \
    lurkworld.h \
    lurkroom.h \
    jalib.h
