import unittest
from PIL import Image

from importlib import import_module
import_module('imagetotext')
from imagetotext import get_text_for_image, get_character_for_pixels

class SarcasticTests(unittest.TestCase):

    def test_gets_correct_character_for_pixels(self):
        im = Image.new('RGB', (2, 4), (0, 0, 0))
        pix = im.load()  # all black

        actual = get_character_for_pixels(pix)
        self.assertEqual(actual, chr(0X28FF))  # ⣿

        pix[0, 0] = (255, 255, 255)
        actual = get_character_for_pixels(pix)
        self.assertEqual(actual, chr(0X28FE))  # ⣾

        pix[1, 1] = (255, 255, 255)
        actual = get_character_for_pixels(pix)
        self.assertEqual(actual, chr(0X28EE))  # ⣮


    def test_gets_correct_character_for_8_pixel_image(self):
        im = Image.open('TestImages/allblack.png')
        actual = get_text_for_image(im)
        self.assertEqual(actual, chr(0X28FF))  # ⣿

        im = Image.open('TestImages/upperleft.png')
        actual = get_text_for_image(im)
        self.assertEqual(actual, chr(0X28FE))  # ⣾

        im = Image.open("TestImages/diagonal.png")
        actual = get_text_for_image(im)
        self.assertEqual(actual, chr(0X28EE))  # ⣮

    
    def test_gets_correct_grayscale_for_image(self):
        im_100 = Image.new('RGB', (2, 4), (0, 0, 0))
        actual = get_text_for_image(im_100.load())
        self.assertEqual(actual, chr(0X28FF))  # ⣿

        im_75 = Image.new('RGB', (2, 4), (64, 64, 64))
        actual = get_text_for_image(im_75.load())
        self.assertEqual(actual, chr(0X280C)) # ⠌

        im_50 = Image.new('RGB', (2, 4), (128, 128, 128))
        actual = get_text_for_image(im_50.load())
        self.assertEqual(actual, chr(0X286A)) # ⡪

        im_25 = Image.new('RGB', (2, 4), (192, 192, 192))
        actual = get_text_for_image(im_50.load())
        self.assertEqual(actual, chr(0X286A)) # 



    def test_gets_correct_character_for_256_pixel_image(self):
        im = Image.open('TestImages/allblack16x16.png')

        actual = get_text_for_image(im)
        self.assertEqual(len([character for character in actual if character == '⣿']), 32) # 32 non newline characters (256 / 8)
        self.assertEqual(len([character for character in actual if character == '\n']), 3) # 4 rows, 3 ending with newlines


if __name__ == '__main__':
    unittest.main()
