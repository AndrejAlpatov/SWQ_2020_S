//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Unit-Tests of classes CalendarDate and Duration.
/// \copyright  GNU General Public License (GPL) Version 3
///
/// \todo CalendarDate soll Modifikation unterstützen (Setter)
/// \todo CalendarDate auf wcout ausgeben (gut für Tests, aber auch sonst)
/// \todo CalendarDate wirft Exception für ungültige Werte (Konstruktor, Setter)
/// \todo Duration Konstante für 1 Tag / 1 Woche / 1 Monat / 1 Jahr
/// \todo Duration operator *() für Multiplikation, z.B. '2*Day' für 2 Tage
///
//============================================================================

#include "app-lib/CalendarDate.h"

#include "Helpers.h"
#include <gtest/gtest.h>

using namespace std;

/// Test Fixture Class for the following tests.
class TestDefaultCalendarDate : public ::testing::Test {
    protected:
        CalendarDate defaultDate;
};

/// \test
TEST_F(TestDefaultCalendarDate, isInitializedToUnsetConstantByDefault) {
    EXPECT_EQ( defaultDate.getDay(), CalendarDate::unset );
    EXPECT_EQ( defaultDate.getMonth(), CalendarDate::unset );
    EXPECT_EQ( defaultDate.getYear(), CalendarDate::unset );
}

/// \test
TEST_F(TestDefaultCalendarDate, canBeComparedEqual) {
    CalendarDate unsetDate(CalendarDate::unset, CalendarDate::unset, CalendarDate::unset);
    CalendarDate someDate(2, 11, 2016);

    EXPECT_TRUE( defaultDate==unsetDate );
    EXPECT_EQ( defaultDate, unsetDate );

    EXPECT_FALSE( defaultDate==someDate );
}

/// \test
TEST_F(TestDefaultCalendarDate, canBeComparedNotEqual) {
    CalendarDate unsetDate(CalendarDate::unset, CalendarDate::unset, CalendarDate::unset);
    CalendarDate someDate(2, 11, 2016);

    EXPECT_TRUE( defaultDate!=someDate );
    EXPECT_NE( defaultDate, someDate );

    EXPECT_FALSE( defaultDate!=unsetDate );
}


struct TestCalendarData {
    int day;
    int month;
    int year;
};

ostream & operator << (ostream & os, TestCalendarData const & data) {
    return os << "(" << data.day << "," << data.month << "," << data.year << ")";
}

class TestCalendarDateGetter : public ::testing::TestWithParam<TestCalendarData> {
    /* nothing else needed */
};

vector<TestCalendarData> calendarDates = { {24, 10, 2016} , {1, 1, 2017} };

/// \test
TEST_P(TestCalendarDateGetter, returnsGivenDateElements) {
    // Arrange
    TestCalendarData testData = GetParam();
    CalendarDate date(testData.day, testData.month, testData.year);

    // Act & Assert
    EXPECT_EQ( date.getDay(), testData.day );
    EXPECT_EQ( date.getMonth(), testData.month );
    EXPECT_EQ( date.getYear(), testData.year);
}

INSTANTIATE_TEST_CASE_P( OnSomeDayValues, TestCalendarDateGetter, ::testing::ValuesIn(calendarDates) );


/// \test
/// \todo CalendarDate::add() mit weiteren Werten
TEST(CalendarDate,addDurationOfOneDayIncrementsDayByOne) {
    CalendarDate someDate(1,1,2017);
    Duration oneDay(1,0,0,0);

    someDate.add(oneDay);
    ASSERT_EQ(someDate.getDay(), 2);
}


// Grenzwertanalyse entsprechend Praktikums-Aufgabe P6.3
// CalendarDate( int day, int month, int year )
// Parameters:              gueltige / ungueltige Werte (Klassen)
// day                      uAek1: day < 0  (erlaubt: unset==0 !)
//                          uAek2: day > 31
//                          uAek3: day == 31, wenn month in {2,4,6,9,11}
//                          uAek4: day > 28, wenn month==2 und nicht Schaltjahr
//                          uAek5: day > 29, wenn month==2 und nicht Schaltjahr
//                          gAek1: 1 <= day <= 28
//                          gAek2: day == 29, wenn Schaltjahr oder month!=2
//                          gAek3: day == 30, wenn month!=2
//                          gAek4: day == 31, wenn month in {1,3,5,7,8,10,12,unset}
//                          gAek5: day == unset (0)
//
// month                    uAek8: month < 0 (erlaubt: unset==0)
//                          uAek9: month > 12
//                          gAek6: 1 <= month <= 12
//                          gAek7: month == unset (0)
//
/// \todo untere Grenze für Jahr spezifizieren: 1900
// year                     uAek10: 0 < year < 1900
//                          uAek11: year < 0 (erlaubt: unset==0)
/// \todo obere Grenze für Jahr spezifizieren: 3000
//                          uAek12: year >= 3000
//                          gAek8: 1900 <= year < 3000


/// \test
TEST(Duration,DefaultConstructorInitializesWithZeroValues) {
    // Arrange & Act
    Duration duration;

    // Assert
    EXPECT_EQ(duration.days(), 0);
    EXPECT_EQ(duration.weeks(), 0);
    EXPECT_EQ(duration.months(), 0);
    EXPECT_EQ(duration.years(), 0);
}


/// \test
TEST(Duration,CanBeComparedEqual) {
    // Arrange
    Duration defaultDuration;
    Duration zeroDuration(0,0,0,0);

    // Act & Assert
    EXPECT_TRUE(defaultDuration == zeroDuration);
    EXPECT_EQ(defaultDuration, zeroDuration);
}

/// \test
TEST(Duration,CanBeComparedUnequal) {
    // Arrange
    Duration defaultDuration;

    // Act & Assert
    EXPECT_NE(Duration(1,0,0,0), defaultDuration);
    EXPECT_NE(Duration(0,1,0,0), defaultDuration);
    EXPECT_NE(Duration(0,0,1,0), defaultDuration);
    EXPECT_NE(Duration(0,0,0,1), defaultDuration);
}

/// \test
TEST(Duration,providesSimpleConstants) {
    EXPECT_EQ(OneDay, Duration(1,0,0,0));
    EXPECT_EQ(OneWeek, Duration(0,1,0,0));
    EXPECT_EQ(OneMonth, Duration(0,0,1,0));
    EXPECT_EQ(OneYear, Duration(0,0,0,1));
}

/// \test
TEST(Duration,normalizesDaysToWeeks) {
    EXPECT_EQ(Duration(7,0,0,0), Duration(0,1,0,0));
    EXPECT_EQ(Duration(8,0,0,0), Duration(1,1,0,0));
}

/// \test
TEST(Duration,normalizesMonthsToYears) {
    EXPECT_EQ(Duration(0,0,12,0), Duration(0,0,0,1));
    EXPECT_EQ(Duration(0,0,13,0), Duration(0,0,1,1));
}
