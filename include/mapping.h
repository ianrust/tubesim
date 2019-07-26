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
    }

    bool isGoal(size_t address) const {
        return channels[int(address / leds_per_channel)] == ChannelType::GOALPOST;
    }

    bool isLine(size_t address) const {
        return channels[int(address / leds_per_channel)] == ChannelType::LINES;
    }

    ChannelType getChannelType(size_t channel) const {
        return channels[channel];
    }

    Position getPosition(size_t channel) const {
        return positions[channel];
    }

    //assumes all LEDs are in 1 group for each pole
    //removes last 5 address on each shortened strip
    void addressToImageIndex(size_t address, size_t& x, size_t& y, bool& valid) const {
        size_t cropped_address = address % leds_per_channel;
        size_t gap = 0;
        size_t low = goal_led_strip_length_cropped;
        for (; (low < addresses_per_goal); low+=2*goal_led_strip_length) {
            if (cropped_address < low) {
                break;
            } else if (cropped_address < (low+num_goal_leds_excluded_double)) {
                valid = false;
                return;
            }
            gap+=num_goal_leds_excluded_double;
        }

        cropped_address -= gap;

        valid = true;
        x = (address % addresses_per_goal) / goal_led_strip_length;
        if (x % 2 == 0) {
            y = (cropped_address % goal_led_strip_length_cropped);
        } else {
            y = (goal_led_strip_length_cropped - 1) -
                (cropped_address % goal_led_strip_length_cropped);
         }
    } 
 
    //a ssumes all LEDs are in 1 group for each pole, 12 strips
    //  TODO add position of pixel around the pole
    void addressToCartesianPoint(size_t address, float& x_cart, float& y_cart, float& z_cart) const {
        size_t x_image = 0;
        size_t y_image = 0;
        bool valid;
        size_t channel_index = address / leds_per_channel;
        // for goals
        if (isGoal(address)) {
            addressToImageIndex(address, x_image, y_image, valid);
            // TODO add radius here
            x_cart = positions[channel_index].x;
            y_cart = positions[channel_index].y;
            z_cart = y_image * pixel_height;
        } else { //for lines
            size_t progressIndex = address % leds_per_channel;
            int side = positions[channel_index].x;
            if (progressIndex < 200) {
                x_cart = side * float(progressIndex) * pixel_length;
                y_cart = (pitch_width_half);
            } else if (progressIndex < 500) {
                x_cart = side*(pitch_length_half); 
                y_cart = (pitch_width_half) - (progressIndex+1 - 200) * pixel_length; 
            } else {
                x_cart = side*((pitch_length_half) - (progressIndex+1 - 500) * pixel_length); 
                y_cart = -(pitch_width_half); 
            }
            z_cart = 0;
        }
    }

    // num_wraps around the pole interpolated b/w 2 colors (parametrizes by ratio). wrapps on speed
    // which is in m/(offset index). offset is usually state.tick but you decide!
    void addressToLighthausParameter(size_t address, float num_wraps, float speed, size_t offset, float& ratio) const {
        size_t x_image, y_image;
        bool valid;
        float progress;
        // progress is the meter distance from midline to top of pole, manhattan distance;
        if (isGoal(address)) {
            addressToImageIndex(address, x_image, y_image, valid);
            progress = y_image * pixel_height + pitch_length_half;
        } else if (isLine(address)) {
            float x_cart, y_cart, z_cart;
            addressToCartesianPoint(address, x_cart, y_cart, z_cart);
            if (x_cart < 0) {
                progress = -x_cart;
            } else {
                progress = x_cart;
            }
        }
        float period = (pitch_length_half + goal_led_strip_length_cropped*pixel_height) / num_wraps;

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
        size_t address, 
        float scale,
        float speed,
        size_t offset,
        const Position& direction,
        float& ratio
        ) const {

        float x_cart, y_cart, z_cart;
        addressToCartesianPoint(address, x_cart, y_cart, z_cart);
        float progress = x_cart * direction.x + y_cart * direction.y + z_cart * direction.z;

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

const MappingConfig mapping_config;