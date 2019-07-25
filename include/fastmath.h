#pragma once

#include <math.h>
#include "types.h"

#define RESOLUTION 1000

float SIN_TABLE[RESOLUTION];
float COS_TABLE[RESOLUTION];


float dotProduct(const Position& p1, const Position& p2) {
    return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

float fmodFast(const float& f, const float& divisor) {
    int quotient = f / divisor;
    return (f - (divisor * quotient));
}

void initializeTrigTables() {
    for (int i = 0; i < RESOLUTION; i++) {
        SIN_TABLE[i] = sin(2*M_PI*i / RESOLUTION);
        COS_TABLE[i] = cos(2*M_PI*i / RESOLUTION);
    }
}

float sinFast(float& theta) {
    size_t index = (theta / (2*M_PI)) * RESOLUTION;
    return SIN_TABLE[index];
}

float cosFast(float& theta) {
    size_t index = (theta / (2*M_PI)) * RESOLUTION;
    return SIN_TABLE[index];
}

