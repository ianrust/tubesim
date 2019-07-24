#pragma once

#include <math.h>
#include "spectrum_analysis.h"
#include "mapping.h"
#include "types.h"
#include "../images/images.h"

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
    mapping_config.addressToLighthausParameter(address, 1.5, 0.1, state.tick, ratio);
    return interpolate(Color8bit(0, 56, 255), Color8bit(5, 255, 0), ratio);
}

// This will also take in the frequency information as well as any other inputs/state 
// (ie button press changes state)
// The main color function, takes in:
//    - the address of the LED
//    - the controller state
Color8bit getGoalsColorPortable(size_t address, ControllerState state, int16_t* freq) {
    size_t x_image, y_image;
    bool valid;
    mapping_config.addressToImageIndex(address, x_image, y_image, valid);
    float x_cart, y_cart, z_cart;
    mapping_config.addressToCartesianPoint(address, x_cart, y_cart, z_cart);
    if (!valid) {
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
        if (x_cart > 0 && state.goal_right) {
            // image display example
            size_t offset_x = (state.tick/(mapping_config.pitch_length_half));
            size_t offset_y = 0*(state.tick/2); // zero removes the scroll in that direction
            // reverse direction by inverting offset_x:
            offset_x = pixel_triangles_width - 1 - offset_x;
            size_t rgb_start = (((y_image+offset_y)%pixel_triangles_height) * pixel_triangles_width +
                                (x_image + offset_x)%pixel_triangles_width) * 3;

            return Color8bit(pixel_triangles[rgb_start], pixel_triangles[rgb_start+1], pixel_triangles[rgb_start+2]);
        } else if (x_cart < 0 && state.goal_left) {
            // Mixing example
            size_t offset_x = (state.tick / 12) % organic_width;
            size_t rgb_start = (y_image * organic_width + (x_image + offset_x)) * 3;
            float x_cart, y_cart, z_cart;
            mapping_config.addressToCartesianPoint(address, x_cart, y_cart, z_cart);
            int grad_level = z_cart * 255 / 5;
            float brightness = float(organic[rgb_start] + organic[rgb_start+1] + organic[rgb_start+2]) / (3.0 * 255.0);
            return Color8bit(int(grad_level), int((255-grad_level)*brightness), int((1.0-brightness)*255));
        }

        // ratio example
        return testLightHausPattern(address, state, freq);

        // // gradient block
        // int g = int(255.0*(z_cart)/5.0)*0;
        // int b = int(255.0*(x_cart+10.0)/20.0);
        // int r = 255-b;
        // return Color8bit(r, g, b);
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, ControllerState state, int16_t* freq) {
    return testLightHausPattern(address, state, freq);

    // // crappy mod scroll example
    // float x_cart, y_cart, z_cart;
    // mapping_config.addressToCartesianPoint(address, x_cart, y_cart, z_cart);
    // int r = int(255.0*fabs(y_cart+state.tick/3)/(mapping_config.pitch_width_half)) % 255;
    // int g = int(255.0*fabs(x_cart+state.tick/3)/(mapping_config.pitch_length_half)) % 255;
    // int b = 255-r;
    // return Color8bit(r, g, b);
}
