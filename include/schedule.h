#pragma once

#include "types.h"
#include "images.h"

const size_t SCHEDULE_SIZE = 8;

const ScheduleDatum schedule[] = {
    {(Time){.hours = 1,  .minutes = 0, .seconds = 0}, .left_color1 = Color8bit(255, 0, 0), .left_color2 = Color8bit(255, 255, 0), .right_color1 = Color8bit(255, 45, 0), .right_color2 = Color8bit(2, 255, 0), .speed = 0.5, .num_wraps = 1.1},

    // Sunrise start
    {(Time){.hours = 6,  .minutes = 8, .seconds = 0}, .left_color1 = Color8bit(0, 66, 87), .left_color2 = Color8bit(100, 93, 60), .right_color1 = Color8bit(0, 66, 87), .right_color2 = Color8bit(100, 93, 60), .speed = 0.01, .num_wraps = 2.0},
    {(Time){.hours = 8,  .minutes = 8, .seconds = 0}, .left_color1 = Color8bit(0, 66, 87), .left_color2 = Color8bit(100, 93, 60), .right_color1 = Color8bit(0, 66, 87), .right_color2 = Color8bit(100, 93, 60), .speed = 0.01, .num_wraps = 2.0},
    {(Time){.hours = 8,  .minutes = 45, .seconds = 0}, .left_color1 = Color8bit(0, 0, 0), .left_color2 = Color8bit(0, 0, 0), .right_color1 = Color8bit(0, 0, 0), .right_color2 = Color8bit(0, 0, 0), .speed = 0.01, .num_wraps = 0.2},

    // Sunset start
    {(Time){.hours = 19,  .minutes = 15, .seconds = 0}, .left_color1 = Color8bit(0, 0, 0), .left_color2 = Color8bit(0, 0, 0), .right_color1 = Color8bit(0, 0, 0), .right_color2 = Color8bit(0, 0, 0), .speed = 0.01, .num_wraps = 0.2},
    {(Time){.hours = 19,  .minutes = 45, .seconds = 0}, .left_color1 = Color8bit(33, 0, 66), .left_color2 = Color8bit(100, 45, 45), .right_color1 = Color8bit(33, 0, 66), .right_color2 = Color8bit(100, 45, 45), .speed = 0.01, .num_wraps = 2.0},
    {(Time){.hours = 21,  .minutes = 15, .seconds = 0}, .left_color1 = Color8bit(33, 0, 66), .left_color2 = Color8bit(100, 45, 45), .right_color1 = Color8bit(33, 0, 66), .right_color2 = Color8bit(100, 45, 45), .speed = 0.01, .num_wraps = 2.0},


    {(Time){.hours = 23,  .minutes = 0, .seconds = 0}, .left_color1 = Color8bit(0, 255, 0), .left_color2 = Color8bit(255, 0, 255), .right_color1 = Color8bit(255, 45, 255), .right_color2 = Color8bit(2, 255, 0), .speed = 0.7, .num_wraps = 1.1},
};

// for testing individual animations

//const size_t ANIMATIONS_SIZE = 1;
//
//const Animation animation_schedule[] = {
//    {.flash_image = &bubbles, .speed_divisor_x = 1000000, .speed_divisor_y = 2, .x_forward = false, .y_forward = false, .mask_prob = 0.2},
//};

const size_t ANIMATIONS_SIZE = 8;

const Animation animation_schedule[] = {
    {.flash_image = &organic, .speed_divisor_x = 2, .speed_divisor_y = 10000, .x_forward = true, .y_forward = true, .mask_prob = 1.0},
    {.flash_image = &pastel, .speed_divisor_x = 2, .speed_divisor_y = 4, .x_forward = true, .y_forward = true, .mask_prob = 0.0},
    {.flash_image = &hair, .speed_divisor_x = 3, .speed_divisor_y = 10000, .x_forward = false, .y_forward = false, .mask_prob = 0.4},
    {.flash_image = &cross_gradient, .speed_divisor_x = 3, .speed_divisor_y = 10000, .x_forward = false, .y_forward = false, .mask_prob = 0.7},
    {.flash_image = &leaves, .speed_divisor_x = 3, .speed_divisor_y = 5, .x_forward = false, .y_forward = false, .mask_prob = 0.5},
    {.flash_image = &squares, .speed_divisor_x = 3, .speed_divisor_y = 2, .x_forward = false, .y_forward = false, .mask_prob = 0.7},
    {.flash_image = &bubbles, .speed_divisor_x = 1000000, .speed_divisor_y = 2, .x_forward = false, .y_forward = false, .mask_prob = 0.2},
    {.flash_image = &eyeball, .speed_divisor_x = 4, .speed_divisor_y = 2, .x_forward = true, .y_forward = false, .mask_prob = 0.15},
};