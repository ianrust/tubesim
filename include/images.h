#pragma once

// creates a const array in flash that ImageData will index into
#include "types.h"
#include "../images/imagedata.h"

Color8bit getImageColor(const FlashImage* flash_image,
                        const size_t& address,
                        size_t x_offset,
                        size_t y_offset,
                        bool x_forward,
                        bool y_forward) {
    ImageIndex image_index = mapping_config.addressToImageIndex(address);

    // reverse direction by inverting offset
    if (!x_forward) {
        x_offset = flash_image->width - 1 - x_offset;
    }
    if (!y_forward) {
        y_offset = flash_image->height - 1 - y_offset;
    }

    size_t rgb_start = (((image_index.y + y_offset)%flash_image->height) * flash_image->width +
                         (image_index.x + x_offset)%flash_image->width) * 3 +
                         flash_image->start;

    return Color8bit(image_data[rgb_start], image_data[rgb_start+1], image_data[rgb_start+2]);
};

Color8bit getImageColor(const Animation& animation, const size_t& address, const size_t& tick) {
    return getImageColor(
        animation.flash_image,
        address,
        tick / animation.speed_divisor_x,
        tick / animation.speed_divisor_y,
        animation.x_forward,
        animation.y_forward
    );
};

Color8bit getImageColor(const Animation& animation, const size_t& address, const size_t& tick, const Color8bit& color1, const Color8bit& color2, const Color8bit& color3, const Color8bit& color4, float& ratio) {
    Color8bit image_color = getImageColor(animation, address, tick);
    float brightness = float(image_color.r + image_color.g + image_color.b) / (3.0 * 255.0);

    Color8bit grad1 = interpolate(color1, color2, ratio);
    Color8bit grad2 = interpolate(color3, color4, ratio);

    return interpolate(grad1, grad2, brightness);
};
