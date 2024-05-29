//
// Created by Krzysztof Sawicki on 14/05/2024.
//

#include "../Headers/TimeSpace.h"

namespace TimeSpace
{
    std::string to_string(Months month)
    {
        switch(month)
        {
            case Months::January: return "January";
            case Months::February: return "February";
            case Months::March: return "March";
            case Months::April: return "April";
            case Months::May: return "May";
            case Months::June: return "June";
            case Months::July: return "July";
            case Months::August: return "August";
            case Months::September: return "September";
            case Months::October: return "October";
            case Months::November: return "November";
            case Months::December: return "December";
            default: return "Invalid month";
        }
    }

    std::string to_string(Days day)
    {
        switch(day)
        {
            case Days::Monday: return "Monday";
            case Days::Tuesday: return "Tuesday";
            case Days::Wednesday: return "Wednesday";
            case Days::Thursday: return "Thursday";
            case Days::Friday: return "Friday";
            case Days::Saturday: return "Saturday";
            case Days::Sunday: return "Sunday";
            default: return "Invalid day";
        }
    }

    std::string to_string(Seasons season)
    {
        switch(season)
        {
            case Seasons::Spring: return "Spring";
            case Seasons::Summer: return "Summer";
            case Seasons::Autumn: return "Autumn";
            case Seasons::Winter: return "Winter";
            default: return "Invalid season";
        }
    }

    std::ostream& operator<<(std::ostream& os, TimeSpace::Months month)
    {
        os << TimeSpace::to_string(month);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, TimeSpace::Days day)
    {
        os << TimeSpace::to_string(day);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, TimeSpace::Seasons season)
    {
        os << TimeSpace::to_string(season);
        return os;
    }

    int GameTime::daysInMonth = 28;

    // Method to get dayOfYear
    int GameTime::getDayOfYear() const
    {
        return static_cast<int>(month) * daysInMonth + dayOfMonth;
    }

    // Method to get year
    int GameTime::getYear() const
    {
        return year;
    }

    // Method to get dayOfWeek
    Days GameTime::getDayOfWeek() const
    {
        return dayOfWeek;
    }

    int GameTime::getDayOfMonth() const
    {
        return dayOfMonth;
    }

    // Method to get month
    Months GameTime::getMonth() const
    {
        return month;
    }

    // Method to get season
    Seasons GameTime::getSeason() const
    {
        int monthID = static_cast<int>(month);
        //shifting the months by 10, so the winter will start in December
        return static_cast<Seasons>((monthID + 10) % 12 / 3);
    }

    // Method to get difference between two dates in years (absolute value)
    int GameTime::yearDifference(const GameTime& time1, const GameTime& time2)
    {
        int difference = abs(time1.year - time2.year);
        if(time1 > time2)
        {
            if(time1.month < time2.month || (time1.month == time2.month && time1.dayOfMonth < time2.dayOfMonth))
            {
                difference--;
            }
        } else if(time1 != time2)
        {
            if(time1.month > time2.month || (time1.month == time2.month && time1.dayOfMonth > time2.dayOfMonth))
            {
                difference--;
            }
        }
        if(difference < 0)
        {
            difference = 0;
        }

        return difference;
    }

    // Method to get difference between two dates in months (absolute value)
    int GameTime::monthDifference(const GameTime& time1, const GameTime& time2)
    {
        int difference = yearDifference(time1, time2) * 12;
        if(time1.year == time2.year)
        {
            difference += abs(static_cast<int>(time1.month) - static_cast<int>(time2.month));
        }
        else
        {
            if(time1.month > time2.month)
            {
                difference += abs(static_cast<int>(time1.month) - static_cast<int>(time2.month));
            }
            else
            {
                difference +=  abs(static_cast<int>(time1.month) - static_cast<int>(time2.month));
            }
        }

        if(time1.month == time2.month)
        {
            if(time1.dayOfMonth < time2.dayOfMonth)
            {
                difference--;
            }
        }

        if(difference < 0)
        {
            difference = 0;
        }
        return difference;
    }

    // Method to get difference between two dates in days (absolute value)
    int GameTime::dayDifference(const GameTime& time1, const GameTime& time2)
    {
        int difference = monthDifference(time1, time2) * daysInMonth;
        difference += abs(time1.dayOfMonth - time2.dayOfMonth);
        return difference;
    }

    // operator to compare two dates for equality
    bool GameTime::operator==(const GameTime& other) const
    {
        return dayOfMonth == other.dayOfMonth && month == other.month && year == other.year;
    }
    // operator to compare two dates for inequality
    bool GameTime::operator!=(const GameTime& other) const
    {
        return !(*this == other);
    }
    // operator to compare two dates for later date
    bool GameTime::operator>(const GameTime& other) const
    {
        if(year > other.year)
        {
            return true;
        }
        else if(year == other.year)
        {
            if(static_cast<int>(month) > static_cast<int>(other.month))
            {
                return true;
            }
            else if(month == other.month)
            {
                if(dayOfMonth > other.dayOfMonth)
                {
                    return true;
                }
            }
        }
        return false;
    }
    // operator to compare two dates for earlier date
    bool GameTime::operator<(const GameTime& other) const
    {
        return !(*this > other) && *this != other;
    }

    GameTime::GameTime(int dayOfMonth, Months month, int year, Days dayOfWeek)
    {
        this->dayOfMonth = dayOfMonth;
        this->month = month;
        this->year = year;
        this->dayOfWeek = dayOfWeek;
    }

    GameTime::~GameTime()
    {

    }

    // Method to set time on the next day
    void GameTime::NextDay()
    {
        // Increment dayOfMonth
        dayOfMonth++;

        // If dayOfMonth is more than daysInMonth, reset it to 0 and increment month
        if(dayOfMonth > daysInMonth)
        {
            dayOfMonth = 0;

            // Increment month and check if it is more than 11
            int monthID = static_cast<int>(month);
            monthID++;
            if(monthID > 11)
            {
                // If it is more than 11, reset it to 0 and increment year
                monthID = 0;
                year++;
            }
            month = static_cast<Months>(monthID);
        }

        // Calculate dayID and set dayOfWeek
        int dayID = static_cast<int>(dayOfWeek) + 1 % 7;
        dayOfWeek = static_cast<Days>(dayID);
    }

    GameTimeSystem::GameTimeSystem(GameTime startTime)
    {
        currentTime = new GameTime(startTime);
        this->startTime = new GameTime(startTime);
        dayFromStart = 0;
    }

    GameTimeSystem::~GameTimeSystem()
    {
        delete currentTime;
        delete startTime;
    }

    // Method to set time on the next day
    void GameTimeSystem::NextDay()
    {
        currentTime->NextDay();
        dayFromStart++;
    }

    // Method to get currentTime
    GameTime* GameTimeSystem::getCurrentTime()
    {
        return currentTime;
    }

    // Method to get startTime
    GameTime* GameTimeSystem::getStartTime()
    {
        return startTime;
    }


    // Method to get dayFromStart
    int GameTimeSystem::getDayFromStart()
    {
        return dayFromStart;
    }
}
