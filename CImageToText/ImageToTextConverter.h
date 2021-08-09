#ifndef IMAGE_TO_TEXT_CONVERTER_DEF
#define IMAGE_TO_TEXT_CONVERTER_DEF

namespace c_image_to_text
{
    class ImageToTextConverter
    {
    public:
        ImageToTextConverter();
        ~ImageToTextConverter();
        const char *get_character_for_pixels(const short pixels[2][4]);

    private:
        const short threshold_ = 75
    };
}

#endif