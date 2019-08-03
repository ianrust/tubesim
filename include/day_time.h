#pragma once

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

class Time {
    public:
        void init();
        uint8_t hours();
        uint8_t minutes();
        uint8_t seconds();
   
    private:
        uint8_t init_hours;
        uint8_t init_minutes;
        uint8_t init_seconds;
};

void Time::init()
{
    // hh:mm:ss
    char timestr[] = __TIME__;
    timestr[2] = '\0'; // a bit jank, but just string parse
    timestr[5] = '\0';

    init_hours = atoi(timestr) % 24;
    init_minutes = atoi(timestr + 3) % 60;
    init_seconds = atoi(timestr + 6) % 60;
}

// returns the number of seconds since original boot
unsigned long seconds_since_boot() {
    unsigned long delta = millis(); 
    return delta / 1000;
}

// returns the hour of day, overflows every 50 days!
uint8_t Time::hours() {
    unsigned long delta = seconds_since_boot(); // total seconds elapsed
    unsigned long delta_minutes = delta / 60;   // total minutes elapsed
    unsigned long delta_hours = delta_minutes / 60; // total hours elapsed

    unsigned long minute_diff = (init_seconds + (delta % 60)) / 60; // diff contributed by seconds to minutes
    unsigned long hour_diff = ((init_minutes + delta_minutes + minute_diff) / 60) % 24;  // dif contributed by minutes to hours

    return (init_hours + delta_hours + hour_diff) % 24;
}

// returns the minute of the day, overflows every 50 days!
uint8_t Time::minutes() {
    unsigned long delta = seconds_since_boot();
    unsigned long delta_minutes = delta / 60;

    unsigned long minute_diff = (init_seconds + (delta % 60)) / 60; // diff contributed by seconds to minutes
    return (init_minutes + delta_minutes + minute_diff) % 60;
}

// returns the second of the day, overflows every 50 days!
uint8_t Time::seconds() {
    unsigned long delta = seconds_since_boot();
    return (init_seconds + delta) % 60;
}