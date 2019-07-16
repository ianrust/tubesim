#pragma once

struct Color8bit {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color8bit() {}
    Color8bit(uint8_t r_, uint8_t g_, uint8_t b_) {
        r = r_;
        g = g_;
        b = b_;
    }
};