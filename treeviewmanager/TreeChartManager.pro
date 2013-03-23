#-------------------------------------------------
#
# Project created by QtCreator 2012-05-29T11:30:53
#
#-------------------------------------------------

QT      += core gui
QT      += xml
QT      += webkit network

TARGET = TreeChartManager
TEMPLATE = app


INCLUDEPATH += FileSystem
LIBS    += FileSystem/filesystem.lib

INCLUDEPATH += C:\boost_1_50_0
LIBS += blib\libboost_system-vc100-mt-1_50.lib
LIBS += blib\libboost_filesystem-vc100-mt-1_50.lib


SOURCES += main.cpp\
        mainwindow.cpp \
    filesystemcontroller.cpp \
    ulubioneaction.cpp \
    treeviewelement.cpp \
    treeview.cpp \
    treeviewstyle.cpp \
    dialogstyle.cpp

HEADERS  += mainwindow.h \
    filesystemcontroller.h \
    ulubioneaction.h \
    treeviewelement.h \
    treeview.h \
    treeviewstyle.h \
    dialogstyle.h \
    FileSystem/Path.h \
    FileSystem/Globals.h \
    FileSystem/FileSystem.h \
    FileSystem/File.h \
    FileSystem/Element.h

FORMS    += mainwindow.ui \
    dialogstyle.ui

RESOURCES += \
    ikony.qrc
RC_FILE = ikona.txt
