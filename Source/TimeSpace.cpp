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

    void GameTime::NextDay()
    {
        dayFromStart++;
        dayOfYear++;
        if(dayOfYear > 360)
        {
            dayOfYear = 0;
            year++;
        }

        int dayID = dayFromStart % 7;

        day = static_cast<Days>(dayID);
    }


}
