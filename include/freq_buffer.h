#pragma once

#include "perlin.h"
#include "types.h"

//7x45=315 for tube size
//ring buffer
class FreqBuffer {
public:
    FreqBuffer() {
        for (size_t time_index = 0; time_index < buffer_len; time_index++) {
            buffer[time_index] = 0;
        }
        for (size_t spec_index = 0; spec_index < buffer_depth; spec_index++) {
            accum_buffer[spec_index] = 0;
        }
    }

    // 0 is always at start of buffer
    int16_t getValue(size_t time_index, size_t spec_index) {
        return buffer[getShiftedTimeIndex(time_index)*buffer_depth + spec_index];
    }

    // 0 is always at start of buffer
    int16_t* getArray(size_t time_index) {
        return &buffer[getShiftedTimeIndex(time_index)*buffer_depth];
    }

    Color8bit getColor(size_t time_index, size_t strip_index) {
        return color_buffer[getShiftedTimeIndex(time_index) * color_buffer_depth + (strip_index % color_buffer_depth)];
    }

    void accumulate(int16_t* freq) {
        // discard buffer overrun
        for (size_t spec_index = 0; spec_index < buffer_depth; spec_index++) {
            accum_buffer[spec_index] += freq[spec_index];
        }
        num_accums++;
    }

    void save() {
        buffer_index = (buffer_index + 1) % buffer_len;
        for (size_t spec_index = 0; spec_index < buffer_depth; spec_index++) {
            buffer[buffer_index*buffer_depth + spec_index] = accum_buffer[spec_index] / num_accums;
        }

//        reset accumulator
        for (size_t spec_index = 0; spec_index < buffer_depth; spec_index++) {
            accum_buffer[spec_index] = 0;
        }
        num_accums = 0;

        // store associated colors
        saveColors();
    }

// js interface
    void saveSingle(int16_t freq0, int16_t freq1, int16_t freq2, int16_t freq3, int16_t freq4, int16_t freq5, int16_t freq6) {
        buffer_index = (buffer_index + 1) % buffer_len;
        buffer[buffer_index*buffer_depth + 0] = freq0;
        buffer[buffer_index*buffer_depth + 1] = freq1;
        buffer[buffer_index*buffer_depth + 2] = freq2;
        buffer[buffer_index*buffer_depth + 3] = freq3;
        buffer[buffer_index*buffer_depth + 4] = freq4;
        buffer[buffer_index*buffer_depth + 5] = freq5;
        buffer[buffer_index*buffer_depth + 6] = freq6;

        saveColors();
    }
private:
    int16_t buffer[315];
    size_t buffer_len = 45;
    size_t buffer_depth = 7;
    // operates as a ring buffer
    size_t buffer_index = 0;

    // 12 rows, 45 length
    size_t color_buffer_depth = 12;
    Color8bit color_buffer[50*12];

    // for accumulated input
    int16_t accum_buffer[7];
    int16_t num_accums = 0;

    void saveColors() {
        for (size_t strip_index = 0; strip_index < color_buffer_depth; strip_index++) {
            color_buffer[buffer_index*color_buffer_depth + strip_index] = randColor(strip_index, getArray(0));
        }
    }

    size_t getShiftedTimeIndex(size_t time_index) {
        if (time_index > buffer_index) {
            return (buffer_len - (time_index - buffer_index)) % buffer_len;
        }
        return (buffer_index - time_index) % buffer_len;
    }
};
