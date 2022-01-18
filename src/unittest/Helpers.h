//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Test helper functions.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================
#ifndef HELPERS_H
#define HELPERS_H

#include <QString>
#include <iostream>
#include <memory>

namespace Helpers {

    /// Tests whether each character inside str is printable.
    inline
    bool isPrintable(const QString &str) {
        for(auto ch: str)
            if( ! ch.isPrint() )
                return false;

        return true;
    }
}

#include <gtest/gtest.h>
// additional googletest helpers for QString, string and nullptr_t
namespace testing {
    namespace internal {
        // Just copied from gtest.h and used for QString too:
        // If a C string is compared with an STL string object, we know it's meant
        // to point to a NUL-terminated string, and thus can print it as a string.
#define GTEST_IMPL_FORMAT_C_STRING_AS_STRING_(CharType, OtherStringType)      \
        template <>                                                           \
        class FormatForComparison<CharType*, OtherStringType> {               \
          public:                                                             \
            static ::std::string Format(CharType* value) {                    \
              return ::testing::PrintToString(value);                         \
            }                                                                 \
        }
        GTEST_IMPL_FORMAT_C_STRING_AS_STRING_(char, QString);
        GTEST_IMPL_FORMAT_C_STRING_AS_STRING_(const char, QString);
        GTEST_IMPL_FORMAT_C_STRING_AS_STRING_(wchar_t, QString);
        GTEST_IMPL_FORMAT_C_STRING_AS_STRING_(const wchar_t, QString);
#undef GTEST_IMPL_FORMAT_C_STRING_AS_STRING_


        // Helper functions for {ASSERT|EXPECT}_{EQ|NE} on nullptr_t.
        template <>
        inline
        AssertionResult CmpHelperEQ<long int, std::nullptr_t>
                                    (const char* lhs_expression,
                                    const char* rhs_expression,
                                    const long int & lhs,
                                    const std::nullptr_t & ) {
            return CmpHelperEQ(lhs_expression, rhs_expression, lhs, 0);
        }
        template <>
        inline
        AssertionResult CmpHelperNE<long int, std::nullptr_t>
                                    (const char* lhs_expression,
                                    const char* rhs_expression,
                                    const long int & lhs,
                                    const std::nullptr_t & ) {
            return CmpHelperNE(lhs_expression, rhs_expression, lhs, 0);
        }

        // Helper functions for {ASSERT|EXPECT}_{EQ|NE} on shared_ptr<> vs. nullptr_t.
        template <typename T>
        inline
        AssertionResult CmpHelperEQ(const char* lhs_expression,
                                    const char* rhs_expression,
                                    const std::shared_ptr<T> & lhs,
                                    const std::nullptr_t & rhs) {
            return CmpHelperEQ(lhs_expression, rhs_expression, lhs.get(), rhs);
        }
        template <typename T>
        inline
        AssertionResult CmpHelperNE(const char* lhs_expression,
                                    const char* rhs_expression,
                                    const std::shared_ptr<T> & lhs,
                                    const std::nullptr_t & rhs) {
            return CmpHelperNE(lhs_expression, rhs_expression, lhs.get(), rhs);
        }
    }
}

/// Comparison between QString and std::string
inline
bool operator==(const QString & q, const std::string & s) {
    return q.toStdString() == s;
}

inline
bool operator==(const std::string & s, const QString & q) {
    return q.toStdString() == s;
}

inline
bool operator!=(const QString & q, const std::string & s) {
    return q.toStdString() != s;
}

inline
bool operator!=(const std::string & s, const QString & q) {
    return q.toStdString() != s;
}

/// Comparison between QString and std::wstring
inline
bool operator==(const QString & q, const std::wstring & s) {
    return q.toStdWString() == s;
}

inline
bool operator==(const std::wstring & s, const QString & q) {
    return q.toStdWString() == s;
}

inline
bool operator!=(const QString & q, const std::wstring & s) {
    return q.toStdWString() != s;
}

inline
bool operator!=(const std::wstring & s, const QString & q) {
    return q.toStdWString() != s;
}

/// GoogleTest Print Functions
inline
void PrintTo (const QString & s, ::std::ostream * os) {
    *os << '"' << s.toStdString() << '"';
}

#include "app-lib/CalendarDate.h"
inline
void PrintTo (const CalendarDate & date, ::std::ostream * os) {
    *os << date.getDay() << "." << date.getMonth()
        << "." << date.getYear();
}

inline
void PrintTo (const Duration & duration, ::std::ostream * os) {
    *os << "Duration(" << duration.days() << "," << duration.weeks() << ","
        << duration.months() << "," << duration.years() << ")";
}
#endif // HELPERS_H
