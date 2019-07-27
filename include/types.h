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
        music_on = sum(freq) > 0;
        updateEvent(button_left, button_right);
        updateOutputState();
    }
private:
    uint32_t last_tick_left = 0;
    uint32_t last_tick_right = 0;
    uint32_t goal_period = 60;
};