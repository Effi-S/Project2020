from PIL import Image
import argparse
import random
import os


def main():
    parser = argparse.ArgumentParser('Creates rotated image.')
    parser.add_argument('name', nargs='?', default=None, help='Name of image file path. Default is random file in directory', type=str)
    parser.add_argument('--angle', help='angle to rotate image if not entered a random angle is chosen between 1 and 359', default=None, type=int)
    args = parser.parse_args()

    angle = args.angle or random.randint(a=1, b=359)
    filename = args.name or random.choice(list(filter(lambda x: 'dup' not in x, os.listdir())))
    img = Image.open(filename)
    img2 = img.rotate(angle=angle, expand=False)
    name = filename.split('/')
    name[-1] = 'dup_{}_'.format(angle) + name[-1]
    img2.save('/'.join(name))
    

if __name__ == '__main__':
    main()
