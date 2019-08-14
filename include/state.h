#pragma once

#include "types.h"
#include "schedule.h"

class ControllerState {
public:
    bool goal_left = false;
    bool goal_right = false;
    bool music_on = false;
    uint32_t tick = 0;
    ScheduleDatum schedule_datum;
    Time now_stored = {
        0, 0, 0
    };
    ControllerState(){};

    // Sim interface
    // catches the edges but modifies no output state
    void updateEvent(bool button_left, bool button_right) {
        if (button_left) {
            last_tick_left = tick;
        }

        if (button_right) {
            last_tick_right = tick;
        }
    }

    void updateOutputState() {
        goal_left = (tick - last_tick_left) < goal_period && last_tick_left != 0;
        goal_right = (tick - last_tick_right) < goal_period && last_tick_right != 0;
        tick++;
        ScheduleIndex schedule_index = getScheduleIndex(now_stored, schedule, SCHEDULE_SIZE);
        schedule_datum = interpolate(schedule[schedule_index.index1], schedule[schedule_index.index2], now_stored);
    }

    // Arduino Interface

    void update(bool button_left, bool button_right, int16_t* freq, Time now) {
        music_on = sum(freq) > 0;
        updateEvent(button_left, button_right);
        now_stored = now;
        updateOutputState();
    }

    void getGoalTimeRatio(float& ratio_left, float& ratio_right) {
        ratio_left = float(tick - last_tick_left) / goal_period;
        ratio_right = float(tick - last_tick_right) / goal_period;
    }
private:
    uint32_t last_tick_left = 0;
    uint32_t last_tick_right = 0;
    uint32_t goal_period = 30;
};