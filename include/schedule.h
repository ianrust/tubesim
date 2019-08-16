#pragma once

#include "types.h"
#include "images.h"

const size_t SCHEDULE_SIZE = 3;

const ScheduleDatum schedule[] = {
    {(Time){.hours = 1,  .minutes = 0, .seconds = 0}, .left_color1 = Color8bit(255, 0, 0), .left_color2 = Color8bit(255, 255, 0), .right_color1 = Color8bit(255, 45, 0), .right_color2 = Color8bit(2, 255, 0), .speed = 0.5, .num_wraps = 1.1},
    {(Time){.hours = 10,  .minutes = 45, .seconds = 0}, .left_color1 = Color8bit(0, 0, 0), .left_color2 = Color8bit(255, 255, 255), .right_color1 = Color8bit(5, 45, 0), .right_color2 = Color8bit(2, 255, 0), .speed = 0.01, .num_wraps = 0.2},
    {(Time){.hours = 22,  .minutes = 0, .seconds = 0}, .left_color1 = Color8bit(0, 255, 0), .left_color2 = Color8bit(255, 0, 255), .right_color1 = Color8bit(255, 45, 255), .right_color2 = Color8bit(2, 255, 0), .speed = 0.7, .num_wraps = 1.1},
};

const size_t ANIMATIONS_SIZE = 3;

const Animation animation_schedule[] = {
    {.flash_image = &organic, .speed_divisor_x = 2, .speed_divisor_y = 10000, .x_forward = true, .y_forward = true, .mask_prob = 1.0},
    {.flash_image = &pastel, .speed_divisor_x = 2, .speed_divisor_y = 4, .x_forward = true, .y_forward = true, .mask_prob = 0.0},
    {.flash_image = &hair, .speed_divisor_x = 3, .speed_divisor_y = 10000, .x_forward = false, .y_forward = false, .mask_prob = 0.1},
};