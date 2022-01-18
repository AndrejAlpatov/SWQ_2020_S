# qmake project includes for include paths etc.
#

include(../qmake/common.pri)

# We assume that every library is in one subdirectory below src/, so we just
# include ".." into INCLUDEPATH (i.e., "src/") and can e.g. #include "app-lib/VersionInfo.h"
# In case you'd like to skip the directory in the #include directives, you could add
# INCLUDEPATH += ../$${dep}
# instead to the for loop at the end of this file.
INCLUDEPATH += ..

# The following part was inspired
# from http://stackoverflow.com/questions/2288292/qmake-project-dependencies-linked-libraries

# This function sets up the dependencies for libraries that are built with
# this project.  Specify the libraries you need to depend on in the variable
# DEPENDENCY_LIBRARIES and this will add.
for(dep, DEPENDENCY_LIBRARIES) {
    LIBS += $${DESTDIR}/$${QMAKE_PREFIX_STATICLIB}$${dep}.$${QMAKE_EXTENSION_STATICLIB}
    PRE_TARGETDEPS += $${DESTDIR}/$${QMAKE_PREFIX_STATICLIB}$${dep}.$${QMAKE_EXTENSION_STATICLIB}
}
