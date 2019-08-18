#pragma once

#include <iostream>
#include "fastmath.h"
#include "types.h"

enum ChannelType {
    GOALPOST = 0,
    LINES = 1,
    NOTCONNECTED = 2
};

class MappingConfig {
public:
    // global settings
    size_t leds_per_channel = 700;
    size_t total_leds = 8*leds_per_channel;

    // caches
    Position addressToCartesianPoint_cache[5600];
    ImageIndex addressToImageIndex_cache[5600];

    float pitch_length = 20.0;
    float pitch_width = 15.0;
    float pitch_length_half;
    float pitch_width_half;

    // channel on the octo board
    ChannelType channels[8] = {
        ChannelType::GOALPOST,
        ChannelType::GOALPOST,
        ChannelType::LINES,
        ChannelType::NOTCONNECTED,
        ChannelType::GOALPOST,
        ChannelType::GOALPOST,
        ChannelType::LINES,
        ChannelType::NOTCONNECTED
    };
    Position positions[8];
    
    // goal settings
    size_t goal_led_strip_length = 50;
    size_t num_goal_leds_excluded = 5;
    size_t num_goal_leds_excluded_double;
    size_t goal_led_strip_length_cropped;
    size_t addresses_per_goal = 600;
    float pixel_height = 0.1;
    float goal_width_half = 2.5;
    float radius = 0.1;
    size_t num_strips = 6;

    // line settings
    float pixel_length = 0.05;
    float line_width = 0.1;

    MappingConfig() {
        goal_led_strip_length_cropped = goal_led_strip_length - num_goal_leds_excluded;
        pitch_length_half = pitch_length/2;
        pitch_width_half = pitch_width/2;
        num_goal_leds_excluded_double = num_goal_leds_excluded*2;
        positions[0] = Position(-pitch_length_half, -goal_width_half);
        positions[1] = Position(-pitch_length_half, goal_width_half);
        positions[2] = Position(1, 0); // line direction
        positions[4] = Position(pitch_length_half, goal_width_half);
        positions[5] = Position(pitch_length_half, -goal_width_half);
        positions[6] = Position(-1, 0); // line direction

        // initalize caches
        for (size_t i = 0; i < total_leds; i++) {
            addressToCartesianPoint_cache[i] = Position();
            addressToImageIndex_cache[i] = ImageIndex();
        }
    }

    bool isGoal(const size_t& address) {
        return channels[int(address / leds_per_channel)] == ChannelType::GOALPOST;
    }

    bool isLine(const size_t& address) {
        return channels[int(address / leds_per_channel)] == ChannelType::LINES;
    }

    size_t getChannel(const size_t& address) {
        return address / leds_per_channel;
    }

    ChannelType getChannelType(const size_t& channel) {
        return channels[channel];
    }

    Position getPosition(const size_t& channel) {
        return positions[channel];
    }

    //assumes all LEDs are in 1 group for each pole
    //removes last config-defined address on each shortened strip
    ImageIndex addressToImageIndex(const size_t& address) {
        if (addressToImageIndex_cache[address].cached) {
            return addressToImageIndex_cache[address];
        } else {
            ImageIndex out_index;
            size_t cropped_address = address % leds_per_channel;
            size_t gap = 0;
            size_t low = goal_led_strip_length_cropped;
            for (; (low < addresses_per_goal); low+=2*goal_led_strip_length) {
                if (cropped_address < low) {
                    break;
                } else if (cropped_address < (low+num_goal_leds_excluded_double)) {
                    out_index.valid = false;
                    addressToImageIndex_cache[address] = out_index;
                    addressToImageIndex_cache[address].cached = true;
                    return out_index;
                }
                gap+=num_goal_leds_excluded_double;
            }

            cropped_address -= gap;

            out_index.valid = true;
            out_index.x = (address % addresses_per_goal) / goal_led_strip_length;
            if (out_index.x % 2 == 0) {
                out_index.y = (cropped_address % goal_led_strip_length_cropped);
            } else {
                out_index.y = (goal_led_strip_length_cropped - 1) -
                    (cropped_address % goal_led_strip_length_cropped);
            }

            addressToImageIndex_cache[address] = out_index;
            addressToImageIndex_cache[address].cached = true;

            return out_index;
        }
    } 
 
    // assumes all LEDs are in 1 group for each pole, 12 strips
    //  TODO add position of pixel around the pole
    Position addressToCartesianPoint(const size_t& address) {
        if (addressToCartesianPoint_cache[address].cached) {
            return addressToCartesianPoint_cache[address];
        } else {
            Position out_position;

            size_t channel_index = address / leds_per_channel;
            // for goals
            if (isGoal(address)) {
                ImageIndex image_index = addressToImageIndex(address);
                // TODO add radius here
                out_position.x = positions[channel_index].x;
                out_position.y = positions[channel_index].y;
                out_position.z = image_index.y * pixel_height;
            } else { //for lines
                size_t progressIndex = address % leds_per_channel;
                int side = positions[channel_index].x;
                if (progressIndex < 200) {
                    out_position.x = side * float(progressIndex) * pixel_length;
                    out_position.y = (pitch_width_half);
                } else if (progressIndex < 500) {
                    out_position.x = side*(pitch_length_half);
                    out_position.y = (pitch_width_half) - (progressIndex+1 - 200) * pixel_length;
                } else {
                    out_position.x = side*((pitch_length_half) - (progressIndex+1 - 500) * pixel_length);
                    out_position.y = -(pitch_width_half);
                }
                out_position.z = 0;
            }

            addressToCartesianPoint_cache[address] = out_position;
            addressToCartesianPoint_cache[address].cached = true;

            return out_position;
        }
    }

    // num_wraps around the pole interpolated b/w 2 colors (parametrizes by ratio). wrapps on speed
    // which is in m/(offset index). offset is usually state.tick but you decide!
    void addressToLighthausParameter(const size_t& address, const float& num_wraps, const float& speed, const size_t& offset, float& ratio) {
        float progress = 0;
        // progress is the meter distance from midline to top of pole, manhattan distance;
        if (isGoal(address)) {
            ImageIndex image_index = addressToImageIndex(address);
            progress = image_index.y * pixel_height + pitch_length_half;
        } else if (isLine(address)) {
            Position position = addressToCartesianPoint(address);
            if (position.x < 0) {
                progress = -position.x;
            } else {
                progress = position.x;
            }
        }
        float period = (pitch_length_half + (goal_led_strip_length_cropped-1)*pixel_height) / num_wraps;

        // fabs/fmod are slow
        progress -= speed*offset;
        ratio = 2*fmodFast(progress, period) / period;
        if (ratio < 0) {
            ratio *= -1;
        }
        if (ratio > 1.0) {
            ratio *= 2-ratio;
        }
    }

    // interpolate b/w 2 colors in the direction defined by direction
    void addressToLighthausParameterCartesian(
        const size_t& address,
        const float& scale,
        const float& speed,
        const size_t& offset,
        const Position& direction,
        float& ratio
        ) {

        Position position = addressToCartesianPoint(address);
        float progress = position.x * direction.x + position.y * direction.y + position.z * direction.z;

        // fabs/fmod are slow
        progress -= speed*offset;
        ratio = 2*fmodFast(progress, scale) / scale;
        if (ratio < 0) {
            ratio *= -1;
        }
        if (ratio > 1.0) {
            ratio *= 2-ratio;
        }
    }

};

MappingConfig mapping_config;