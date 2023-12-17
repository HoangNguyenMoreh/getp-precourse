import numpy as np
import cv2
import pickle

def load_image(file_path):
    image = np.load(file_path)
    return image

def apply_convolution(images, kernel, stride=1, padding=0):
    '''
    Implement 2D Convolution Using Numpy
    =================================================================================================
    Arguments:
        + images: np.array of shape (B, input_H, input_W)
        + kernel: np.array of shape (kernel_H, kernel_W)
        + stride: integer
        + padding: integer
    Outputs:
        + output_images: np.array of shape (B, input_H, input_W)
    '''
    kernel = np.flipud(np.fliplr(kernel))

    kernel_h, kernel_w = kernel.shape
    output_h = (images.shape[1] + 2 * padding - kernel.shape[0]) // stride + 1
    output_w = (images.shape[2] + 2 * padding - kernel.shape[1]) // stride + 1
    output_images = np.zeros((0, output_h, output_w))

    for image in images:
        if padding > 0:
            image_padded = np.zeros((image.shape[0] + 2 * padding, image.shape[1] + 2 * padding))
            image_padded[padding:-padding, padding:-padding] = image
        else:
            image_padded = image
        row_stride = stride * image_padded.strides[0]
        col_stride = stride * image_padded.strides[1]
        strides = (row_stride, col_stride) + image_padded.strides
        windows = np.lib.stride_tricks.as_strided(image_padded, 
                                                  shape=(output_h, output_w, kernel_h, kernel_w), 
                                                  strides=strides)
        output = np.tensordot(windows, kernel, axes=((2, 3), (0, 1)))
        output_images = np.append(output_images, [output], axis=0)

    return output_images


if __name__ == "__main__":

    input_file_path = "input_image.npy"

    input_images = load_image(input_file_path)
    num_images = input_images.shape[0]


    # Sobel filter
    sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    sobel_y = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])

    result_x = apply_convolution(input_images, sobel_x, stride=1, padding=1)
    result_y = apply_convolution(input_images, sobel_y, stride=1, padding=1)

    # Combine the results
    result = np.sqrt(result_x**2 + result_y**2)
    
    '''
    =================================================================================================
    Save and submit a portion of the processed 32 images. 
    You are free to choose any number of images (recommend 4~8)."
    '''


