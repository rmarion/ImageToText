from imagetotext import get_text_for_image, get_character_for_pixels
import unittest
from PIL import Image

from importlib import import_module
import_module('imagetotext')


class SarcasticTests(unittest.TestCase):

    def test_gets_correct_character_for_pixels(self):
        im = Image.new("RGB", (2, 4), (0, 0, 0))
        pix = im.load()  # all black

        actual = get_character_for_pixels(pix)
        self.assertEqual(actual, chr(0X28FF))  # ⣿

        pix[0, 0] = (255, 255, 255)
        actual = get_character_for_pixels(pix)
        self.assertEqual(actual, chr(0X28FE))  # ⣾

        pix[1, 1] = (255, 255, 255)
        actual = get_character_for_pixels(pix)
        self.assertEqual(actual, chr(0X28EE))  # ⣮


if __name__ == '__main__':
    unittest.main()
