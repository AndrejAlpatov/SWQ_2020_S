//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      The interface definition of class TodoEntry.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================
#if !defined(TODOENTRY_H)
#define TODOENTRY_H

#include "CalendarDate.h"
#include <string>

/// TodoEntry contains all elements of a TodoEntry :-).
/// This is just a struct (i.e. a class with public elements) with all
/// data needed to define a todo entry.
/// As string type, std::wstring is used (wide strings, i.e. UTF aware).
/// For wchar_t literals (wstring is basic_string<wchar_t>), use the
/// prefix 'L', e.g. 'L"hello"', see e.g.
/// http://en.cppreference.com/w/cpp/language/string_literal
struct TodoEntry {
    bool important;         ///< default: not important
    bool urgent;            ///< default: not urgent
    std::wstring delegate;  ///< a possible delegate person, default: empty
    std::wstring summary;   ///< default: empty
    std::wstring text;      ///< longer description, default: empty
    CalendarDate deadline;  ///< default: empty
    CalendarDate reminder;  ///< default: empty

    /// Default initialization: strings are empty, flags are false.
    TodoEntry()
        : important(false), urgent(false)
    {
    }
};

#endif
