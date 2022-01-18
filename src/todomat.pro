# a simple todo list management project

TEMPLATE = subdirs
SUBDIRS = app-main \
	  app-lib \
          unittest \
	  googletest

app-main.depends = app-lib
unittest.depends = app-lib googletest

OTHER_FILES = ../README.md \
    ../LICENSE.txt \
    ../doc/doxygen/Doxyfile \
    ../doc/doxygen/mainpage.dox \
    ../doc/doxygen/license.dox \

# lupdate does not search subdir project files for translations correctly,
# so we need to include the files here too: If we don't do it, it will say
# "lupdate warning: no TS files specified" :-(
# To avoid redundance, the file list is maintained in translations.pri
# only. If you want to add a new language, do it there.
include(qmake/translations.pri)
for( tsfile, TRANSLATIONLIST ) {
    TRANSLATIONS += resources/translations/$$tsfile
}
