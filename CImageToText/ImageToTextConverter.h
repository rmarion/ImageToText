#ifndef IMAGE_TO_TEXT_CONVERTER_DEF
#define IMAGE_TO_TEXT_CONVERTER_DEF

#include <string>
#include <array>

namespace c_image_to_text
{
    class ImageToTextConverter
    {
    public:
        const std::string get_character_for_pixels(const std::array<std::array<short, 4>, 2> pixels) const;

    private:
        const double threshold_ = 0.4;
    };
}

#endif