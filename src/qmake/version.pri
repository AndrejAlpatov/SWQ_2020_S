# qmake project includes for generating version header file
#
# NOTE: The generation depends on 'bash', so be sure on Windows to
# have it in PATH, e.g. add the cygwin direcotory to the environment
# variable 'Path'
#
# NOTE: All paths are relative to the including project files!

# we will generate a header file in $$OUT_PWD, so include it in search paths
INCLUDEPATH += $$OUT_PWD
DEPENDPATH += $$OUT_PWD

# magically create version.h with subversion number
version.target = $$OUT_PWD/generated-version.h
version.commands = @bash -c \'mkdir -p \"$$OUT_PWD\"; bash \"$$_PRO_FILE_PWD_/../../bin/create-buildtag\" \"$$version.target\"\'
version.depends = checkalways	# ensure this is always made

# the target 'always' just prints a build info
checkalways.commands = @bash -c \'echo -n \"checking version id ... \"\'

QMAKE_EXTRA_TARGETS += version checkalways
PRE_TARGETDEPS += $$version.target
QMAKE_DISTCLEAN += $$version.target
OTHER_FILES += ../../bin/create-buildtag

# qmake sometimes automatically adds (due to include file analysis) a dependency
# to generated-version.h, but the targets above have the full path included.
# If we generally strip the full path and take the filename only, qmake will change the
# dependency to .../some_source_path/generated-version.h, which is even worse.
# So, as workaround, we add another target without path, but do not add it to
# the dependencies manually.
versionlocal.target = $$basename(version.target)
versionlocal.commands = @bash -c \'ls -l \"$$versionlocal.target\"\'
versionlocal.depends = version  # this target will do the real work ...
QMAKE_EXTRA_TARGETS += versionlocal
