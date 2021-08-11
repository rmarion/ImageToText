#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include "ImageToTextConverter.h"
#include <Magick++.h>

using namespace Magick;

bool expect_black_pixels_return_black_unicode()
{
    auto pixels = std::array<std::array<short, 4>, 2>{{{0, 0, 0, 0},
                                                       {0, 0, 0, 0}}};

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28FF");
    return expected == actual;
}

bool expect_white_pixels_return_white_unicode()
{
    auto pixels = std::array<std::array<short, 4>, 2>{{{255, 255, 255, 255},
                                                       {255, 255, 255, 255}}};

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u2800");
    return expected == actual;
}

bool expect_single_swapped_pixel_returns_correct_unicode()
{
    auto pixels = std::array<std::array<short, 4>, 2>{{{255, 0, 0},
                                                       {0, 0, 0}}};

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28FE");
    return expected == actual;
}

bool expect_two_swapped_pixels_return_correct_unicode()
{
    auto pixels = std::array<std::array<short, 4>, 2>{{{255, 0, 0},
                                                       {0, 255, 0}}};

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28EE");
    return expected == actual;
}

std::array<std::array<short, 4>, 2> get_pixels(int x, int y, int width, int height, Image image)
{
    auto pixels = std::array<std::array<short, 4>, 2>();
    for (int row = y; row < height; row++)
    {
        for (int column = x; column < width; column++)
        {
            auto color = ColorGray(image.pixelColor(column, row));
            pixels[column][row] = color.shade();
        }
    }

    return pixels;
}

bool expect_all_black_8_pixel_image_returns_correct_unicode()
{
    Image image;
    image.read("../TestImages/allblack.png");

    // int width = image.columns();
    // int height = image.rows();

    auto pixels = get_pixels(0, 0, 2, 4, image);

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28FF");

    return expected == actual;

    // for (int y = 0; y < height; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         std::cout << x << "," << y << ": Shade:" << test_pixels[x][y] << std::endl;
    //     }
    // }
}

bool expect_only_upper_left_white_image_returns_correct_unicode()
{
    Image image;
    image.read("../TestImages/upperleft.png");

    auto pixels = get_pixels(0, 0, 2, 4, image);

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28FE");

    return expected == actual;
}

bool expect_only_diagonal_white_image_returns_correct_unicode()
{
    Image image;
    image.read("../TestImages/diagonal.png");

    auto pixels = get_pixels(0, 0, 2, 4, image);

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28EE");

    return expected == actual;
}

int main(void)
{
    auto test_methods = std::vector<bool (*)()>{
        expect_black_pixels_return_black_unicode,
        expect_white_pixels_return_white_unicode,
        expect_single_swapped_pixel_returns_correct_unicode,
        expect_two_swapped_pixels_return_correct_unicode,
        expect_all_black_8_pixel_image_returns_correct_unicode,
        expect_only_upper_left_white_image_returns_correct_unicode,
        expect_only_diagonal_white_image_returns_correct_unicode};

    for (auto &test_method : test_methods)
    {
        try
        {
            assert(test_method());
            std::cout << "Test passed!" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << "Test failed: " << e.what() << std::endl;
        }
    }

    return 0;
}