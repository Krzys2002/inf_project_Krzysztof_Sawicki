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
        int dayFromStart;
        int dayOfYear;
        int year;
        Days day;

    public:
        GameTime()
        {
            dayFromStart = 0;
            dayOfYear = 0;
            year = 0;
            day = Days::Monday;
        }
        ~GameTime()
        {

        }

        // set time on the next day
        void NextDay();

        int getDayFromStart() const
        {
            return dayFromStart;
        }
        int getDayOfYear() const
        {
            return dayOfYear;
        }
        int getYear() const
        {
            return year;
        }
        Days getDay() const
        {
            return day;
        }
        Months getMonth() const
        {
            int monthID = dayOfYear / 30;
            if (monthID > 11)
            {
                monthID = 11;
            }

            return static_cast<Months>(monthID);
        }

        int getDayOfMonth() const
        {
            return dayOfYear % 30;
        }

        Seasons getSeason() const
        {
            int monthID = dayOfYear / 30;
            if (monthID > 11)
            {
                monthID = 11;
            }

            return static_cast<Seasons>(monthID / 3);
        }
    };
}

#endif //INF_PROJECT_TIMESPACE_H
