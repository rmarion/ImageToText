#ifndef IMAGE_TO_TEXT_CONVERTER_DEF
#define IMAGE_TO_TEXT_CONVERTER_DEF

#include <string>
#include <array>
#include <Magick++.h>

namespace c_image_to_text
{
    class ImageToTextConverter
    {
    public:
        const std::string get_character_for_pixels(const std::array<std::array<short, 4>, 2> &pixels) const;
        const std::string get_text_for_image(const Magick::Image &image) const;

    private:
        const double threshold_ = 0.4;
        const std::array<std::array<short, 4>, 2> get_pixels(int x, int y, int width, int height, const Magick::Image &image) const;
    };
}

#endif