#pragma once

#include "spectrum_analysis.h"
#include "types.h"

// This will also take in the frequency information as well as any other inputs/state (ie button press changes state)
Color8bit getGoalsColorPortable(int address, int tick, int16_t* freq) {
    normalize255(freq);
    bool clapping = isClapping(freq);
    if (clapping) {
        return Color8bit(255, 255, 255);
    } else {
        return Color8bit(freq[0]*5,
                         (freq[1] + freq[2] + freq[3] + freq[4])/(6 + address % 100),
                         freq[5]*(2 + address % 50));
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, int tick, int16_t* freq) {
    return Color8bit(0, 0, 1.0);
}
