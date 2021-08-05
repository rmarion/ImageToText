from PIL import Image


def generate_images(outputDirectory):
    im = Image.new("RGB", (2, 4))
    pix = im.load()
    states = {0: (255, 255, 255), 1: (0, 0, 0)}

    maxbits = int('11111111', 2)
    for byte in range(0, maxbits + 1):
        # 1 if the nth-most bit is 1, 0 otherwise
        pix[0, 0] = states[byte & 1]
        pix[0, 1] = states[1 if byte & 2 else 0]
        pix[0, 2] = states[1 if byte & 4 else 0]
        pix[0, 3] = states[1 if byte & 8 else 0]
        pix[1, 0] = states[1 if byte & 16 else 0]
        pix[1, 1] = states[1 if byte & 32 else 0]
        pix[1, 2] = states[1 if byte & 64 else 0]
        pix[1, 3] = states[1 if byte & 128 else 0]

        im.save(f'{outputDirectory}/test_{byte:03}.png', 'PNG')


if __name__ == '__main__':
    generate_images('./TestImages')
