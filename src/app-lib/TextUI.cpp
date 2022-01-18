//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Contains parts of the TextUI implementation.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include "TextUI.h"
#include "VersionInfo.h"

using namespace std;

TextUI::TextUI(wistream & is, wostream & os)
    : input(is), output(os)
{
}

void TextUI::sayWelcome()
{
    output << L"Welcome to Todomat"
           << L" version " << VersionInfo::getVersion().toStdWString()
           << L" (" << VersionInfo::getBuildTag().toStdWString() << L")" << endl;
}

void TextUI::sayGoodbye()
{
    output << L"\nGoodbye, thanks for taking care!" << endl;
}

void TextUI::showError(const wstring & message)
{
    output << L"\n" << message << endl;
}

wstring TextUI::getInputLine(const wstring & prompt)
{
    output << prompt << L": " << flush;

    wstring line;
    getline(input, line);

    return line;
}

wstring TextUI::getFilledInputLine(const wstring & prompt, const wstring & errorMessage)
{
    wstring line;
    while( true ) {
        line = getInputLine(prompt);
        if( !line.empty() || input.eof() ) {
            break;
        }

        output << L"\n" << errorMessage << endl;
    }
    return line;
}
