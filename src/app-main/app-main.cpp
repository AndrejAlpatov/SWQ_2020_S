//============================================================================
/// \file
/// \ingroup    g_main
/// \brief      Contains the application's main function.
/// \details    We use a Qt QCoreApplication here (i.e. without GUI).
///
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include "app-lib/app-lib.h"
#include <QCoreApplication>

/// Our little main() function.
/// Not much is happening here, we just create the necessary objects and start them.
/// The program logic resides in the library classes to allow testing.
int main( int argc, char ** argv )
{
    QCoreApplication app(argc, argv);

    TextUI ui;
    Todomat todomat(ui);
    todomat.run();
}
