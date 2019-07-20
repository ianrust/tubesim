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

//assumes all LEDs are in 1 group for each pole
void addressToImageIndex(size_t address, size_t& x, size_t& y) {
    y = address % 50;
    x = address / 50;
    if (x % 2 == 0) {
        y = 50 - y;
    }
}

//assumes all LEDs are in 1 group for each pole, 12 strips
void addressToCartesianPoint(size_t address, float& x_cart, float& y_cart, float& z_cart) {
    size_t x, y;
    addressToImageIndex(address, x, y);
    z_cart = y * 5.0/50.0;
}

// This will also take in the frequency information as well as any other inputs/state (ie button press changes state)
Color8bit getGoalsColorPortable(size_t address, ControllerState state, int16_t* freq) {
    normalize255(freq);
    if (state.music_on) {
        if (isClapping(freq)) {
            return Color8bit(255, 255, 255);
        } else {
            return Color8bit(int(freq[0]*2*(address % 300) / 8),
                             int((freq[1] + freq[2] + freq[3] + freq[4])/4*(address % 100)/16),
                             int(freq[5]*(address % 50)));
        }
    } else {
        // only effect left/right adresses
        if (address > 1200 && state.goal_right) {
            return Color8bit(uint8_t(255), uint8_t(0), organic[state.tick % organic_len]);
        } else if (address <= 1200 && state.goal_left) {
            return Color8bit(uint8_t(255), uint8_t(0), organic[state.tick % organic_len]);
        }
        size_t x, y;
        float x_cart, y_cart, z_cart;
        addressToCartesianPoint(address%300, x_cart, y_cart, z_cart);
        addressToImageIndex(address%300, x, y);
        size_t offset_x = (state.tick / 8) % organic_width;
//        size_t offset_y = (state.tick / 3) % 30;
        size_t rgb_start = (y * organic_width + x + offset_x) * 3;
        float brightness = float(organic[rgb_start] + organic[rgb_start+1] + organic[rgb_start+2]) / (3.0 * 255.0);

        int grad_level = z_cart * 255 / 5;

        return Color8bit(int(grad_level), int((255-grad_level)*brightness), int((1.0-brightness)*255));
//        return Color8bit(pastel[rgb_start], pastel[rgb_start+1], pastel[rgb_start+2]);
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, ControllerState state, int16_t* freq) {
    return Color8bit(0, 0, 1.0);
}
