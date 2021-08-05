from PIL import Image


def get_text_for_image(image):
    pass


threshold = 255 / 2


def get_character_for_pixels(pixels):
    byte = 255  # we'll progressively remove the non-matching parts of this with a bytemask to get our matching code
    # 1 if the nth-most bit is 1, 0 otherwise
    if sum(pixels[0, 0]) / 3 > threshold:
        byte &= 1
        print(0, 0)

    if sum(pixels[0, 1]) / 3 > threshold:
        byte &= 2
        print(0, 1)

    if sum(pixels[0, 2]) / 3 > threshold:
        byte &= 4
        print(0, 2)

    if sum(pixels[0, 3]) / 3 > threshold:
        byte &= 8
        print(0, 3)

    if sum(pixels[1, 0]) / 3 > threshold:
        byte &= 16
        print(1, 0)

    if sum(pixels[1, 1]) / 3 > threshold:
        byte &= 32
        print(1, 1)

    if sum(pixels[1, 2]) / 3 > threshold:
        byte &= 64
        print(1, 2)

    if sum(pixels[1, 3]) / 3 > threshold:
        byte &= 128

    return chr(0X2800 + byte)  # the braille unicode goes from 0X2800 -> 0X28FF
    # pix[0, 0] = states[byte & 1]
    # pix[0, 1] = states[1 if byte & 2 else 0]
    # pix[0, 2] = states[1 if byte & 4 else 0]
    # pix[0, 3] = states[1 if byte & 8 else 0]
    # pix[1, 0] = states[1 if byte & 16 else 0]
    # pix[1, 1] = states[1 if byte & 32 else 0]
    # pix[1, 2] = states[1 if byte & 64 else 0]
    # pix[1, 3] = states[1 if byte & 128 else 0]
