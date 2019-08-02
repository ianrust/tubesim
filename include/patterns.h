#pragma once

#include <math.h>
#include "spectrum_analysis.h"
#include "mapping.h"
#include "types.h"
#include "fastmath.h"
#include "images.h"
#include "perlin.h"

using namespace std;

/**
 * A test pattern to see ticks and sim working.
 */
Color8bit TestPattern(size_t address, ControllerState state, int16_t* freq) {
    int r = uint8_t(address + state.tick + 130) % 256;
    int g = uint8_t(address + state.tick + (mapping_config.pitch_length_half)) % 256;
    int b = uint8_t(address + state.tick + 70) % 256;
    return Color8bit(r,g,b);
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
Color8bit getGoalsColorPortable(size_t address, ControllerState state, FreqBuffer& freq_buffer) {
    ImageIndex image_index = mapping_config.addressToImageIndex(address);
    Position position = mapping_config.addressToCartesianPoint(address);
    if (!image_index.valid) {
        return Color8bit(0, 0, 0);
    }

//    normalize255(freq);
    if (state.music_on) {
        return randColor((image_index.x + state.tick/2) % mapping_config.num_strips, freq_buffer.getArray(image_index.y));
    } else {
        // only effect left/right addresses
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
        return testLightHausPattern(address, state, freq_buffer.getArray(0));
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(size_t& address, ControllerState state, FreqBuffer& freq_buffer) {
    if (state.music_on) {
        return getPerlinColor(address, freq_buffer.getArray(0));
    } else {
        return testLightHausPattern(address, state, freq_buffer.getArray(0));
    }
}
