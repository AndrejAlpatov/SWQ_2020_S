//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Unit- and Integration-Tests of class TextUI.
/// \details    The tests here are not "pure" unit tests, i.e. some (simple)
///             classes like TodoEntry are just used and not replaced by
///             test mocks (stubs or similar), but other more complex classes
///             like User Interface may be simulated. So it's not too far from
///             unit tests ...
/// \copyright  GNU General Public License (GPL) Version 3
///
/// DONE TextUI can be created with istream and ostream references
/// DONE TextUI::sayWelcome() kann Willkommen-Nachricht mit Versionsinformation ausgeben
/// DONE TextUI::sayGoodbye() kann Abschieds-Nachricht ausgeben
/// DONE TextUI::showError(wstring&) kann Fehlermeldung ausgeben
/// DONE TextUI::getInputLine(wstring & prompt) liefert Nutzer-Eingabe nach Prompt
/// \todo TextUI::getFilledInputLine(wstring & prompt) liefert nicht-leere Nutzer-Eingabe nach Prompt
//============================================================================

#include "app-lib/TextUI.h"
#include "app-lib/TextUI.h"

#include "Helpers.h"
#include <gtest/gtest.h>

#include <sstream>
using namespace std;


/// \test
TEST(TextUI, canBeInstantiatedWithInputOutputStreams) {
    // Setup
    wistringstream someInputStream;
    wostringstream someOutputStream;

    // Execute
    TextUI ui(someInputStream, someOutputStream);
    (void) ui;

    // Verify

    // Teardown
}


/// \test
TEST(TextUI, canSayWelcome) {
    // Setup
    const wstring hello(L"Welcome to Todomat");
    wistringstream emptyInput;
    wostringstream output;
    TextUI textui(emptyInput, output);

    // Execute
    textui.sayWelcome();

    // Verify
    wstring startOfOutput = output.str();
    startOfOutput = startOfOutput.substr(0, hello.size());
    EXPECT_EQ(startOfOutput, hello);
}


/// \test
TEST(TextUI, canSayGoodbye) {
    // Setup
    wistringstream emptyInputStream;
    wostringstream outputStream;
    const wstring goodbye(L"\nGoodbye, thanks for taking care!\n");
    TextUI textui(emptyInputStream, outputStream);

    // Execute
    textui.sayGoodbye();

    // Verify
    EXPECT_EQ(outputStream.str(), goodbye);
}


/// \test
TEST(TextUI, canPrintErrorMessage) {
    // Setup
    const wstring someErrorMessage(L"Oh oh!");
    const wstring expectedOutput = wstring(L"\n") + someErrorMessage + L"\n";

    wistringstream emptyInputStream;
    wostringstream outputStream;
    TextUI textui(emptyInputStream, outputStream);

    // Execute
    textui.showError(someErrorMessage);

    // Verify
    EXPECT_EQ(outputStream.str(), expectedOutput);
}


/// \test
TEST(TextUI, getInputLineShowsPromptOnEmptyInput) {
    // Setup
    const wstring somePrompt(L"Give me some data please");
    const wstring expectedOutput = somePrompt + L": ";

    wistringstream emptyInputStream;
    wostringstream outputStream;
    TextUI textui(emptyInputStream, outputStream);

    // Execute
    wstring line = textui.getInputLine(somePrompt);

    // Verify
    EXPECT_EQ(outputStream.str(), expectedOutput);
    EXPECT_TRUE(line.empty()) << L"line input is <" << line << L">";
}


/// \test
TEST(TextUI, getInputLineDeliversOneLineOfInput) {
    // Setup
    const wstring somePrompt(L"Any Prompt :-) ");
    const wstring expectedOutput = somePrompt + L": ";
    const wstring firstLineOfInput(L"First Line");
    const wstring twoLinesOfInput = firstLineOfInput + L"\nSecond Line";

    wistringstream inputStream(twoLinesOfInput);
    wostringstream outputStream;
    TextUI textui(inputStream, outputStream);

    // Execute
    wstring line = textui.getInputLine(somePrompt);

    // Verify
    EXPECT_EQ(outputStream.str(), expectedOutput);
    EXPECT_EQ(line, firstLineOfInput);
}


/// \test
TEST(TextUI, getFilledInputLineShowsErrorMessageOnBlankLine) {
    // Setup
    const wstring somePrompt(L"Any Prompt :-) ");
    const wstring someErrorMessage(L"I want MORE date!");
    const wstring expectedOutput = somePrompt + L": \n"
                                   + someErrorMessage + L"\n"
                                   + somePrompt + L": ";

    wistringstream oneBlankLineOfInput(L"\n");
    wostringstream outputStream;
    TextUI textui(oneBlankLineOfInput, outputStream);

    // Execute
    wstring line = textui.getFilledInputLine(somePrompt, someErrorMessage);

    // Verify
    EXPECT_EQ(outputStream.str(), expectedOutput);
    EXPECT_EQ(line, L"");
}
