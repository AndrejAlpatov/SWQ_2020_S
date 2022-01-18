//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Contains the CalendarDate implementation.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include "CalendarDate.h"
#include <stdexcept>
#include <QDate>
#include <cassert>

using namespace std;

Duration::Duration()
    : _days(0), _weeks(0), _months(0), _years(0)
{
}

Duration::Duration(int days, int weeks, int months, int years)
    : _days(days), _weeks(weeks), _months(months), _years(years)
{
    // negative values are not yet supported, so throw invalid_argument
    if( days < 0 || weeks < 0 || months < 0 || years < 0 )
    {
        throw( invalid_argument("Duration: negative values not yet supported") );
    }
    normalize();
}

bool Duration::operator ==(const Duration &other) const
{
    return (_days == other._days) &&
            (_weeks == other._weeks) &&
            (_months == other._months) &&
            (_years == other._years);
}

Duration Duration::operator +(const Duration &rhs) const
{
    return Duration(_days + rhs._days,
            _weeks + rhs._weeks,
            _months + rhs._months,
            _years + rhs._years);
}

void Duration::normalize() {
    const int DaysPerWeek = 7;
    _weeks += _days / DaysPerWeek;
    _days %= DaysPerWeek;

    const int MonthsPerYear = 12;
    _years += _months / MonthsPerYear;
    _months %= MonthsPerYear;
}

int Duration::asBankDays() const {
    const int HundredYearsAsBankDays = 100 * 360;

    int bankDays = _days + 7 * _weeks + 30 * _months + 360 * _years;

    if( bankDays > HundredYearsAsBankDays ) {
        throw out_of_range("Duration longer than 100 years unsupported");
    }
    return bankDays;
}

// Value is set in definition already, but storage needs to be defined here.
const int CalendarDate::unset;

CalendarDate::CalendarDate(int _day, int _month, int _year)
    : day(_day), month(_month), year(_year)
{
    if( !isValid() ) {
        throw invalid_argument("CalendarDate: invalid date spec");
    }
}

bool CalendarDate::operator ==(const CalendarDate &other) const
{
    return (day == other.day) && (month == other.month) && (year == other.year);
}

/// \todo Fehlerbehandlung fehlt noch
/// \todo Schaltjahr fehlt
/// \todo Spezifikation bei "gemischter" Duration fehlt
void CalendarDate::add(Duration d)
{
    if( year != unset ) {
        year += d.years();
    }

    if( month != unset ) {
        month += d.months();
        if( month > 12 ) {
            year += (month-1)/12;
            month = (month-1)%12 + 1;
        }
    }

    if( day != unset ) {
        day += d.days();
        if( day > maxDay(month) ) {
            day = maxDay(month);
        }
    }

    // Workaround for non-leap-years
    if( !isValid() && day == 29 && month == 2 ) {
        --day;
    }

    // The date has to be valid after adding.
    assert(isValid());
}

/// Check whether this is a valid CalendarDate object.
/// \returns true if values are unset or valid dates.
bool CalendarDate::isValid() const
{
    // We assume that 'unset' is 0 which is a valid day/month/year
    // If that is not the case, the following 'if' statement has
    // to be adapted!
    assert(unset == 0);

    if( day < 0 || day > maxDay(month) ||
        month < 0 || month > 12 ||
        year < 0 )
    {
        return false;
    }

    if( day == unset || month == unset || year == unset ) {
        return true;    // we cannot check more
    }

    // For fully specified dates, we simply use the Qt date class to verify the
    // day/month/year combination (leap year).
    return QDate(year, month, day).isValid();
}

int CalendarDate::maxDay(int month) const
{
    switch( month ) {
        case 2:
            return 29;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
    }

    // includes 'unset'!
    return 31;
}
