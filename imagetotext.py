from PIL import Image


# This will cut off images that aren't a multiple of (2 x 4). If this becomes an issue for some reason, get_character_for_pixels can be extended for partials
def get_text_for_image(image):
    subwidth = 2
    subheight = 4

    x = 0
    y = 0

    columns = int(image.width / subwidth)
    rows = int(image.height / subheight)

    textlist = []

    for row in range(rows):
        rowlist = []
        for column in range(columns):
            x = row * subheight
            y = column * subwidth
            subimage = image.crop((x, y, x + subwidth, y + subheight))
            character = get_character_for_pixels(subimage.load())
            rowlist.append(character)
        textlist.append(''.join(rowlist))

    return '\n'.join(textlist)


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
