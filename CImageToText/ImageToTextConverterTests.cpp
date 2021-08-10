#include <cassert>
#include <iostream>
#include <string>
#include "ImageToTextConverter.h"

bool expect_black_pixels_return_black_unicode()
{
    short pixels[2][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28FF");
    return expected == actual;
}

bool expect_white_pixels_return_white_unicode()
{
    short pixels[2][4] = {
        {255, 255, 255, 255},
        {255, 255, 255, 255}};

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u2800");
    return expected == actual;
}

int main(void)
{
    assert(expect_black_pixels_return_black_unicode());
    assert(expect_white_pixels_return_white_unicode());
    return 0;
}