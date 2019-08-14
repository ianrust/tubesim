#pragma once

#include "types.h"

const size_t SCHEDULE_SIZE = 3;

const ScheduleDatum schedule[] = {
    {(Time){.hours = 1,  .minutes = 0, .seconds = 0}, .color1 = Color8bit(255, 0, 0), .color2 = Color8bit(255, 255, 0), .speed = 0.5, .num_wraps = 1.1},
    {(Time){.hours = 10,  .minutes = 45, .seconds = 0}, .color1 = Color8bit(0, 0, 0), .color2 = Color8bit(255, 255, 255), .speed = 0.01, .num_wraps = 0.2},
    {(Time){.hours = 22,  .minutes = 0, .seconds = 0}, .color1 = Color8bit(0, 255, 0), .color2 = Color8bit(255, 0, 255), .speed = 0.7, .num_wraps = 1.1},
};
