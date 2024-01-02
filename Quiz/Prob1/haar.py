import numpy as np
import cv2
import argparse

def normalize(img):
    new_img = (img - img.min()) / (img.max() - img.min()) * 255.0
    return new_img

def haar_wavelet_transform(img, depth=1):
    h, w = img.shape
    if (h % 2 != 0):
        raise Exception("The height of the image is not divided by 2")
    if (w % 2 != 0):
        raise Exception("The width of the image is not divided by 2")
    
    img = img.astype(np.float32)
    L = (img[::2, :] + img[1::2, :]) / np.sqrt(2)
    H = (img[::2, :] - img[1::2, :]) / np.sqrt(2)
    LL = (L[:, ::2] + L[:, 1::2]) / np.sqrt(2)
    LH = (L[:, ::2] - L[:, 1::2]) / np.sqrt(2)
    HL = (H[:, ::2] + H[:, 1::2]) / np.sqrt(2)
    HH = (H[:, ::2] - H[:, 1::2]) / np.sqrt(2)
    img = np.vstack([np.hstack([LL, LH]), np.hstack([HL, HH])])

    del L, H, LL, LH, HL, HH
    if depth > 1:
        img[:h//2, :w//2] = haar_wavelet_transform(img[:h//2, :w//2], depth-1)

    return img


def main(args):
    image = cv2.imread(args.input, cv2.IMREAD_GRAYSCALE).astype(np.float32)
    image = normalize(image)
    transformed_image = haar_wavelet_transform(image, depth=args.depth)
    cv2.imwrite(args.output, transformed_image)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', type=str, required=True, help='input image path')
    parser.add_argument('--output', type=str, required=True, help='output image path')
    parser.add_argument('--depth', type=int, required=True, help='depth of Haar wavelet transform')
    args = parser.parse_args()
    main(args)