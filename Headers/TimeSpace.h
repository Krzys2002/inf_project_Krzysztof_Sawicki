//
// Created by Krzysztof Sawicki on 14/05/2024.
//

#ifndef INF_PROJECT_TIMESPACE_H
#define INF_PROJECT_TIMESPACE_H


#include <iostream>

namespace TimeSpace
{
    enum class Days
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    enum class Months
    {
        January,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    enum class Seasons
    {
        Spring,
        Summer,
        Autumn,
        Winter
    };


    std::string to_string(Days day);
    std::string to_string(Seasons season);
    std::string to_string(Months month);

    std::ostream& operator<<(std::ostream& os, Days day);
    std::ostream& operator<<(std::ostream& os, Seasons season);
    std::ostream& operator<<(std::ostream& os, Months month);

    class GameTime
    {
    protected:
        static int daysInMonth;

        int dayOfMonth;
        Months month;
        int year;
        Days dayOfWeek;

    public:
        // set the number of days in the month
        static void SetDaysInMonth(int daysInMonth);
        // get the number of days in the month
        static int GetDaysInMonth();
        // get difference between two dates in years (absolute value)
        static int yearDifference(const GameTime& time1, const GameTime& time2);
        // get difference between two dates in months (absolute value)
        static int monthDifference(const GameTime& time1, const GameTime& time2);
        // get difference between two dates in days (absolute value)
        static int dayDifference(const GameTime& time1, const GameTime& time2);

        bool operator==(const GameTime& other) const;
        bool operator!=(const GameTime& other) const;
        // later date
        bool operator>(const GameTime& other) const;
        // earlier date
        bool operator<(const GameTime& other) const;

        GameTime(int dayOfMonth, Months month, int year, Days dayOfWeek);
        ~GameTime();

        void NextDay();

        int getDayOfMonth() const;
        Months getMonth() const;
        int getYear() const;
        Days getDayOfWeek() const;
        Seasons getSeason() const;
        int getDayOfYear() const;
    };

    class GameTimeSystem
    {
        int dayFromStart;
        GameTime* currentTime;
        GameTime* startTime;

    public:
        GameTimeSystem(GameTime startTime);
        ~GameTimeSystem();

        // set time on the next day
        void NextDay();

        int getDayFromStart();

        GameTime* getCurrentTime();
        GameTime* getStartTime();
    };
}

#endif //INF_PROJECT_TIMESPACE_H
