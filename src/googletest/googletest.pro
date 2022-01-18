# qmake project file to build the static library googletest (including
# gmock and gtest)

# It is assumed that this project file is part of a subdirs project,
# where the directory containing this file is named 'googletest'.

# Usually you may use this as a submodule with git, e.g.:
# git submodule add -b testen/fused https://atlas.ai.it.fh-worms.de/bitbucket/scm/tst/googletest.git src/googletest

# We expect common settings in this include file in the parent directory:
include(../qmake/common.pri)

TEMPLATE = lib
TARGET = googletest
CONFIG += staticlib
QT -= gui

HEADERS += \
    gtest/gtest.h \
    gmock/gmock.h

SOURCES += gmock-gtest-all.cc

OTHER_FILES += \
    README.md \
    LICENSE \

# Currently qmake (version 3.0) does not remove a library
# target if the destination directory is not the build directory,
# so we try to add this. Unfortunately it may be non-platform-portable
# as we need to guess the real filename.
# See target 'distclean' in build/gtest/Makefile
QMAKE_DISTCLEAN += $${DESTDIR}/$${QMAKE_PREFIX_STATICLIB}$${TARGET}.$${QMAKE_EXTENSION_STATICLIB}
