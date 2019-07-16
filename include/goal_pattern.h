#pragma once

#include "types.h"

Color8bit getGoalColorPortable(int address, int tick) {
    if (address > tick) {
        return Color8bit(0, 0, int(float(address%150) * 255.0 / 150.0));
    } else {
        return Color8bit(int(float(tick % 150) * 255.0/ 150.0), int(float(address % 150) * 255.0/ 150.0), 0);
    }
}
