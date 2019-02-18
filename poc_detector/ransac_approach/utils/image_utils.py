import numpy as np
import cv2
import matplotlib as plt

class ImageLoader():
    def __init__(self, filename=None):
        self.__bin_image = cv2.imread(filename, cv2.IMREAD_COLOR)

    @property
    def image(self):
        return self.__bin_image

