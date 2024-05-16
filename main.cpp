#include <iostream>
#include "Headers/TimeSpace.h"

int main()
{
    TimeSpace::GameTime time;

    for(int i = 0; i < 1000; i++)
    {
        std::cout << "form Start: " << time.getDayFromStart()
        << " Year: " << time.getYear() << " month: " << time.getMonth() << " day: " << time.getDay()
        << " day of year: " << time.getDayOfYear() << " season: " << time.getSeason()
        << " DayID: " << time.getDay() << std::endl;

        time.NextDay();
    }
}
