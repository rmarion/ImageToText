#ifndef IMAGE_TO_TEXT_CONVERTER_DEF
#define IMAGE_TO_TEXT_CONVERTER_DEF

#include <string>

namespace c_image_to_text
{
    class ImageToTextConverter
    {
    public:
        const std::string get_character_for_pixels(const short pixels[2][4]) const;

    private:
        const short threshold_ = 75;
    };
}

#endif