from PIL import Image


def get_text_for_image(image):
    pass


def get_character_for_pixels(pixels):
    threshold = 255 / 2
    byte = 255  # we'll progressively remove the non-matching parts of this with a bytemask to get our matching code
    
    if sum(pixels[0, 0]) / 3 > threshold: # ⣾
        byte ^= 1

    if sum(pixels[0, 1]) / 3 > threshold: # ⣽
        byte ^= 2

    if sum(pixels[0, 2]) / 3 > threshold: # ⣻
        byte ^= 4

    if sum(pixels[1, 0]) / 3 > threshold: # ⣷
        byte ^= 8

    if sum(pixels[1, 1]) / 3 > threshold: # ⣯
        byte ^= 16

    if sum(pixels[1, 2]) / 3 > threshold: # ⣟
        byte ^= 32

    if sum(pixels[0, 3]) / 3 > threshold: # ⢿
        byte ^= 64

    if sum(pixels[1, 3]) / 3 > threshold: # ⡿
        byte ^= 128

    return chr(0X2800 + byte)  # the braille unicode goes from 0X2800 -> 0X28FF
