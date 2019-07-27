#pragma once

// creates a const array in flash that ImageData will index into
#include "types.h"
#include "../images/imagedata.h"

Color8bit getImageColor(const FlashImage& flash_image,
                        size_t& address,
                        size_t x_offset,
                        size_t y_offset,
                        bool x_forward,
                        bool y_forward) {
    ImageIndex image_index = mapping_config.addressToImageIndex(address);

    // reverse direction by inverting offset
    if (!x_forward) {
        x_offset = flash_image.width - 1 - x_offset;
    }
    if (!y_forward) {
        y_offset = flash_image.width - 1 - y_offset;
    }

    size_t rgb_start = (((image_index.y + y_offset)%flash_image.height) * flash_image.width +
                         (image_index.x + x_offset)%flash_image.width) * 3 +
                         flash_image.start;

    return Color8bit(image_data[rgb_start], image_data[rgb_start+1], image_data[rgb_start+2]);
};
