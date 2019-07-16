#pragma once

#include "types.h"

Color getGoalColorPortable(int address, int tick) {
    if (address > tick) {
        return Color(0, 0, float(address%150) / 150.0);
    } else {
        return Color(float(tick % 30) / 30.0, float(address%50) / 50.0, 0);
    }
}