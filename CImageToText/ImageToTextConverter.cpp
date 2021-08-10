#include "ImageToTextConverter.h"
#include <string>
#include <locale>
#include <codecvt>
#include <string>

namespace c_image_to_text
{
    const std::string ImageToTextConverter::get_character_for_pixels(const short pixels[2][4]) const
    {
        unsigned long byte = 0X28FF; // we'll progressively remove the non-matching parts of this with a bytemask to get our matching code

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
        // from https://stackoverflow.com/questions/20419605/how-to-convert-unicode-code-points-to-utf-8-in-c
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        auto string = converter.to_bytes(byte);

        return string;
    }
}