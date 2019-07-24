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

ColorNormalized getGoalsColor(int address, ControllerState state, int16_t freq0,
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
    return ColorNormalized(getGoalsColorPortable(address, state, freq_input));
}

ColorNormalized getLinesColor(int address, ControllerState state, int16_t freq0,
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
    return ColorNormalized(getLinesColorPortable(address, state, freq_input));
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("getGoalsColor", &getGoalsColor)
    ;
    emscripten::function("getLinesColor", &getLinesColor)
    ;
    emscripten::enum_<ChannelType>("ChannelType")
        .value("GOALPOST", ChannelType::GOALPOST)
        .value("LINES", ChannelType::LINES)
        .value("NOTCONNECTED", ChannelType::NOTCONNECTED)
        ;
    emscripten::class_<Position>("Position")
        .constructor<>()
        .property("x", &Position::x)
        .property("y", &Position::y)
        .property("z", &Position::z)
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
        ;
    emscripten::class_<ControllerState>("ControllerState")
        .constructor<>()
        .property("tick", &ControllerState::tick)
        .property("goal_left", &ControllerState::goal_left)
        .property("goal_right", &ControllerState::goal_right)
        .property("music_on", &ControllerState::music_on)
        .function("updateEvent", &ControllerState::updateEvent)
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
