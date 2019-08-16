#pragma once

#include "types.h"
#include "schedule.h"

const size_t MAX_SAFE_RAND = 100000;
inline int safe_rand() {
    return rand() % MAX_SAFE_RAND;
}

class PostAnimation {
public:
    Animation animation;

    bool active = false;
    bool mask = false;

    Color8bit color1;
    Color8bit color2;
    Color8bit color3;
    Color8bit color4;

    size_t last_active_tick = 0;
    size_t duration = 0;

    PostAnimation() {
        animation = animation_schedule[0];
    }

    void start(const size_t& tick_, const size_t& duration_) {
        if (!active) {
            last_active_tick = tick_;
            duration = duration_;
            animation = animation_schedule[rand() % ANIMATIONS_SIZE];
            int mask_threshold = MAX_SAFE_RAND * (1-animation.mask_prob);
            mask = safe_rand() > mask_threshold;
            color1 = Color8bit(safe_rand() % 255, safe_rand() % 255, safe_rand() % 255);
            color2 = Color8bit(safe_rand() % 255, safe_rand() % 255, safe_rand() % 255);
            color3 = Color8bit(safe_rand() % 255, safe_rand() % 255, safe_rand() % 255);
            color4 = Color8bit(safe_rand() % 255, safe_rand() % 255, safe_rand() % 255);
        }
        update(tick_);
    }

    void update(const size_t& tick) {
        if (active && tick > (last_active_tick + duration)) {
            active = false;
        } else if (!active && tick >= last_active_tick && tick <= (last_active_tick + duration)) {
            active = true;
        }
    }

};

class AnimationState {
public:
    AnimationState(){
        for (size_t i = 0; i < 8; i++) {
            post_animations[i] = PostAnimation();
        }
    };

    PostAnimation post_animations[8];

    int threshold =  MAX_SAFE_RAND - 200;
    int divisor = 250;

    void update(const size_t& tick) {
        for (size_t i = 0; i < 8; i++) {
            if (safe_rand() > threshold) {
                post_animations[i].start(tick, safe_rand()/divisor);
            }
            post_animations[i].update(tick);
        }
    }

};

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
    AnimationState animation_state;
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

//        decide where in the color schedule we are
        ScheduleIndex schedule_index = getScheduleIndex(now_stored, schedule, SCHEDULE_SIZE);
        schedule_datum = interpolate(schedule[schedule_index.index1], schedule[schedule_index.index2], now_stored);

//        decide if we should randomly do an animation
        animation_state.update(tick);
    }

    // Arduino Interface

    void update(bool button_left, bool button_right, int16_t* freq, Time now) {
        music_on = sum(freq) > 0;
        updateEvent(button_left, button_right);
        now_stored = now;
        updateOutputState();
    }

    void getGoalTimeRatio(float& ratio_left, float& ratio_right) const {
        ratio_left = float(tick - last_tick_left) / goal_period;
        ratio_right = float(tick - last_tick_right) / goal_period;
    }
private:
    uint32_t last_tick_left = 0;
    uint32_t last_tick_right = 0;
    uint32_t goal_period = 30;
};