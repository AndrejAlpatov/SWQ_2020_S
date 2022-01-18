# A simple TODO list management tool: todomat

Welcome to the "todomat" project. This project is used an exercise to learn
[Google Test](https://github.com/google/googletest/blob/master/README.md) and
[Google
Mock](https://github.com/google/googletest/blob/master/googlemock/README.md) as
an [xUnit]( https://en.wikipedia.org/wiki/XUnit) like [Unit
Testing](https://en.wikipedia.org/wiki/Unit_testing) framework in a `qmake`
based C++ project.

The "todomat" will provide a command line program to manage entries in a TODO
list.

--------------------------------------------------------------

## Contents

- todomat project
  - [Intention](#intention)
  - [Features](#features)
  - [For Starters](#forstarters)
  - [Links](#links)
  - [License](#license)
- [Project Structure](#projectstructure)
  - [Directories](#directories)
  - [Documentation](#documentation)
- [Build Instructions](#buildinstructions)
  - [Prerequisites](#prerequisites)
  - [Installing QT](#installingqt)
  - [Checking out the code](#checkingoutthecode)
  - [Preparations](#preparations)
  - [Building the application and the unit test program](#building)
  - [Cleaning the build directory](#cleaning)
- [Translation](#translation)

--------------------------------------------------------------

## Intention<a name=intention></a>

This little project is used as an exercise in software development and quality management (testing) using git, C++, QtCreator, and Google Test.

## Features<a name=features></a>

- portable C++ (Linux, Windows, OS X), due to
- `qmake` project based build environment
- multi directory project layout supports building libraries
- GoogleTest xUnit-like unit test environment
- GoogleMock supporting
- Open Source License (GPLv3)

## For Starters<a name=forstarters></a>
You want to enhance this base project, or you want to use it as base of your
new project. In any case, you should get a basic knowledge of the project's
structure and of the used tools.

1. Read this [README](README.md) from top to bottom.
2. Try to [build the project](#buildinstructions) by yourself.
3. Check the [code documentation](#documentation).
4. Complete your knowledge about the used tools as necessary, see e.g. the
   [links](#links).

It would be nice if you could record the time you spent for some of these
activities and to add a time estimate to the items above.

## Links<a name=links></a>
- [Project Home](
  https://atlas.ai.it.hs-worms.de/bitbucket/projects/TST/repos/17s-projects/browse?at=refs%2Fheads%2Ftodomat%2Fmaster)
- [Qt](http://www.qt.io)
- [Git](https://git-scm.com/)
- [Google Test & Google Mock](https://github.com/google/googletest)
- [Doxygen](http://www.stack.nl/~dimitri/doxygen)
- [Markdown Syntax](http://daringfireball.net/projects/markdown/syntax)
- [C++ Reference](http://en.cppreference.com/w/cpp)

## License<a name=license></a>
If not mentioned otherwise in the files, the following licenses are used:
- Soure Code: [GPLv3](LICENSE.txt)
- Documentation: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

--------------------------------------------------------------

# Project Structure<a name=projectstructure></a>
This is only a very short overview on the project structure. In case you need
more explanation, feel free to ask and to add additional hints here :-)

## Directories<a name=directories></a>

* `bin/` contains some build and code generation shell scripts
* `build/` is initially empty (except of a `.gitignore` file) and is used as
  build directory, so that the build artefacts don't upset the source
  directories
* `doc/` holds some Doxygen configuration and principal documentation files,
  while most of the Doxygen texts are comments inside the source code files
* `src/` contains the project's `qmake` configuration file
  todomat.pro` and several subdirectories with source code and
  unit tests:
* `src/app-lib/` - the largest source code part
* `src/app-main/` - a small application main routine
* `src/googletest/` - the [GoogleTest](https://github.com/google/googletest)
  framework code
* `src/qmake/` - additional `qmake` configuration files included by others
* `src/resources/` - translations and optionally other resources
* `src/unittest/` - the Unit Test source code

## Documentation<a name=documentation></a>

The documentation is consisting of two parts mainly:

1. This [README.md](README.md) overview documentation written in
   [Markdown](http://daringfireball.net/projects/markdown/syntax). It is
   simply readable as text file, but more beautiful when viewed in the
   browser.

   The version in the git repository is probably viewed via some source code
   browser as Bitbucket or Github which interprete the Markdown syntax.

   When working on the file, it may be helpful to use e.g. the *Markdown
   Viewer* plugin for Firefox or similar, so the browser itself can render the
   Markdown files.

2. Googletest documentation is also available as Markdown in
   [src/googletest/README.md](src/googletest/README.md)

3. Code documentation built by Doxygen. This is the main documentation.

   Either view it at the [Jenkins build
   server](https://ci.kom-labor.it.fh-worms.de/jenkins/job/17s-projects_all-branches/)
   (you have to find a fitting build, as we build many projects there, and our
   Jenkins is reachable via VPN only, sorry), or you install the doxygen tool
   on your machine and run `bin/run-doxygen`; then the documentation will be
   available in [build/html](build/html/index.html).

--------------------------------------------------------------

# Build Instructions<a name=buildinstructions></a>

## Prerequisites:<a name=prerequisites></a>
- QT 5.2 or later
  - download the suitable version for your environment at
    <http://www.qt.io/download-open-source/>

## Installing QT:<a name=installingqt></a>
This is only one way that worked on Ubuntu 14.04 - if in doubt, follow
the instructions on <http://www.qt.io>

- E.g. download the Qt Online Installer for Linux (32-bit or 64-bit,
  depending on your system); for me (with Qt 5.1), the file name was
  `qt-linux-opensource-1.4.0-2-x86_64-online.run`. Adapt the following to
  the current file name.

      chmod +x qt-linux-opensource-1.4.0-2-x86_64-online.run
      sudo qt-linux-opensource-1.4.0-2-x86_64-online.run
      PATH=/opt/Qt/5.3/gcc_64/bin:$PATH	# adapt to your needs,
      					# put it into $HOME/.profile or similar

## Checking out the code:<a name=checkingoutthecode></a>
You can check out the code (and binary libraries) with a command similar
to:

    git clone https://atlas.ai.it.hs-worms.de/bitbucket/scm/tst/17s-projects.git
    git branch -a
    git checkout todomat/master		# switch to the correct branch

## Preparations:<a name=preparations></a>
Generate your platform specific build environment using cmake started
from a command line prompt (bash on Linux / Mac OS X; cmd or PowerShell
or Cygwin on Windows):

    cd build
    qmake ../src/todomat.pro CONFIG+=debug	# generates Makefile

## Building the application and the unit test program:<a name=building></a>
    cd build      # only if not already there
    make          # generates all
    ./helloworld  # enjoy the famous program
    ./unit-test   #
    make clean    # optionally, remove all temporary files

## Cleaning the build directory:<a name=cleaning></a>
- initially the build directory is empty, so all files there are
  generated by the build - and if you didn't save anything there, you
  can safely remove all files by using rm
- alternatively, just remove the files built by 'make':

      cd build		# only if not already there
      make clean		# optionally, remove all temporary files
      make distclean		# as clean, but removes also libs and Makefiles

--------------------------------------------------------------

# Translation<a name=translation></a>
The application is prepared for localization (*l10n*) using Qt's
internationalization (*i18n*) mechanisms and tools.

For details, see the [Qt Linguist
Manual](http://doc.qt.io/qt-5/qtlinguist-index.html).

The basic steps are as follows:

1. The programmer marks all translatable strings in the program by calls
   to `tr()`.
2. Inside QtCreator, you may collect these marks by executing
   `Tools`->`External`->`Linguist`->`lupdate` which adds the newly
   found marks to the `src/resources/translations/*.ts` files (these
   are XML files).
3. Start the GUI tool `linguist`, preferrably with all `*.ts` files
   together: `linguist src/resources/translations/*.ts`
4. In `linguist`, provide the translations to the different languages,
   and save the files.
5. The build process will automatically transform the XML style `*.ts`
   files into binary `*.qm` files (using the tool `lrelease`) and make
   them part of the compiled in resources.
6. The newly built programm will now find the translations just via the
   `tr()` calls of the first step - depending on the selected language.
   You may test the behaviour by starting the application with different
   language settings, e.g. 
   * `LANGUAGE=fr_FR build/*/helloworld`
   * `LANGUAGE=de_DE build/*/helloworld`
   * `LANGUAGE=en_US build/*/helloworld`
7. Commit the changes (especially the `*.ts` translations) as usual. The
   `*.qm` binary files are not part of the git repository, they will be
   rebuilt as necessary.

