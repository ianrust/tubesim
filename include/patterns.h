#pragma once

#include <math.h>
#include "spectrum_analysis.h"
#include "mapping.h"
#include "types.h"
#include "fastmath.h"
#include "images.h"
#include "perlin.h"
#include "state.h"

using namespace std;

/**
 * A test pattern to see ticks and sim working.
 */
Color8bit TestPattern(const size_t& address, const ControllerState& state, int16_t* freq) {
    int r = uint8_t(address + state.tick + 130) % 256;
    int g = uint8_t(address + state.tick + (mapping_config.pitch_length_half)) % 256;
    int b = uint8_t(address + state.tick + 70) % 256;
    return Color8bit(r,g,b);
}

Color8bit testLightHausPattern(const size_t& address, const ControllerState& state, int16_t* freq) {
    float ratio;
//    float theta = fmodFast(state.tick * 0.03, 2*M_PI);
//    mapping_config.addressToLighthausParameterCartesian(address, 3, 0.1, state.tick, Position(cosFast(theta), sinFast(theta), 0), ratio);
    mapping_config.addressToLighthausParameter(address, 0.5, 0.1, state.tick, ratio);
    return interpolate(Color8bit(138, 43, 226), Color8bit(255, 182, 93), ratio);
}

Color8bit lightHausPattern(const size_t& address, const ControllerState& state, int16_t* freq) {
    float ratio;
    mapping_config.addressToLighthausParameter(address, state.schedule_datum.num_wraps, state.schedule_datum.speed, state.tick, ratio);
    Position position = mapping_config.addressToCartesianPoint(address);
    if (position.x < 0) {
        return normalize(interpolate(state.schedule_datum.left_color1, state.schedule_datum.left_color2, ratio));
    } else {
        return normalize(interpolate(state.schedule_datum.right_color1, state.schedule_datum.right_color2, ratio));
    }
}

Color8bit getRandomAnimation(const size_t& address, const ControllerState& state, bool& actually_display) {
    PostAnimation post_animation = state.animation_state.post_animations[mapping_config.getChannel(address)];
    if (post_animation.active) {
        actually_display = true;
        if (post_animation.mask) {
            Position position = mapping_config.addressToCartesianPoint(address);
            float ratio = position.z / (mapping_config.pixel_height * mapping_config.goal_led_strip_length_cropped);
            return getImageColor(post_animation.animation, address, state.tick, post_animation.color1, post_animation.color2, post_animation.color3, post_animation.color4, ratio);
        } else {
            return getImageColor(post_animation.animation, address, state.tick);
        }
    } else {
        actually_display = false;
        return Color8bit(0,0,0);
    }
};

Color8bit explode(const size_t& address, const Position& position, const Position& origin, const float& ratio) {
    float dx = position.x - origin.x;
    float dy = position.y - origin.y;
    float dz = position.z - origin.z;
    float distance_from_base_squared = dx*dx + dy*dy + dz*dz;
    float max_distance_squared = mapping_config.pitch_length_half * mapping_config.pitch_length_half;
    float my_ratio = distance_from_base_squared / max_distance_squared;
    if (ratio > my_ratio) {
        return Color8bit(uint8_t(255*rand())%255, uint8_t(255*rand())%255, uint8_t(255*rand())%255);
    } else {
        float front_progress = 0.3*(my_ratio - ratio) / (1-ratio);
        return Color8bit(uint8_t(255*front_progress*rand())%255, uint8_t(255*front_progress*rand())%255, uint8_t(255*front_progress*rand())%255);
    }
}

// This will also take in the frequency information as well as any other inputs/state 
// (ie button press changes state)
// The main color function, takes in:
//    - the address of the LED
//    - the controller state
Color8bit getGoalsColorPortable(const size_t& address, const ControllerState& state, FreqBuffer& freq_buffer) {
    ImageIndex image_index = mapping_config.addressToImageIndex(address);
    Position position = mapping_config.addressToCartesianPoint(address);
    if (!image_index.valid) {
        return Color8bit(0, 0, 0);
    }

    if (state.music_on) {
            size_t distance_from_center = (image_index.y > mapping_config.goal_led_strip_length_cropped/2) ?
                                            image_index.y - mapping_config.goal_led_strip_length_cropped/2 :
                                            mapping_config.goal_led_strip_length_cropped/2 - image_index.y;
            Color8bit spec_color = freq_buffer.getColor(distance_from_center, mapping_config.getStrip(address));
            return interpolate(spec_color, Color8bit(0,0,0), float(distance_from_center*3)/(sum(freq_buffer.getArray(0))));
    } else {
        float goal_ratio_left, goal_ratio_right;
        state.getGoalTimeRatio(goal_ratio_left, goal_ratio_right);
        // only effect left/right adresses
        if (state.goal_right) {
            return explode(address, position, Position(mapping_config.pitch_length/2.0, 0, 0), goal_ratio_right);
        } else if (state.goal_left) {
            return explode(address, position, Position(-mapping_config.pitch_length/2.0, 0, 0), goal_ratio_left);
        }

        bool pattern_on;
        Color8bit pattern = getRandomAnimation(address, state, pattern_on);
        if (pattern_on) {
            return pattern;
        } else {
            return lightHausPattern(address, state, freq_buffer.getArray(0));
        }
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(const size_t& address, const ControllerState& state, FreqBuffer& freq_buffer) {
    Position position = mapping_config.addressToCartesianPoint(address);
    if (state.music_on) {
        if (isClapping(freq_buffer.getArray(0))) {
            return Color8bit(255, 255, 255);
        } else {
            Color8bit c1 = freq_buffer.getColor(0, ((address % mapping_config.leds_per_channel) / LINES_BINS) % 12);
            Color8bit c2 = freq_buffer.getColor(0, (((address % mapping_config.leds_per_channel) / LINES_BINS) % 12 + 1) %12);
            float ratio_line = float(address % LINES_BINS) / LINES_BINS ;
            return interpolate(c1, c2, ratio_line);
        }
    } else if (state.goal_right) {
        float goal_ratio_left, goal_ratio_right;
        state.getGoalTimeRatio(goal_ratio_left, goal_ratio_right);
        return explode(address, position, Position(mapping_config.pitch_length/2.0, 0, 0), goal_ratio_right);
    } else if (state.goal_left) {
        float goal_ratio_left, goal_ratio_right;
        state.getGoalTimeRatio(goal_ratio_left, goal_ratio_right);
        return explode(address, position, Position(-mapping_config.pitch_length/2.0, 0, 0), goal_ratio_left);
    } else {
        return lightHausPattern(address, state, freq_buffer.getArray(0));
    }
}
