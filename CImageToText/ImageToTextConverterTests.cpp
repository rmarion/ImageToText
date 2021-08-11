#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include <numeric>
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

    auto pixels = get_pixels(0, 0, 2, 4, image);

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_character_for_pixels(pixels);
    auto expected = std::string(u8"\u28FF");

    return expected == actual;
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

bool expect_gets_correct_character_for_256_pixel_image()
{
    Image image;
    image.read("../TestImages/allblack16x16.png");

    auto sut = c_image_to_text::ImageToTextConverter();
    auto actual = sut.get_text_for_image(image);

    auto expected = std::string(u8"\u28FF");

    int black_characters = 0;
    auto black_char_pos = actual.find(expected);
    while (black_char_pos != std::string::npos)
    {
        black_characters++;
        black_char_pos = actual.find(expected, black_char_pos + expected.length());
    }

    auto newline = std::string("\n");
    int newlines = 0;
    auto newline_pos = actual.find(newline);
    while (newline_pos != std::string::npos)
    {
        newlines++;
        newline_pos = actual.find(newline, newline_pos + newline.length());
    }

    return black_characters == 32 && newlines == 4;
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
        expect_only_diagonal_white_image_returns_correct_unicode,
        expect_gets_correct_character_for_256_pixel_image};

    for (auto &test_method : test_methods)
    {
        try
        {
            if (test_method())
            {
                std::cout << "Test passed!" << std::endl;
            }
            else
            {
                std::cout << "Test failed." << std::endl;
            }
        }
        catch (std::exception &e)
        {
            std::cout << "Test failed: " << e.what() << std::endl;
        }
    }

    return 0;
}