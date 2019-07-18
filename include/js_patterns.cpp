#include <emscripten/bind.h>
#include "patterns.h"

using namespace emscripten;

struct ColorNormalized {
    float r;
    float g;
    float b;
    ColorNormalized() {}
    ColorNormalized(Color8bit color_8_bit) {
        r = color_8_bit.r / 255.0;
        g = color_8_bit.g / 255.0;
        b = color_8_bit.b / 255.0;
    }
};


ColorNormalized getGoalsColor(int address, int tick, bool goal_left, bool goal_right, int16_t freq0,
                                                                                      int16_t freq1,
                                                                                      int16_t freq2,
                                                                                      int16_t freq3,
                                                                                      int16_t freq4,
                                                                                      int16_t freq5,
                                                                                      int16_t freq6) {
    int16_t freq_input[7];
    freq_input[0] = freq0; 
    freq_input[1] = freq1; 
    freq_input[2] = freq2; 
    freq_input[3] = freq3; 
    freq_input[4] = freq4; 
    freq_input[5] = freq5; 
    freq_input[6] = freq6; 
    return ColorNormalized(getGoalsColorPortable(address, tick, goal_left, goal_right, freq_input));
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("getGoalsColor", &getGoalsColor);
    value_array<ColorNormalized>("ColorNormalized")
        .element(&ColorNormalized::r)
        .element(&ColorNormalized::g)
        .element(&ColorNormalized::b)
        ;
    value_array<Color8bit>("Color8bit")
        .element(&Color8bit::r)
        .element(&Color8bit::g)
        .element(&Color8bit::b)
        ;
}
