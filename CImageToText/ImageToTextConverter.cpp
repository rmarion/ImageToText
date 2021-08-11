#include "ImageToTextConverter.h"
#include <array>
#include <string>
#include <locale>
#include <codecvt>
#include <string>
#include <sstream>
#include <Magick++.h>

namespace c_image_to_text
{
    const std::string ImageToTextConverter::get_character_for_pixels(const std::array<std::array<short, 4>, 2> &pixels) const
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

    const std::array<std::array<short, 4>, 2> ImageToTextConverter::get_pixels(int x, int y, int width, int height, const Magick::Image &image) const
    {
        auto pixels = std::array<std::array<short, 4>, 2>();
        for (int row = y; row < height; row++)
        {
            for (int column = x; column < width; column++)
            {
                auto color = Magick::ColorGray(image.pixelColor(column, row));
                pixels[column][row] = color.shade();
            }
        }

        return pixels;
    }

    const std::string ImageToTextConverter::get_text_for_image(const Magick::Image &image) const
    {
        std::stringstream ss;
        std::array<std::array<short, 4>, 2> pixels;
        std::string newline = "\n";

        for (int y = 0; y < image.rows(); y += 4)
        {
            for (int x = 0; x < image.columns(); x += 2)
            {
                pixels = get_pixels(x, y, 2, 4, image);
                ss << get_character_for_pixels(pixels);
            }
            ss << newline;
        }

        return ss.str();
    }
}