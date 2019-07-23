#pragma once

#include <math.h>
#include "spectrum_analysis.h"
#include "types.h"
#include "../images/images.h"

using namespace std;

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
    uint32_t last_tick_left;
    uint32_t last_tick_right;
    uint32_t goal_period = 60;
};

//assumes all LEDs are in 1 group for each pole
//removes last 5 address on each shortened strip
void addressToImageIndex(size_t address, size_t& x, size_t& y, bool& valid) {
    size_t cropped_address = address % 700;
    size_t gap = 0;
    size_t low = 45;
    size_t last_low = 0;
    for (; (low < 600); low+=100) {
        if (cropped_address < low) {
            break;
        } else if (cropped_address < (low+10)) {
            valid = false;
            return;
        }
        gap+=10;
        last_low = low; 
    }

    cropped_address -= gap;

    valid = true;
    x = (address % 600) / 50;
    if (x % 2 == 0) {
        y = (cropped_address % 45);
    } else {
        y = 44 - (cropped_address % 45);
    }
}

//assumes all LEDs are in 1 group for each pole, 12 strips
// TODO add position of pixel around the pole
void addressToCartesianPoint(size_t address, float& x_cart, float& y_cart, float& z_cart) {
    size_t x, y;
    bool valid;
    // first 4 addresses are goals.
    bool goal = (address / 700) < 4;
    if (goal) {
        addressToImageIndex(address, x, y, valid);
    }
    size_t goal_index = address / 700;
    // for goals
    if (goal) {
        // from pitch.js
            // new Tube(-10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            // new Tube(-10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            // new Tube(10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            // new Tube(10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
        if (goal_index == 0) {
            x_cart = -10;
            y_cart = -2.5;
        } else if (goal_index == 1) {
            x_cart = -10;
            y_cart = 2.5;
        } else if (goal_index == 2) {
            x_cart = 10;
            y_cart = 2.5;
        } else if (goal_index == 3) {
            x_cart = 10;
            y_cart = -2.5;
        }
        z_cart = y * 4.5/45.0;
    } else { //for lines
        size_t progressIndex = address % 700;
        int side = (goal_index == 4) ? 1 : -1;
        if (progressIndex < 200) {
            x_cart = side * progressIndex * 0.05;
            y_cart = 7.5;
        } else if (progressIndex < 500) {
            x_cart = side*10; 
            y_cart = 7.5 - (progressIndex+1 - 200) * 0.05; 
        } else {
            x_cart = -side*(10 - (progressIndex+1 - 500) * 0.05); 
            y_cart = -7.5; 
        }
        z_cart = 0;
    }
}

/**
 * A test pattern to see ticks and sim working.
 */
Color8bit TestPattern(size_t address, ControllerState state, int16_t* freq) {
    int r = uint8_t(address + state.tick + 130) % 256;
    int g = uint8_t(address + state.tick + 10) % 256;
    int b = uint8_t(address + state.tick + 70) % 256;
    return Color8bit(r,g,b);
}

// This will also take in the frequency information as well as any other inputs/state 
// (ie button press changes state)
// The main color function, takes in:
//    - the address of the LED
//    - the controller state
Color8bit getGoalsColorPortable(size_t address, ControllerState state, int16_t* freq) {
    size_t x, y;
    bool valid;
    addressToImageIndex(address, x, y, valid);
    if (!valid) {
        return Color8bit(0, 0, 0);
    }
    normalize255(freq);
    if (state.music_on) {
        if (isClapping(freq)) {
            return Color8bit(255, 255, 255);
        } else {
            return Color8bit(int(freq[0]*2*(address % 300) / 8),
                             int((freq[1] + freq[2] + freq[3] + freq[4])/4*(address % 100)/16),
                             int(freq[5]*(address % 45)));
        }
    } else {
        // only effect left/right adresses
        if (address > 1200 && state.goal_right) {
            return Color8bit(uint8_t(255), uint8_t(0), organic[state.tick % organic_len]);
        } else if (address <= 1200 && state.goal_left) {
            return Color8bit(uint8_t(255), uint8_t(0), organic[state.tick % organic_len]);
        }

//         // pixels_triangle block
//         // bigger goes slower for 12
//         size_t offset_x = (state.tick/10) % eyeball_width;
//         // reverse direction by inverting offset_x:
//         offset_x = eyeball_width - 1 - offset_x;
//         size_t rgb_start = (((y+state.tick/3)%eyeball_height) * eyeball_width + (x + offset_x)%eyeball_width) * 3;

//         float total = eyeball[rgb_start]+eyeball[rgb_start+1]+eyeball[rgb_start+2];
//         float average = total/3;

//         return Color8bit(2*int((eyeball[rgb_start]-average/1.1)*255.0/total), 2*int((eyeball[rgb_start+1]-average/1.1)*255.0/total), 2*int((eyeball[rgb_start+2]-average/1.1)*255.0/total));
// //        return Color8bit(eyeball[rgb_start], eyeball[rgb_start+1], eyeball[rgb_start+2]);

    //    // Organic block
    //    size_t offset_x = (state.tick / 12) % organic_width;
    //    size_t rgb_start = (y * organic_width + (x + offset_x)) * 3;
    //    float x_cart, y_cart, z_cart;
    //    addressToCartesianPoint(address, x_cart, y_cart, z_cart);
    //    int grad_level = z_cart * 255 / 5.0;
    //    float brightness = float(organic[rgb_start] + organic[rgb_start+1] + organic[rgb_start+2]) / (3.0 * 255.0);
    //    return Color8bit(int(grad_level), int((255-grad_level)*brightness), int((1.0-brightness)*255));
        
        // gradient block
        float x_cart, y_cart, z_cart;
        addressToCartesianPoint(address, x_cart, y_cart, z_cart);
        int g = int(255.0*(z_cart)/5.0);
        int r = 255-g;
        return Color8bit(r, g, 0);
    
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, ControllerState state, int16_t* freq) {
    float x_cart, y_cart, z_cart;
    addressToCartesianPoint(address, x_cart, y_cart, z_cart);
    // int r = 255.0*fabs(x_cart)/10.0;
    int r;
    if (x_cart > 0) {
        r = 255.0*x_cart/10.0;
    } else {
        r = -255.0*x_cart/10.0;
    }
    // int r = 255.0*fabs(y_cart)/7.5;
    int b = 255-r;
    return Color8bit(r, 0, b);
}
