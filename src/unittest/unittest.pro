# this qmake project file generates the unit test application

TARGET = unit-test
TEMPLATE = app

QT += testlib
QT -= gui

CONFIG += console
CONFIG -= app_bundle    # for Mac users
CONFIG += testcase      # adds make target for 'make check'

HEADERS += \
    Helpers.h

SOURCES += \
    testmain.cpp \
    testVersionInfo.cpp \
    testCalendarDate.cpp \
    testTodoEntry.cpp \
    testTodomat.cpp \
    testTextUI.cpp \
    aufgabe.cpp

OTHER_FILES += unittest.dox

include(../qmake/resources.pri)

# allow to #include <gtest/...> and <gmock/..>
INCLUDEPATH += $$_PRO_FILE_PWD_/../googletest

DEPENDENCY_LIBRARIES += googletest \    # used in includes.pri
    app-lib
include(../qmake/includes.pri)
