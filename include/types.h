#pragma once

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