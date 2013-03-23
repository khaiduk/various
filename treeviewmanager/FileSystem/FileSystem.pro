#-------------------------------------------------
#
# Project created by QtCreator 2012-08-26T11:34:51
#
#-------------------------------------------------

QT       -= core gui

TARGET = ../filesystem
TEMPLATE = lib
CONFIG += staticlib




INCLUDEPATH += .
INCLUDEPATH += C:\boost_1_50_0
LIBS += ..\blib\libboost_system-vc100-mt-1_50.lib
LIBS += ..\blib\libboost_filesystem-vc100-mt-1_50.lib

SOURCES += \
    Path.cpp \
    Globals.cpp \
    File.cpp \
    Element.cpp \
    Directory.cpp

HEADERS += \
    Path.h \
    Globals.h \
    File.h \
    Element.h \
    Directory.h
