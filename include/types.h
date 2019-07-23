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