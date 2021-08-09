#include <cassert>
#include <iostream>
#include <string>
#include "ImageToTextConverter.h"

int main(void)
{
    auto converter = c_image_to_text::ImageToTextConverter();
    short pixels[2][4] = {
        {255, 255, 255, 255},
        {255, 255, 255, 255}};
    auto actual = std::string(converter.get_character_for_pixels(pixels));
    auto expected = std::string(u8"\u28FF");
    assert(actual == expected);
    return 0;
}