#pragma once

#include <math.h>
#include "spectrum_analysis.h"
#include "mapping.h"
#include "types.h"
#include "fastmath.h"
#include "images.h"
#include "state.h"

using namespace std;

Color8bit black = Color8bit(0, 0, 0);
Color8bit green = Color8bit(0, 255, 0);

/**
 * Flash one tube at a time in a spiral. At the beginning only the buttom of the tube is lit and over time,
 * more and more of the tube becomes lit. The spiral also goes faster over time.
 */
Color8bit SpiralPattern(size_t address, ControllerState state, int16_t* freq) {
    // Do not render the spiral where it would not be valid
    ImageIndex image_index = mapping_config.addressToImageIndex(address);
    if (!image_index.valid) {
        return black;
    }

    int periodNumber = (state.tick - state.current_pattern_tick) / 10;
    int interval = 120 - periodNumber;
    if (interval < 8) {
        interval = 8;
    }

    int litGoal = (periodNumber % 4) + 1;
    int goalNumber = mapping_config.getGoalNumber(address);

    if (goalNumber == litGoal) {
        Position position = mapping_config.addressToCartesianPoint(address);

        // Light up the tube from the bottom to the top over time.
        float z_position = 5 - interval * .05;
        if (z_position > position.z) {
            return state.current_pattern_color;
        }
    }

    return black;
}

/**
 * One color!
 */
Color8bit OneColor(size_t address, ControllerState state, int16_t* freq) {
    return state.current_pattern_color;
}

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
    return interpolate(Color8bit(138, 43, 226), Color8bit(0, 255, 0), ratio);
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
    float my_ratio = pow(distance_from_base_squared / max_distance_squared, 0.2);
    if (ratio > my_ratio) {
        return Color8bit(uint8_t(255*rand())%255, uint8_t(255*rand())%255, uint8_t(255*rand())%255);
    } else {
        float front_progress = 0.1*(my_ratio - ratio) / (1-ratio);
        return Color8bit(uint8_t(255*front_progress*rand())%255, uint8_t(255*front_progress*rand())%255, uint8_t(255*front_progress*rand())%255);
    }
}

// This will also take in the frequency information as well as any other inputs/state 
// (ie button press changes state)
// The main color function, takes in:
//    - the address of the LED
//    - the controller state
Color8bit getGoalsColorPortable(const size_t& address, const ControllerState& state, int16_t* freq) {
    ImageIndex image_index = mapping_config.addressToImageIndex(address);
    Position position = mapping_config.addressToCartesianPoint(address);
    if (!image_index.valid) {
        return Color8bit(0, 0, 0);
    }

    if (state.current_pattern == "s") {
        return SpiralPattern(address, state, freq);
    }

    if (state.current_pattern == "o") {
        return OneColor(address, state, freq);
    }

    normalize255(freq);
    if (state.music_on) {
        if (isClapping(freq)) {
            return Color8bit(255, 255, 255);
        } else {
            return Color8bit(int(freq[0]*2*(address % 300) / 8),
                             int((freq[1] + freq[2] + freq[3] + freq[4])/4*(address % 100)/16),
                             int(freq[5]*(address % 45)));
        }
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
            return lightHausPattern(address, state, freq);
        }
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(const size_t& address, const ControllerState& state, int16_t* freq) {
    return white;

    Position position = mapping_config.addressToCartesianPoint(address);
    if (state.goal_right) {
        float goal_ratio_left, goal_ratio_right;
        state.getGoalTimeRatio(goal_ratio_left, goal_ratio_right);
        return explode(address, position, Position(mapping_config.pitch_length/2.0, 0, 0), goal_ratio_right);
    } else if (state.goal_left) {
        float goal_ratio_left, goal_ratio_right;
        state.getGoalTimeRatio(goal_ratio_left, goal_ratio_right);
        return explode(address, position, Position(-mapping_config.pitch_length/2.0, 0, 0), goal_ratio_left);
    } else {
        return lightHausPattern(address, state, freq);
    }
}
