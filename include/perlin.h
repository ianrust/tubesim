#pragma once

#include "mapping.h"
#include "types.h"
#include "spectrum_analysis.h"

const size_t GOAL_RADIAL_BINS = 4;
const size_t GOAL_VERT_BINS = 10;
const size_t LINES_BINS = 50;

const size_t COLOR_MATS_SIZE = 500;
const int32_t SCALE_FREQ = (25*7);

// row-wise encoded array of matrices that map from spectrum to unit vector in color space.
bool ColorMats[COLOR_MATS_SIZE];

void initializePerlinMats() {
    for (size_t i = 0; i < COLOR_MATS_SIZE; i++) {
        // fill w/ 1s at a 50/50 chance
        // high frequencies bias white
        size_t spec_index = i % 7;
        if (spec_index == 5 || spec_index == 6) {
            ColorMats[i] = true;
        } else {
            ColorMats[i] = (rand() & 1) || (rand() & 2);
        }
    }
}

Color8bit randColor(size_t mat_address, int16_t* freq) {
    int16_t red;
    int16_t green;
    int16_t blue;
    for (size_t mat_index = mat_address * 7 * 3; mat_index < (mat_address + 1) * 7 * 3; mat_index++) {
        size_t spec_index = mat_index % 7;
        if (ColorMats[mat_index]) {
            uint8_t row = (mat_index - (mat_address * 7 * 3)) / 7;
            int16_t offset = 0;
            if (spec_index == 5 || spec_index == 6) {
                offset = 1205;
            }
            if (row == 0) {
                red += freq[spec_index] + offset;
            } else if (row == 1) {
                green += freq[spec_index] + offset;
            } else {
                blue += freq[spec_index] + offset;
            }
        }
    }

    red *= 255;
    red /= SCALE_FREQ;
    green *= 255;
    green /= SCALE_FREQ;
    blue *= 255;
    blue /= SCALE_FREQ;
    if (isClapping(freq)) {
        return Color8bit(255, 255, 255);
    } else {
        return Color8bit(red, green, blue);
    }
}

Color8bit getPerlinColor(size_t& address, int16_t* freq) {
    size_t mat_address;
    if (mapping_config.isGoal(address)) {
        ImageIndex image_index = mapping_config.addressToImageIndex(address);
        if (!image_index.valid) {
            return Color8bit(0, 0, 0);
        }
        mat_address = image_index.x / GOAL_RADIAL_BINS + 3 * (image_index.y / GOAL_VERT_BINS);

        Color8bit c_bottom_left = randColor(7*3*(mat_address), freq);
        Color8bit c_top_left = randColor(7*3*(mat_address+3), freq);

        Color8bit c_bottom_right;
        Color8bit c_top_right;

        // handle wrapping
        if (mat_address % GOAL_RADIAL_BINS == 4) {
            c_bottom_right = randColor(7*3*(mat_address - 2), freq);
            c_top_right= randColor(7*3*(mat_address + 1), freq);
        } else {
            c_bottom_right = randColor(7*3*(mat_address+1), freq);
            c_top_right= randColor(7*3*(mat_address+4), freq);
        }

        float ratio_x = float(image_index.x % GOAL_RADIAL_BINS) / GOAL_RADIAL_BINS;
        float ratio_y = float(image_index.y % GOAL_VERT_BINS) / GOAL_VERT_BINS;

        Color8bit c_left = interpolate(c_bottom_left, c_top_left, ratio_y);
        Color8bit c_right = interpolate(c_bottom_right, c_top_right, ratio_y);
        return interpolate(c_left, c_right, ratio_x);
    } else {
        mat_address = (address % mapping_config.leds_per_channel) / LINES_BINS + 7*20;
        Color8bit c1 = randColor(7*3*(mat_address), freq);
        Color8bit c2 = randColor(7*3*(mat_address+1), freq);
        float ratio_line = float(address % LINES_BINS) / LINES_BINS;
        return interpolate(c1, c2, ratio_line);
    }
}