#ifndef IMAGE_TO_TEXT_CONVERTER_DEF
#define IMAGE_TO_TEXT_CONVERTER_DEF

#include <string>
#include <array>
#include <Magick++.h>

using namespace Magick;

namespace c_image_to_text
{
    enum ConverterMode
    {
        Cutoff,
        Gradient
    };

    class ImageToTextConverter
    {
    public:
        ImageToTextConverter(const ConverterMode converter_mode = Cutoff, const double cutoff_threshold = 0.45, const int max_size = 256);
        const std::string get_character_for_pixels(const std::array<std::array<double, 4>, 2> &pixels) const;
        const std::string get_text_for_image(Image &image) const;
        const std::array<std::array<double, 4>, 2> get_pixels(const int x, const int y, const int width, const int height, const Image &image) const;

    private:
        const double cutoff_threshold_;
        const ConverterMode converter_mode_;
        const int max_size_;
        std::array<std::array<double, 4>, 2> gradient_thresholds_;
        const bool exceeds_threshold(const std::array<std::array<double, 4>, 2> &pixels, const int column, const int row) const;
        const void clean_image(Image &image) const;
    };

}

#endif