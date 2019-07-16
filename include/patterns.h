#pragma once

#include "types.h"

// This will also take in the frequency information as well as any other inputs/state (ie button press changes state)
Color8bit getGoalsColorPortable(int address, int tick) {
    if (address > tick) {
        return Color8bit(0, 0, int(float(address%150) * 255.0 / 150.0));
    } else {
        return Color8bit(int(float(tick % 150) * 255.0/ 150.0), int(float(address % 150) * 255.0/ 150.0), 0);
    }
}

// same as above, though this is for lines
Color8bit getLinesColorPortable(int address, int tick) {
    return Color8bit(0, 0, 1.0);
}
