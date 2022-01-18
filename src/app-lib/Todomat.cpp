//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Implementation parts of class Todomat.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include "Todomat.h"

using namespace std;

Todomat::Todomat(UI & givenUi)
    : ui(givenUi)
{
}

void Todomat::run()
{
    ui.sayWelcome();

    wstring command = ui.getFilledInputLine(L"Bitte Kommando eingeben",
                                            L"Leere Eingabe, bitte wiederholen!");
    (void) command;     /// \todo react on command

    ui.sayGoodbye();
}
