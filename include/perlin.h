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

void rand2d(size_t mat_address, int16_t* freq, int16_t& x, int16_t& y) {
    x = y = 0;
    for (size_t mat_index = mat_address * 7; mat_index < (mat_address + 1) * 7; mat_index++) {
        size_t spec_index = mat_index % 7;
        if (ColorMats[mat_index]) {
            uint8_t row = (mat_index - (mat_address * 7)) / 7;
            if (row == 0) {
                x += freq[spec_index];
            } else if (row == 1) {
                y += freq[spec_index];
            }
        }
    }
    x -= (100*7/2);
    y -= (100*7/2);
}

int16_t dot2d(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    return (x1 * x2 + y1 * y2);
}

int16_t twoDPerlin(ImageIndex image_index, int16_t* freq, size_t offset) {
    size_t mat_address = image_index.x / GOAL_RADIAL_BINS + 3 * (image_index.y / GOAL_VERT_BINS);

    int16_t x_vertex = image_index.x % GOAL_RADIAL_BINS;
    int16_t y_vertex = image_index.y % GOAL_VERT_BINS;

    int16_t x_bottom_left, y_bottom_left;
    int16_t x_top_left, y_top_left;
    int16_t x_bottom_right, y_bottom_right;
    int16_t x_top_right, y_top_right;

    rand2d(offset + mat_address, freq, x_bottom_left, y_bottom_left);
    rand2d(offset + mat_address+3, freq, x_top_left, y_top_left);

    // handle wrapping
    if (mat_address % GOAL_RADIAL_BINS == 0) {
        rand2d(offset + mat_address-2, freq, x_bottom_right, y_bottom_right);
        rand2d(offset + mat_address+1, freq, x_top_right, y_top_right);
    } else {
        rand2d(offset + mat_address+1, freq, x_bottom_right, y_bottom_right);
        rand2d(offset + mat_address+4, freq, x_top_right, y_top_right);
    }

    float x_ratio = float(x_vertex) / GOAL_RADIAL_BINS;
    float y_ratio = float(y_vertex) / GOAL_VERT_BINS;

    int16_t scale = 1;

    int16_t influence_bottom_left = dot2d(x_bottom_left, y_bottom_left, x_vertex, y_vertex) / scale;
    int16_t influence_top_left = dot2d(x_top_left, y_top_left, x_vertex, y_vertex - GOAL_VERT_BINS) / scale;
    int16_t influence_bottom_right = dot2d(x_bottom_right, y_bottom_right, x_vertex - GOAL_RADIAL_BINS, y_vertex) / scale;
    int16_t influence_top_right = dot2d(x_top_right, y_top_right, x_vertex - GOAL_RADIAL_BINS, y_vertex - GOAL_VERT_BINS) / scale;

    int16_t left = influence_bottom_left * (1-y_ratio) + influence_top_left * y_ratio;
    int16_t right = influence_bottom_right * (1-y_ratio) + influence_top_right * y_ratio;

    return (left * (1-x_ratio) + right * x_ratio)+100;
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
                offset = 125;
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
    if (mapping_config.isGoal(address)) {
        ImageIndex image_index = mapping_config.addressToImageIndex(address);
        if (!image_index.valid) {
            return Color8bit(0, 0, 0);
        }

        int16_t red = twoDPerlin(image_index, freq, 0);
        int16_t green = twoDPerlin(image_index, freq, 20);
        int16_t blue = twoDPerlin(image_index, freq, 40);

        return Color8bit(red, green, blue);
    } else {
        size_t mat_address = (address % mapping_config.leds_per_channel) / LINES_BINS + 7*20;
        Color8bit c1 = randColor(mat_address, freq);
        Color8bit c2 = randColor(mat_address+1, freq);
        float ratio_line = float(address % LINES_BINS) / LINES_BINS;
        return interpolate(c1, c2, ratio_line);
    }
}