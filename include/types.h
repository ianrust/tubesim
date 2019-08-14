#pragma once

#include "spectrum_analysis.h"

using namespace std;

struct Color8bit {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color8bit() {}
    Color8bit(int r_, int g_, int b_) {
        r = min(255, max(r_, 0));
        g = min(255, max(g_, 0));
        b = min(255, max(b_, 0));
    }
    Color8bit(uint8_t r_, uint8_t g_, uint8_t b_) {
        r = r_;
        g = g_;
        b = b_;
    }
};

Color8bit interpolate(const Color8bit& c1, const Color8bit& c2, float ratio) {
    Color8bit interp_value;
    interp_value.r = c1.r * (1-ratio) + c2.r * ratio;
    interp_value.g = c1.g * (1-ratio) + c2.g * ratio;
    interp_value.b = c1.b * (1-ratio) + c2.b * ratio;
    return interp_value;
};

uint8_t interpolate(const uint8_t& v1, const uint8_t& v2, float ratio) {
    return v1 * (1-ratio) + v2 * ratio;
}

float interpolate(const float& v1, const float& v2, float ratio) {
    return v1 * (1-ratio) + v2 * ratio;
}

struct Time {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

Time timeFromDaySeconds(int day_seconds) {
    uint8_t hours = day_seconds / 3600;
    uint8_t minutes = (day_seconds - hours*3600) / 60;
    uint8_t seconds = (day_seconds - hours*3600 - minutes*60);
    return (Time){
        .hours = hours,
        .minutes = minutes,
        .seconds = seconds,
    };
}

Time interpolate(const Time& t1, const Time& t2, float ratio) {
    Time out = {
        .hours = interpolate(t1.hours, t2.hours, ratio),
        .minutes = interpolate(t1.minutes, t2.minutes, ratio),
        .seconds = interpolate(t1.seconds, t2.seconds, ratio),
    };
    return out;
}

// tells you if t2 is ahead of t1;
bool ahead(const Time& t1, const Time& t2) {
    if (t1.hours > t2.hours) {
        return false;
    } else if (t1.minutes > t2.minutes) {
        return false;
    } else if (t1.seconds > t2.seconds) {
        return false;
    } else {
        return true;
    }
}

float getRatioDumb(const Time& now, const Time& time1, const Time& time2) {
    float ratio = float(now.hours - time1.hours) / (time2.hours -  time1.hours);
    if ((time2.minutes -  time1.minutes) != 0) {
        float minutes_ratio = float(now.minutes - time1.minutes) / (time2.minutes -  time1.minutes);
        minutes_ratio /= 24.0;
        ratio += minutes_ratio;
    }
    if ((time2.seconds -  time1.seconds) != 0) {
        float seconds_ratio = float(now.seconds - time1.seconds) / (time2.seconds -  time1.seconds);
        seconds_ratio /= 24.0 * 60.0;
        ratio += seconds_ratio;
    }
    return ratio;
}

float getRatio(const Time& now, const Time& time1, const Time& time2) {
    if (ahead(time2, time1)) {
        Time time2_plus_one_day = time2;
        time2_plus_one_day.hours += 24;
        if (!ahead(time1, now)) {
            Time now_plus_one_day = now;
            now_plus_one_day.hours += 24;
            return getRatioDumb(now_plus_one_day, time1, time2_plus_one_day);
        }
        return getRatioDumb(now, time1, time2_plus_one_day);
    }
    return getRatioDumb(now, time1, time2);
}

struct ScheduleDatum {
    Time time;

    Color8bit color1;
    Color8bit color2;

    float speed;
    float num_wraps;
};

struct ScheduleIndex {
    size_t index1;
    size_t index2;
};

ScheduleIndex getScheduleIndex(const Time& now, const ScheduleDatum* schedule, size_t schedule_size) {
    size_t index_ahead = schedule_size;
    for (size_t index = 0; index < schedule_size; index++) {
        if (!ahead(schedule[index].time, now)) {
            index_ahead = index;
            break;
        }
    }

//    handle edges
    if (index_ahead == 0 || index_ahead == schedule_size) {
        return (ScheduleIndex){.index1 = schedule_size-1, .index2 = 0};
    } else {
        return (ScheduleIndex){.index1 = index_ahead-1, .index2 = index_ahead};
    }
}

ScheduleDatum interpolate(const ScheduleDatum& schedule_datum1, const ScheduleDatum& schedule_datum2, const Time now) {
    float ratio = getRatio(now, schedule_datum1.time, schedule_datum2.time);
    ScheduleDatum out = {
        .time = interpolate(schedule_datum1.time, schedule_datum2.time, ratio),
        .color1 = interpolate(schedule_datum1.color1, schedule_datum2.color1, ratio),
        .color2 = interpolate(schedule_datum1.color2, schedule_datum2.color2, ratio),
        .speed = interpolate(schedule_datum1.speed, schedule_datum2.speed, ratio),
        .num_wraps = interpolate(schedule_datum1.num_wraps, schedule_datum2.num_wraps, ratio),
    };
    return out;
}

struct FlashImage {
    size_t len;
    size_t width;
    size_t height;
    size_t start;
    FlashImage(size_t len_, size_t width_, size_t height_, size_t start_) {
        len = len_;
        width = width_;
        height = height_;
        start = start_;
    }
};

struct Cached {
    bool cached = false;
};

struct Position : Cached {
    float x = 0;
    float y = 0;
    float z = 0;
    Position(){};
    Position(float x_, float y_) {
        x = x_;
        y = y_;
        z = 0;
    }
    Position(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

struct ImageIndex : Cached {
    size_t x = 0;
    size_t y = 0;
    bool valid = false;
    ImageIndex(){};
};