#include "ImageToTextConverter.h"

namespace c_image_to_text
{
    const char *ImageToTextConverter::get_character_for_pixels(const short pixels[2][4])
    {
        short byte = 255; // we'll progressively remove the non-matching parts of this with a bytemask to get our matching code

        if (pixels[0][0] > threshold_) // ⣾
        {
            byte ^= 1;
        }

        if (pixels[0][1] > threshold_) // ⣽
        {
            byte ^= 2;
        }

        if (pixels[0][2] > threshold_) // ⣻
        {
            byte ^= 4;
        }

        if (pixels[1][0] > threshold_) // ⣷
        {
            byte ^= 8;
        }

        if (pixels[1][1] > threshold_) // ⣯
        {
            byte ^= 16;
        }

        if (pixels[1][2] > threshold_) // ⣟
        {
            byte ^= 32;
        }

        if (pixels[0][3] > threshold_) // ⢿
        {
            byte ^= 64;
        }

        if (pixels[1][3] > threshold_) // ⡿
        {
            byte ^= 128;
        }

        char bytes[4];
        unsigned long character = 0x2800 + byte;

        bytes[0] = (character >> 24) & 0xFF;
        bytes[1] = (character >> 16) & 0xFF;
        bytes[2] = (character >> 8) & 0xFF;
        bytes[3] = character & 0xFF;
        return bytes;
    }
}