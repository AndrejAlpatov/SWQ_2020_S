//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Unit-Tests of class TodoEntry.
/// \copyright  GNU General Public License (GPL) Version 3
///
/// \todo   TodoEntry Modifikation testen
/// \todo   TodoEntry Ausgabeoperator <<
///
//============================================================================

#include "app-lib/TodoEntry.h"

#include "Helpers.h"
#include <gtest/gtest.h>

using namespace std;

/// \test
TEST(TodoEntry,isEmptyByDefault) {
    // Arrange
    TodoEntry todo;
    wstring emptyString(L"");   // note the 'L' prefix for wchar_t string literals

    // Act
    CalendarDate emptyDate;

    // Assert
    EXPECT_FALSE(todo.important);
    EXPECT_FALSE(todo.urgent);
    EXPECT_TRUE(todo.delegate.empty());
    EXPECT_EQ(todo.delegate, emptyString);  // gives more info than checking wstring::empty()
    EXPECT_EQ(todo.summary, emptyString);
    EXPECT_EQ(todo.text, emptyString);
    EXPECT_EQ(todo.deadline, emptyDate);
    EXPECT_EQ(todo.reminder, emptyDate);
}

