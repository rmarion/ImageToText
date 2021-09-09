#include "ImageToTextConverter.h"
#include <array>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <Magick++.h>

#include <iostream>

using namespace Magick;

namespace c_image_to_text
{
    ImageToTextConverter::ImageToTextConverter(const ConverterMode converter_mode, const double cutoff_threshold, const int max_size)
        : converter_mode_(converter_mode), cutoff_threshold_(cutoff_threshold), max_size_(max_size)
    {
        // it's possible to chart these out to figure out the best order to assign these, if we want to put effort into that in the future
        double threshold_step = 1.0 / 8.0;
        gradient_thresholds_ =
            {{{threshold_step * 1,  // ⣾
               threshold_step * 5,  // ⣽
               threshold_step * 2,  // ⣻
               threshold_step * 7}, // ⣷
              {
                  threshold_step * 3, // ⣯
                  threshold_step * 6, // ⣟
                  threshold_step * 8, // ⢿
                  threshold_step * 4, // ⡿
              }}};
    }

    const bool ImageToTextConverter::exceeds_threshold(const std::array<std::array<double, 4>, 2> &pixels, const int column, const int row) const
    {

        if (converter_mode_ == ConverterMode::Cutoff)
        {
            return pixels[column][row] < cutoff_threshold_;
        }

        return pixels[column][row] < gradient_thresholds_[column][row];
    }

    const std::string ImageToTextConverter::get_character_for_pixels(const std::array<std::array<double, 4>, 2> &pixels) const
    {
        unsigned long byte = 0X28FF; // we'll progressively remove the non-matching parts of this with a bytemask to get our matching code

        if (exceeds_threshold(pixels, 0, 0)) // ⣾ //(pixels[0][0] > cutoff_threshold_)
        {
            byte ^= 1;
        }

        if (exceeds_threshold(pixels, 0, 1)) // ⣽
        {
            byte ^= 2;
        }

        if (exceeds_threshold(pixels, 0, 2)) // ⣻
        {
            byte ^= 4;
        }

        if (exceeds_threshold(pixels, 1, 0)) // ⣷
        {
            byte ^= 8;
        }

        if (exceeds_threshold(pixels, 1, 1)) // ⣯
        {
            byte ^= 16;
        }

        if (exceeds_threshold(pixels, 1, 2)) // ⣟
        {
            byte ^= 32;
        }

        if (exceeds_threshold(pixels, 0, 3)) // ⢿
        {
            byte ^= 64;
        }

        if (exceeds_threshold(pixels, 1, 3)) // ⡿
        {
            byte ^= 128;
        }
        // from https://stackoverflow.com/questions/20419605/how-to-convert-unicode-code-points-to-utf-8-in-c
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        auto string = converter.to_bytes(byte);

        return string;
    }

    const std::array<std::array<double, 4>, 2> ImageToTextConverter::get_pixels(const int x, const int y, const int width, const int height, const Image &image) const
    {
        auto pixels = std::array<std::array<double, 4>, 2>();

        for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < width; column++)
            {
                auto color = Magick::ColorGray(image.pixelColor(column + x, row + y));
                pixels[column][row] = color.shade();
            }
        }

        return pixels;
    }

    // We don't have this as const right now since we're changing the size here.
    // In the future, we should move the size change to the python entry point and generate the image there, making this const again.
    const std::string ImageToTextConverter::get_text_for_image(Image &image) const
    {
        clean_image(image);
        std::stringstream ss;
        std::array<std::array<double, 4>, 2> pixels;
        std::string newline = "\n";
        int max_row = (image.rows() / 4) * 4 - 1;
        int max_column = (image.columns() / 2) * 2 - 1;

        for (int y = 0; y < max_row; y += 4)
        {
            for (int x = 0; x < max_column; x += 2)
            {
                pixels = get_pixels(x, y, 2, 4, image);
                ss << get_character_for_pixels(pixels);
            }
            ss << newline;
        }

        return ss.str();
    }

    const void ImageToTextConverter::clean_image(Image &image) const
    {
        if (image.rows() > max_size_ || image.columns() > max_size_)
        {
            image.resize(Geometry(max_size_, max_size_));
        }

        if (image.alpha())
        {
            auto background = Image(image.size(), ColorMono(true));
            background.composite(image, 0, 0);
            image = background;
        }
    }
}