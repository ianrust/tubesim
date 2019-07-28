#pragma once

#include <math.h>
#include "spectrum_analysis.h"
#include "mapping.h"
#include "types.h"
#include "fastmath.h"
#include "images.h"

using namespace std;

Color8bit RED = Color8bit(255, 0, 0);
Color8bit YELLOW = Color8bit(255, 255, 0);

/**
 * A test pattern to see ticks and sim working.
 */
Color8bit TestPattern(size_t address, ControllerState state, int16_t* freq) {
    int r = uint8_t(address + state.tick + 130) % 256;
    int g = uint8_t(address + state.tick + (mapping_config.pitch_length_half)) % 256;
    int b = uint8_t(address + state.tick + 70) % 256;
    return Color8bit(r,g,b);
}

Color8bit Waves(size_t address, ControllerState state, int16_t* freq) {
    Position pos = mapping_config.addressToCartesianPoint(address);
    int16_t bass = freq[0];
    float bass_percentage = float(bass) / float(32767);
    float max_height = mapping_config.pixel_height * mapping_config.num_goal_leds_excluded_double;
    if (bass_percentage * 1000 < pos.z) { 
        return YELLOW;
    }
    return RED;
}


Color8bit testLightHausPattern(size_t address, ControllerState state, int16_t* freq) {
    float ratio;
    float theta = fmodFast(state.tick * 0.03, 2*M_PI);
    mapping_config.addressToLighthausParameterCartesian(address, 3, 0.1, state.tick, Position(cosFast(theta), sinFast(theta), 0), ratio);
//    mapping_config.addressToLighthausParameter(address, 0.5, 0.1, state.tick, ratio);
    return interpolate(Color8bit(138, 43, 226), Color8bit(0, 255, 0), ratio);
}

// This will also take in the frequency information as well as any other inputs/state 
// (ie button press changes state)
// The main color function, takes in:
//    - the address of the LED
//    - the controller state
Color8bit getGoalsColorPortable(size_t address, ControllerState state, int16_t* freq) {
    return Waves(address, state, freq);
    ImageIndex image_index = mapping_config.addressToImageIndex(address);
    Position position = mapping_config.addressToCartesianPoint(address);
    if (!image_index.valid) {
        return Color8bit(0, 0, 0);
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
        // only effect left/right adresses
        if (position.x > 0 && state.goal_right) {
            // image display example
            size_t x_offset = (state.tick/2);
            size_t y_offset = 0*(state.tick/2); // zero removes the scroll in that direction

            return getImageColor(pixel_triangles, address, x_offset, y_offset, false, true);
        } else if (position.x < 0 && state.goal_left) {
            // Mixing example
            size_t x_offset = (state.tick / 12);

            Color8bit image_color = getImageColor(organic, address, x_offset, 0, true, true);

            Position position = mapping_config.addressToCartesianPoint(address);
            int grad_level = position.z * 255 / 5;
            float brightness = float(image_color.r + image_color.g + image_color.b) / (3.0 * 255.0);

            return Color8bit(int(grad_level), int((255-grad_level)*brightness), int((1.0-brightness)*255));
        }

        // ratio example
        return testLightHausPattern(address, state, freq);

        // // gradient block
        // int g = int(255.0*(position.z)/5.0)*0;
        // int b = int(255.0*(position.x+10.0)/20.0);
        // int r = 255-b;
        // return Color8bit(r, g, b);
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, ControllerState state, int16_t* freq) {
    return testLightHausPattern(address, state, freq);

    // // crappy mod scroll example
    // float position.x, position.y, position.z;
    // mapping_config.addressToCartesianPoint(address, position.x, position.y, position.z);
    // int r = int(255.0*fabs(position.y+state.tick/3)/(mapping_config.pitch_width_half)) % 255;
    // int g = int(255.0*fabs(position.x+state.tick/3)/(mapping_config.pitch_length_half)) % 255;
    // int b = 255-r;
    // return Color8bit(r, g, b);
}
