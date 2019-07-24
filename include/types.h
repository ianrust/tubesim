#pragma once
#include "gamma.h"

using namespace std;

struct Color8bit {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color8bit() {}
    Color8bit(int r_, int g_, int b_) {
        r = gamma8[min(255, max(r_, 0))];
        g = gamma8[min(255, max(g_, 0))];
        b = gamma8[min(255, max(b_, 0))];
    }
    Color8bit(uint8_t r_, uint8_t g_, uint8_t b_) {
        r = gamma8[r_];
        g = gamma8[g_];
        b = gamma8[b_];
    }
};

class ControllerState {
public:
    bool goal_left = false;
    bool goal_right = false;
    bool music_on = false;
    uint32_t tick = 0;
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
    }

    // Arduino Interface
    void update(bool button_left, bool button_right, int16_t* freq) {
        music_on = sum(freq);
        updateEvent(button_left, button_right);
        updateOutputState();
    }
private:
    uint32_t last_tick_left = 0;
    uint32_t last_tick_right = 0;
    uint32_t goal_period = 60;
};