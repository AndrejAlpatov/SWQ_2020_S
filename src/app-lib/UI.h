//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Defines the abstract interface of a User Interface (UI).
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================
#if !defined(UI_H)
#define UI_H

#include <string>

/// UI defines the user interface to Todomat (abstract class).
class UI {
    public:
        virtual void sayWelcome() = 0;      ///< output welcome string with version number
        virtual void sayGoodbye() = 0;      ///< output goodbye string
        virtual void showError(std::wstring const & message) = 0;

        /// @{
        /// \name input functions
        /// Show prompt and read one line of input.

        /// read one line after showing prompt, line may be empty
        virtual std::wstring getInputLine(std::wstring const & prompt) = 0;

        /// read non-empty line, show errorMessage and repeat if input is empty
        virtual std::wstring getFilledInputLine(std::wstring const & prompt, std::wstring const & errorMessage) = 0;
        /// @}

        virtual ~UI();
};

#endif
