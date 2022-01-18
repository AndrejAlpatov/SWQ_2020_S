//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Unit- and Integration-Tests of class TodoMat.
/// \details    The tests here are not "pure" unit tests, i.e. some (simple)
///             classes like TodoEntry are just used and not replaced by
///             test mocks (stubs or similar), but other more complex classes
///             like User Interface may be simulated. So it's not too far from
///             unit tests ...
/// \copyright  GNU General Public License (GPL) Version 3
///
/// DONE Todomat kann mit UI initialisiert werden
/// DONE Todomat::run ruft UI::getFilledInputLine() auf bis EOF kommt
/// \todo Todomat::run gibt bei Hilfekommando Hilfe (Usage) aus
/// \todo Todomat::run ruft bei Ende Storage::save() auf
/// \todo Todomat kann auch mit Storage initialisiert werden
/// \todo Todomat::run ruft bei Start Storage::load() auf
///
//============================================================================

#include "app-lib/Todomat.h"
#include "app-lib/Todomat.h"		// check include protection
#include "app-lib/TextUI.h"

#include "Helpers.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

/// A UI test spy class.
class SpyUI : public UI
{
    public:
        SpyUI(wstring const & input = L"")
            : welcomeCalls(0), goodbyeCalls(0), is(input) {
        }

        void sayWelcome() { ++welcomeCalls; callSequence += "w"; }
        void sayGoodbye() { ++goodbyeCalls; callSequence += "g"; }
        void showError(wstring const & /*message*/) { callSequence += "e"; }

        wstring getInputLine(wstring const & /*prompt*/) {
            callSequence += "g";
            return nextLine();
        }

        wstring getFilledInputLine(wstring const & /*prompt*/, wstring const & /*errorMessage*/)  {
            callSequence += "f";
            return nextLine();      // cannot call getInputLine() here - would change callSequence!
        }

        /// @{
        /// \name The Spy Counters
        size_t welcomeCalls;
        size_t goodbyeCalls;
        string callSequence;
        /// @}

    private:
        wistringstream is;
        /// Helper function, get next line from simulated input stream.
        wstring nextLine() {
            wstring line;
            getline(is, line);
            return line;
        }
};


/// \test
TEST(Todomat, isSilentWithoutRunUsingSpy) {
    // Setup
    SpyUI spyUI;

    // Execute
    Todomat todomat(spyUI);
    (void) todomat;

    // Verify
    EXPECT_EQ(spyUI.welcomeCalls, 0U);
    EXPECT_EQ(spyUI.goodbyeCalls, 0U);
    EXPECT_EQ(spyUI.callSequence, "");
}


/// \test
TEST(Todomat, isSilentWithoutRun) {
    // Setup
    wistringstream emptyInput;
    wostringstream output;
    TextUI ui(emptyInput, output);

    // Execute
    Todomat todomat(ui);
    (void) todomat;

    // Verify
    EXPECT_EQ(output.str(), L"");
}


/// \test
TEST(Todomat, callsSayWelcomeAndSayGoodbyeOnceForEmptyInput) {
    // Setup
    SpyUI spyUI;
    Todomat todomat(spyUI);

    // Execute
    todomat.run();

    // Verify
    EXPECT_EQ(spyUI.welcomeCalls, 1U);
    EXPECT_EQ(spyUI.goodbyeCalls, 1U);
    EXPECT_EQ(spyUI.callSequence, "wfg");
}


/// \test
TEST(Todomat, startsOutputWithWelcomeOnStartup) {
    // Setup
    const wstring hello(L"Welcome to Todomat");
    wostringstream output;
    wistringstream emptyInput;
    TextUI ui(emptyInput, output);
    Todomat todomat(ui);

    // Execute
    todomat.run();

    // Verify
    wstring startOfOutput = output.str();
    startOfOutput = startOfOutput.substr(0, hello.size());
    EXPECT_EQ(startOfOutput, hello);
}


/// \test
TEST(Todomat, saysGoodbyeAtEmptyInput) {
    // Setup
    wistringstream emptyInputStream;
    wostringstream outputStream;
    TextUI ui(emptyInputStream, outputStream);
    Todomat todomat(ui);

    // Execute
    todomat.run();

    // Verify
    wstring goodbye(L"\nGoodbye, thanks for taking care!\n");
    wstring output = outputStream.str();
    EXPECT_NE(output.find(goodbye), wstring::npos)
            << "Verabschiedung <" << goodbye << "> fehlt "
               "in Ausgabe <" << output << ">";

    // Teardown
}


/// \test
TEST(Todomat, outputsPromptAtEmptyInput) {
    // Setup
    wistringstream emptyInputStream;
    wostringstream outputStream;
    const wstring prompt(L"Kommando eingeben: ");
    TextUI ui(emptyInputStream, outputStream);
    Todomat todomat(ui);

    // Execute
    todomat.run();

    // Verify
    wstring output = outputStream.str();
    wstring promptErrorMessage;
    promptErrorMessage += L"for output <" + output + L"> and prompt <" + prompt + L">";
    EXPECT_NE(output.find(prompt), wstring::npos) << promptErrorMessage;
    EXPECT_EQ(output.find(prompt), output.rfind(prompt)) << promptErrorMessage;
}


/// Currently Todomat stops Todomat::run() if the call of
/// UI::getFilledInputLine() returns an empty line.
/// \todo This doesn't look "natural"; an explicit condition would be better.
TEST(Todomat,stopsReadingIfReadFilledInputLineReturnsEmptyLine) {
    // Setup
    SpyUI spyUI(L"\nsome Text\n\n\n\n\n");
    Todomat todomat(spyUI);

    // Execute
    todomat.run();

    // Verify
    EXPECT_EQ(spyUI.callSequence, "wfg");
}


/// \test
TEST(Todomat, outputsPromptTwoTimesForOneBlankLineOfInput) {
    // Setup
    wistringstream oneBlankLineOfInput(L"\n");
    wostringstream outputStream;
    const wstring doubleprompt(L"Bitte Kommando eingeben: \n"
                               L"Leere Eingabe, bitte wiederholen!\n"
                               L"Bitte Kommando eingeben: "
                               );
    TextUI ui(oneBlankLineOfInput, outputStream);
    Todomat todomat(ui);

    // Execute
    todomat.run();

    // Verify
    wstring output = outputStream.str();
    wstring errorMessage;
    errorMessage += L"for output <" + output + L"> and prompt <" + doubleprompt + L">";
    EXPECT_NE(output.find(doubleprompt), wstring::npos) << errorMessage;
    EXPECT_EQ(output.find(doubleprompt), output.rfind(doubleprompt)) << errorMessage;
}


/// \test
TEST(Todomat, callsSayWelcomeAndSayGoodbyeOnceForEmtpyInput) {
    // Setup
    SpyUI spyUI;
    Todomat todomat(spyUI);
    // preconditions
    ASSERT_EQ(spyUI.welcomeCalls, 0U);
    ASSERT_EQ(spyUI.goodbyeCalls, 0U);

    // Execute
    todomat.run();

    // Verify
    EXPECT_EQ(spyUI.welcomeCalls, 1U);
    EXPECT_EQ(spyUI.goodbyeCalls, 1U);
    EXPECT_EQ(spyUI.callSequence, "wfg");
}
