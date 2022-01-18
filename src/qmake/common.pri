# qmake project include file with common settings

# The libs and executables shall not be "hidden" in the
# subdirectories of the build directory, therefore:
DESTDIR = ..            # target directory one level above

CONFIG += c++11         # enable features of C++11 standard

*-g++ {
    # -Wall / -Wextra are enabled by default
    QMAKE_CXXFLAGS += -Werror
    QMAKE_CXXFLAGS += -Wdeprecated
    QMAKE_CXXFLAGS += -Wextra           # not enabled on linux by default
    # disable g++ 9.2 warnings on old library sources (googletest, older Qt libs)
    QMAKE_CXXFLAGS += -Wno-deprecated-copy
}
