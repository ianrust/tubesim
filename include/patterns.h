#pragma once

#include "spectrum_analysis.h"
#include "types.h"
#include "../images/images.h"

using namespace std;

class ControllerState {
public:
    bool goal_left = false;
    bool goal_right = false;
    bool music_on = false;
    uint16_t tick = 0;
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
        goal_left = (tick - last_tick_left) < goal_period;
        goal_right = (tick - last_tick_right) < goal_period;
        tick++;
    }

    // Arduino Interface
    void update(bool button_left, bool button_right, int16_t* freq) {
        music_on = sum(freq);
        updateEvent(button_left, button_right);
        updateOutputState();
    }
private:
    uint16_t last_tick_left;
    uint16_t last_tick_right;
    uint16_t goal_period = 60;
};

// This will also take in the frequency information as well as any other inputs/state (ie button press changes state)
Color8bit getGoalsColorPortable(int address, ControllerState state, int16_t* freq) {
    normalize255(freq);
    if (state.music_on) {
        if (isClapping(freq)) {
            return Color8bit(255, 255, 255);
        } else {
            return Color8bit(freq[0]*2*(address % 300) / 8,
                            (freq[1] + freq[2] + freq[3] + freq[4])/4*(address % 100)/16,
                            freq[5]*(address % 50));
        }
    } else {
        // only effect left/right adresses
        if (address > 600 && state.goal_right) {
            return Color8bit(uint8_t(255), uint8_t(0), organic[state.tick % organic_len]);
        } else if (address <= 600 && state.goal_left) {
            return Color8bit(uint8_t(255), uint8_t(0), organic[state.tick % organic_len]);
        }
        return Color8bit(0, (state.tick + address)%300, address%160);
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, ControllerState state, int16_t* freq) {
    return Color8bit(0, 0, 1.0);
}
