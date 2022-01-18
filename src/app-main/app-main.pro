# qmake project file to build the application

TARGET = todomat
TEMPLATE = app

QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += app-main.cpp
OTHER_FILES += appmain.dox

include(../qmake/resources.pri)         # translations and others

DEPENDENCY_LIBRARIES += app-lib         # used in includes.pri
include(../qmake/includes.pri)
