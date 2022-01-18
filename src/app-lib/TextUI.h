//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      The interface definition of class TextUI.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================
#if !defined(TEXTUI_H)
#define TEXTUI_H

#include "UI.h"
#include <iostream>
#include <string>


/// TextUI provides a text (console) based user interface to Todomat.
class TextUI : public UI {
    public:
        TextUI(std::wistream & is = std::wcin, std::wostream & os = std::wcout);
        void sayWelcome();              ///< output welcome string with version number
        void sayGoodbye();              ///< output goodbye string
        void showError(std::wstring const & message);

        /// @{
        /// \name input functions
        /// Show prompt and read one line of input.

        /// read one line after showing prompt, line may be empty
        std::wstring getInputLine(std::wstring const & prompt);

        /// read non-empty line, show errorMessage and repeat if input is empty
        std::wstring getFilledInputLine(std::wstring const & prompt, std::wstring const & errorMessage);
        /// @}

    private:
        std::wistream & input;
        std::wostream & output;
};

#endif
