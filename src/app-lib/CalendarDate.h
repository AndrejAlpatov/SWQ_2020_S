//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      The interface definition of Calendar Date classes.
/// \details    This file contains the CalendarDate and Duration class interfaces.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================
#if !defined(CALENDARDATE_H)
#define CALENDARDATE_H


/// A duration, defined as simple constant object:
/// It cannot be changed after creation.
///
/// Duration is used e.g. for CalendarDate.add(). It contains
/// publicly accessible methods to get the values of days, weeks, months
/// and years.
///
/// Only the number of days and the number of months is normalized during
/// creation:
/// - every multiple of 7 days adds one week
/// - every multiple of 12 months adds one year
///
/// Example:
/// Duration{8,1,27,2} is automatically converted to Duration{1,2,3,4}:
/// 8 days => 1 week + 1 day
/// 27 months => 2 years + 3 months
///
/// That means that the values are converted into the following ranges
/// during creation:
/// days(): 0-6 (Values >= 7 increase the number of weeks accordingly)
/// months(): 0-11 (Values >= 12 increase the number of years accordingly)
///
class Duration {
    public:
        /// Default initialization is with zero values.
        Duration();

        /// Days and Months are normalized, see comments above.
        /// NOTE: Negative numbers are not yet supported and lead to an
        /// exception of type std::invalid_argument.
        Duration( int days, int weeks, int months, int years );

        /// \name Getters
        ///@{
        int days() const;
        int weeks() const;
        int months() const;
        int years() const;
        ///@}

        /// Return the number of "bank days" of this Duration object.
        /// We assume that the bank does a simplified computation
        /// of Duration days for the calculation of interest ("Zinsen"):
        /// - a week has 7 days (as usual)
        /// - a month has exactly 30 days (which is not accurate)
        /// - a year has exactly 360 days (which is not accurate)
        /// For security reasons, a Duration longer than 100 years may not
        /// be allowed for calculation of interest, so an exception of type
        /// std::out_of_range shall be omitted then.
        int asBankDays() const;

        /// \name Comparison operators
        /// Two Duration objects are equal, if the days, weeks, months and years
        /// attributes are equal.
        ///@{
        bool operator ==(const Duration & other) const;
        bool operator !=(const Duration & other) const;
        ///@}

        /// \name Arithmetic operators
        /// Two Duration objects can be added.
        ///@{
        Duration operator +(const Duration & rhs) const;
        ///@}

    private:
        int _days;
        int _weeks;
        int _months;
        int _years;

        void normalize();   /// normalize days and months according to comments above
};

/// Some simple constants
const Duration OneDay (1, 0, 0, 0);
const Duration OneWeek (0, 1, 0, 0);
const Duration OneMonth (0, 0, 1, 0);
const Duration OneYear (0, 0, 0, 1);

/// A simple calendar date consisting of day, month and year.
/// The CalendarDate takes care that the defined date is correct.
/// The definition of invalid dates will be rejected by throwing
/// an appropriate exception.
class CalendarDate {
    public:
        static const int unset = 0;    ///< used as default value

        /// Construct CalendarDate from given values.
        /// If no value is given, use CalendarDate::unset as default.
        /// For invalid dates, an exception of type std::invalid_argument is
        /// thrown (but the value 'unset' is allowed).
        CalendarDate( int day = unset, int month = unset, int year = unset);

        /// \name Getters
        ///@{
        int getDay() const;
        int getMonth() const;
        int getYear() const;
        ///@}

        void add(Duration d);   ///< add Duration to current date

        /// \name Comparison operators
        /// Two CalendarDate objects are equal, if the day, month and year
        /// attributes are equal.
        ///@{
        bool operator ==(const CalendarDate & other) const;
        bool operator !=(const CalendarDate & other) const;
        ///@}

    private:
        bool isValid() const;
        int maxDay(int month) const;

    private:
        int day;            ///< Valid day according to month (i.e., 1..28/29/30/31)
        int month;          ///< Valid month, i.e. 1..12
        int year;           ///< Valid year, but only Gregorian Calendar supported.
};


/// \name Implementation of inline member functions
///@{
inline
int Duration::days() const
{
    return _days;
}

inline
int Duration::weeks() const
{
    return _weeks;
}

inline
int Duration::months() const
{
    return _months;
}

inline
int Duration::years() const
{
    return _years;
}

inline
bool Duration::operator !=(Duration const & other) const
{
    return !(*this == other);
}
///@}


/// \name Implementation of inline member functions
///@{
inline
int CalendarDate::getDay() const
{
    return day;
}

inline
int CalendarDate::getMonth() const
{
    return month;
}

inline
int CalendarDate::getYear() const
{
    return year;
}

inline
bool CalendarDate::operator !=(CalendarDate const & other) const
{
    return !(*this == other);
}
///@}

#endif
