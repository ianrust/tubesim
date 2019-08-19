#include <emscripten/bind.h>
#include "freq_buffer.h"
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

ColorNormalized getGoalsColor(size_t address, ControllerState state, FreqBuffer freq_buffer) {
    return ColorNormalized(getGoalsColorPortable(address, state, freq_buffer));
}

ColorNormalized getLinesColor(size_t address, ControllerState state, FreqBuffer freq_buffer) {
    return ColorNormalized(getLinesColorPortable(address, state, freq_buffer));
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("getGoalsColor", &getGoalsColor)
    ;
    emscripten::function("getLinesColor", &getLinesColor)
    ;
    emscripten::function("initializeTrigTables", &initializeTrigTables)
    ;
    emscripten::function("initializePerlinMats", &initializePerlinMats)
    ;
    emscripten::function("timeFromDaySeconds", &timeFromDaySeconds)
    ;
    emscripten::enum_<ChannelType>("ChannelType")
        .value("GOALPOST", ChannelType::GOALPOST)
        .value("LINES", ChannelType::LINES)
        .value("NOTCONNECTED", ChannelType::NOTCONNECTED)
        ;
    emscripten::class_<Time>("Time")
        .property("hours", &Time::hours)
        .property("minutes", &Time::minutes)
        .property("seconds", &Time::seconds)
        ;
    emscripten::class_<Position>("Position")
        .constructor<>()
        .property("x", &Position::x)
        .property("y", &Position::y)
        .property("z", &Position::z)
        ;
    emscripten::class_<FreqBuffer>("FreqBuffer")
        .constructor<>()
        .function("saveSingle", &FreqBuffer::saveSingle)
        .function("getValue", &FreqBuffer::getValue)
        ;
    emscripten::class_<MappingConfig>("MappingConfig")
        .constructor<>()
        .property("leds_per_channel", &MappingConfig::leds_per_channel)
        .property("pitch_length", &MappingConfig::pitch_length)
        .property("pitch_width", &MappingConfig::pitch_width)
        .property("pitch_length_half", &MappingConfig::pitch_length_half)
        .property("pitch_width_half", &MappingConfig::pitch_width_half)
        .property("addresses_per_goal", &MappingConfig::addresses_per_goal)
        .property("goal_led_strip_length", &MappingConfig::goal_led_strip_length)
        .property("addresses_per_goal", &MappingConfig::addresses_per_goal)
        .property("radius", &MappingConfig::radius)
        .property("pixel_height", &MappingConfig::pixel_height)
        .property("pixel_length", &MappingConfig::pixel_length)
        .property("line_width", &MappingConfig::line_width)
        .function("getChannelType", &MappingConfig::getChannelType)
        .function("getPosition", &MappingConfig::getPosition)
        .function("isGoal", &MappingConfig::isGoal)
        .function("isLine", &MappingConfig::isLine)
        ;
    emscripten::class_<ControllerState>("ControllerState")
        .constructor<>()
        .property("tick", &ControllerState::tick)
        .property("now_stored", &ControllerState::now_stored)
        .property("goal_left", &ControllerState::goal_left)
        .property("goal_right", &ControllerState::goal_right)
        .property("music_on", &ControllerState::music_on)
        .function("updateEvent", &ControllerState::updateEvent)
        .function("updatePattern", &ControllerState::updatePattern)
        .function("updateOutputState", &ControllerState::updateOutputState)
        ;
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
