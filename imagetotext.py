import argparse
from PIL import Image, ImageOps


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
    threshold = 75
    byte = 255  # we'll progressively remove the non-matching parts of this with a bytemask to get our matching code

    if pixels[0, 0] > threshold: # ⣾
        byte ^= 1

    if pixels[0, 1] > threshold: # ⣽
        byte ^= 2

    if pixels[0, 2] > threshold: # ⣻
        byte ^= 4

    if pixels[1, 0] > threshold: # ⣷
        byte ^= 8

    if pixels[1, 1] > threshold: # ⣯
        byte ^= 16

    if pixels[1, 2] > threshold: # ⣟
        byte ^= 32

    if pixels[0, 3] > threshold: # ⢿
        byte ^= 64

    if pixels[1, 3] > threshold: # ⡿
        byte ^= 128

    return chr(0X2800 + byte)  # the braille unicode goes from 0X2800 -> 0X28FF


def get_args(argv=None):
    parser = argparse.ArgumentParser('Converts images to text')
    parser.add_argument('file', type=str, help='The file to make sarcastic')
    args = parser.parse_args()
    return args


def load_image(path, max_size):
    try:
        max_size = float(max_size)
        image = Image.open(path)
        current_size = image.size

        if current_size[0] > current_size[1]:
            ratio = max_size / current_size[0]
            new_size = (int(ratio * current_size[0]), int(ratio * current_size[1]))
        else:
            ratio = max_size / current_size[1]
            new_size = (int(ratio * current_size[0]), int(ratio * current_size[1]))

        return ImageOps.grayscale(image.resize(new_size))
        # return image
    except Exception as e:
        print(str(e))
        return None


def main(args):
    if not args.file:
        return 'You must provide either a file or phrase. Type sarcastic.py -h for help.'
    image = load_image(args.file, 128)
    if not image:
        return f'Failed to load {args.file}.'
    return get_text_for_image(image)
    

if __name__ == '__main__':
    args = get_args()
    print(main(args))
