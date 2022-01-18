# qmake project file to build the static library app-lib

include(../qmake/common.pri)
include(../qmake/version.pri)

QT -= gui
TARGET = app-lib
TEMPLATE = lib
CONFIG += staticlib

HEADERS += app-lib.h \
    CalendarDate.h \
    VersionInfo.h \
    TodoEntry.h \
    Todomat.h \
    TextUI.h \
    UI.h

SOURCES += \
    CalendarDate.cpp \
    VersionInfo.cpp \
    Todomat.cpp \
    TextUI.cpp \
    UI.cpp

OTHER_FILES += applib.dox

