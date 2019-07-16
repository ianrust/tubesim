#include <emscripten/bind.h>
#include "goal_pattern.h"

using namespace emscripten;

Color getGoalColor(int address, int tick) {
    return getGoalColorPortable(address, tick);
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("getGoalColor", &getGoalColor);
    value_array<Color>("Color")
        .element(&Color::r)
        .element(&Color::g)
        .element(&Color::b)
        ;
}
