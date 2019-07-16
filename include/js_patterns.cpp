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

ColorNormalized getGoalsColor(int address, int tick) {
    return ColorNormalized(getGoalsColorPortable(address, tick));
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("getGoalsColor", &getGoalsColor);
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
